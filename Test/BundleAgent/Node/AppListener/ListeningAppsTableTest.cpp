/*
* Copyright (c) 2016 SeNDA
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRAlatIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
/**
 * FILE ListeningAppsTableTest.cpp
 * AUTHOR Blackcatn13
 * DATE Jan 19, 2016
 * VERSION 1
 * This file contains the tests of the ListeningAppsTable class.
 */

#include <string>
#include <map>
#include <memory>
#include <vector>
#include "Node/AppListener/ListeningAppsTable.h"
#include "gtest/gtest.h"
#include "Node/AppListener/App.h"

/**
 * Check the add and remove options.
 * Add an app, check that the app is in, sleep for 2s,
 * clean all the apps that have more than 1s of time.
 * Check that we did not loose the app.
 * Get the apps again, and check that now the app is out.
 */
TEST(ListeningAppsTableTest, AddAndRemove) {
  ListeningAppsTable* lat = new ListeningAppsTable();
  lat->update(std::make_shared<App>("100", "192.168.1.1", 40000, 1));
  // Get the neighbours
  auto apps = lat->getValues();
  // Check neighbour
  ASSERT_EQ("100", lat->getValue("100")->getId());
  sleep(2);
  // Clean the neighbour
  auto app = lat->getValue("100");
  lat->clean(1);
  // Check that we still hold the pointer
  ASSERT_EQ("100", app->getId());
  apps.clear();
  apps = lat->getValues();
  ASSERT_THROW(lat->getValue("100"), TableException);
  delete lat;
}

/**
 * Check add and remove with more apps.
 * Make the same as the previous test, but with more apps.
 */
TEST(ListeningAppsTableTest, AddAndRemoveMore) {
  ListeningAppsTable* lat = new ListeningAppsTable();
  lat->update(std::make_shared<App>("100", "192.168.1.1", 40100, 1));
  sleep(1);
  lat->update(std::make_shared<App>("101", "192.168.1.1", 40101, 2));
  sleep(1);
  lat->update(std::make_shared<App>("102", "192.168.1.1", 40102, 3));
  auto apps = lat->getValues();
  ASSERT_EQ(3, apps.size());
  ASSERT_EQ(40100, lat->getValue("100")->getAppPort());
  ASSERT_EQ(40101, lat->getValue("101")->getAppPort());
  ASSERT_EQ(40102, lat->getValue("102")->getAppPort());
  lat->clean(2);
  apps.clear();
  apps = lat->getValues();
  ASSERT_EQ(2, apps.size());
  ASSERT_EQ(40101, lat->getValue("101")->getAppPort());
  ASSERT_EQ(40102, lat->getValue("102")->getAppPort());
  lat->clean(1);
  apps.clear();
  lat->update(std::make_shared<App>("102", "192.168.1.1", 40105, 3));
  apps = lat->getValues();
  ASSERT_EQ(1, apps.size());
  ASSERT_EQ(40105, lat->getValue("102")->getAppPort());
  apps.clear();
  lat->update(std::make_shared<App>("102", "192.168.1.102", 40105, 3));
  apps = lat->getValues();
  ASSERT_EQ(1, apps.size());
  ASSERT_EQ("192.168.1.102", lat->getValue("102")->getAppAddress());
  delete lat;
}


