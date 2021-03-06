/*
 * Copyright (c) 2015 SeNDA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
/**
 * FILE NeighbourDiscoveryTest.cpp
 * AUTHOR Blackcatn13
 * DATE Jun 30, 2015
 * VERSION 1
 * This file contains the NeighbourDiscovery tests.
 */

#include <map>
#include <string>
#include <fstream>
#include <memory>
#include "Node/Neighbour/NeighbourDiscovery.h"
#include "gtest/gtest.h"
#include "Node/Neighbour/NeighbourTable.h"
#include "Node/Neighbour/Neighbour.h"
#include "Node/Config.h"
#include "Utils/globals.h"

/**
 * Check NeighbourCleaner thread.
 * Create the neighbour discovery object, add some neighbours and let the
 * cleaner delete them.
 * Stop the cleaner and check that it has really stopped.
 */
TEST(NeighbourDiscoveryTest, NeighbourCleanerTest) {
  g_stop = false;
  std::ofstream ss;
  ss.open("adtn.ini");
  ss << "[Node]" << std::endl << "nodeId : node1" << std::endl
     << "nodeAddress : 127.0.0.1" << std::endl << "nodePort : 40000"
     << std::endl << "[NeighbourDiscovery]" << std::endl
     << "discoveryAddress : 239.100.100.100" << std::endl
     << "discoveryPort : 40001" << std::endl << "discoveryPeriod : 2"
     << std::endl << "neighbourExpirationTime : 4" << std::endl
     << "neighbourCleanerTime : 2" << std::endl << "testMode : false"
     << std::endl << "[Logger]" << std::endl << "filename : /tmp/adtn.log"
     << std::endl << "level : 100" << std::endl << "[Constants]" << std::endl
     << "timeout : 3" << std::endl << "[BundleProcess]" << std::endl
     << "dataPath : /tmp/.adtn/" << std::endl;
  ss.close();
  Config cf = Config("adtn.ini");
  std::shared_ptr<NeighbourTable> nt = std::shared_ptr<NeighbourTable>(
      new NeighbourTable());
  NeighbourDiscovery nd(cf, nt);
  nt->update(std::make_shared<Neighbour>("node100", "192.168.1.1", 4000));
  auto neighbours = nt->getValues();
  ASSERT_EQ(1, neighbours.size());
  nt->update(std::make_shared<Neighbour>("node101", "192.168.1.1", 4000));
  neighbours.clear();
  neighbours = nt->getValues();
  ASSERT_EQ(2, neighbours.size());
  sleep(3);
  neighbours.clear();
  neighbours = nt->getValues();
  ASSERT_EQ(2, neighbours.size());
  nt->update(std::make_shared<Neighbour>("node101", "192.168.1.1", 4000));
  sleep(2);
  neighbours.clear();
  neighbours = nt->getValues();
  ASSERT_EQ(1, neighbours.size());
  ASSERT_EQ("node101", nt->getValue("node101")->getId());
  sleep(5);
  neighbours.clear();
  neighbours = nt->getValues();
  ASSERT_EQ(0, neighbours.size());
  g_stop = true;
  // The neighbour cleaner thread has been stopped, so the new neighbours
  // must not be cleaned.
  nt->update(std::make_shared<Neighbour>("node101", "192.168.1.1", 4000));
  sleep(5);
  neighbours.clear();
  neighbours = nt->getValues();
  ASSERT_EQ(1, neighbours.size());
}

/**
 * Check if the sender and receiver threads are working correctly.
 * To do this, we start the neighbour discovery, and put in test mode.
 * With this we are going to have a neighbour, ourselves.
 */
TEST(NeighbourDiscoveryTest, NeighbourSendAndReceiveTest) {
  g_stop = false;
  std::ofstream ss;
  ss.open("adtn1.ini");
  ss << "[Node]" << std::endl << "nodeId : node1" << std::endl
     << "nodeAddress : 127.0.0.1" << std::endl << "nodePort : 40000"
     << std::endl << "[NeighbourDiscovery]" << std::endl
     << "discoveryAddress : 239.100.100.100" << std::endl
     << "discoveryPort : 40001" << std::endl << "discoveryPeriod : 2"
     << std::endl << "neighbourExpirationTime : 4" << std::endl
     << "neighbourCleanerTime : 2" << std::endl << "testMode : true"
     << std::endl << "[Logger]" << std::endl << "filename : /tmp/adtn.log"
     << std::endl << "level : 100" << std::endl << "[Constants]" << std::endl
     << "timeout : 3" << std::endl << "[BundleProcess]" << std::endl
     << "dataPath : /tmp/.adtn/" << std::endl;
  ss.close();

  Config cf = Config("adtn1.ini");
  // clear the Nighbour table to ensure test values.
  sleep(1);
  std::shared_ptr<NeighbourTable> nt = std::shared_ptr<NeighbourTable>(
      new NeighbourTable());
  NeighbourDiscovery nd(cf, nt);
  sleep(3);
  auto neighbours = nt->getValues();
  ASSERT_EQ(1, neighbours.size());
  ASSERT_EQ("node1", nt->getValue(*neighbours.begin())->getId());
  ASSERT_EQ("127.0.0.1", nt->getValue(*neighbours.begin())->getNodeAddress());
  ASSERT_EQ(40000, nt->getValue(*neighbours.begin())->getNodePort());
  g_stop = true;
  sleep(5);
}
