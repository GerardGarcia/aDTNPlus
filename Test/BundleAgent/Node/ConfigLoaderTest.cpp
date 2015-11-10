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
 * FILE ConfigLoaderTest.cpp
 * AUTHOR Blackcatn13
 * DATE Jun 30, 2015
 * VERSION 1
 * This file contains the test of the ConfigLoader class.
 */

#include "Node/ConfigLoader.h"
#include "gtest/gtest.h"

/**
 * Check the configuration load.
 * Load the configuration file and check that all the fields are correct.
 */
TEST(ConfigLoaderTest, ParseFile) {
  ConfigLoader cf = ConfigLoader();
  ASSERT_TRUE(cf.load("../BundleAgent/Config/adtn.ini"));
  ASSERT_EQ("node1", cf.getNodeId());
  ASSERT_EQ("127.0.0.1", cf.getNodeAddress());
  ASSERT_EQ(40000, cf.getNodePort());
  ASSERT_EQ("239.100.100.100", cf.getDiscoveryAddress());
  ASSERT_EQ(40001, cf.getDiscoveryPort());
  ASSERT_EQ(2, cf.getDiscoveryPeriod());
  ASSERT_EQ(4, cf.getNeighbourExpirationTime());
}
