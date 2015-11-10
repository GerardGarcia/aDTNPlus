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
 * FILE Config.h
 * AUTHOR Blackcatn13
 * DATE Nov 10, 2015
 * VERSION 1
 *
 */
#ifndef BUNDLEAGENT_NODE_CONFIG_H_
#define BUNDLEAGENT_NODE_CONFIG_H_

#include <string>
#include "Utils/ConfigLoader.h"

class Config {
 public:
  /**
   *
   */
  Config();
  /**
   *
   * @param configFilename
   */
  explicit Config(const std::string &configFilename);
  /**
   *
   */
  virtual ~Config();
  /**
   * Get the node id in the configuration.
   *
   * @return The node id.
   */
  std::string getNodeId();
  /**
   * Get the node IP address in the configuration.
   *
   * @return The IP address.
   */
  std::string getNodeAddress();
  /**
   * Get the node Port in the configuration.
   *
   * @return The node Port.
   */
  int getNodePort();
  /**
   * Get the discovery IP address in the configuration.
   *
   * @return The discovery IP address.
   */
  std::string getDiscoveryAddress();
  /**
   * Get the discovery Port in the configuration.
   *
   * @return The discovery port.
   */
  int getDiscoveryPort();
  /**
   * Get the discovery period in the configuration.
   *
   * @return The discovery period.
   */
  int getDiscoveryPeriod();
  /**
   * Get the neighbour expiration time in the configuration.
   *
   * @return The neighbour expiration time.
   */
  int getNeighbourExpirationTime();
  /**
   * Get the neighbour cleaner time in the configuration.
   *
   * @return The cleaner time.
   */
  int getNeighbourCleanerTime();
  /**
   * Get the log filename in the configuration.
   *
   * @return The log filename.
   */
  std::string getFilename();
  /**
   * Get the log level in the configuration.
   *
   * @return The log level.
   */
  int getLevel();

 private:
  /**
   * Node id.
   */
  std::string m_nodeId;
  /**
   * IP address of the node.
   */
  std::string m_nodeAddress;
  /**
   * Port of the node.
   */
  int m_nodePort;
  /**
   * IP address of the discovery beacon.
   */
  std::string m_discoveryAddress;
  /**
   * Port of the discovery beacon.
   */
  int m_discoveryPort;
  /**
   * Period to send discovery beacons.
   */
  int m_discoveryPeriod;
  /**
   * Time to expire a not detected neighbour.
   */
  int m_neighbourExpirationTime;
  /**
   * Time to call the cleaner thread.
   */
  int m_neighbourCleanerTime;
  /**
   * Filename of the log file.
   */
  std::string m_filename;
  /**
   * Log level.
   */
  int m_level;
  /**
   * Variable that holds the Config Loader.
   */
  ConfigLoader m_configLoader;
  /**
   * Default values
   */
  static const std::string NODEID;
  static const std::string NODEADDRESS;
  static const int NODEPORT;
  static const std::string DISCOVERYADDRESS;
  static const int DISCOVERYPORT;
  static const int DISCOVERYPERIOD;
  static const int NEIGHBOUREXPIRATIONTIME;
  static const int NEIGHBOURCLEANERTIME;
  static const std::string FILENAME;
  static const int LEVEL;
};

#endif  // BUNDLEAGENT_NODE_CONFIG_H_
