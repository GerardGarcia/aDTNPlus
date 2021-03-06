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
 * FILE BasicBundleProcessor.h
 * AUTHOR Blackcatn13
 * DATE Dec 17, 2015
 * VERSION 1
 *
 */
#ifndef BUNDLEAGENT_NODE_BUNDLEPROCESSOR_BASICBUNDLEPROCESSOR_H_
#define BUNDLEAGENT_NODE_BUNDLEPROCESSOR_BASICBUNDLEPROCESSOR_H_

#include <memory>
#include <vector>
#include <string>
#include "Node/BundleProcessor/BundleProcessor.h"
#include "Node/Executor/Worker.h"

class Bundle;
class BundleQueue;
class BundleContainer;
class NeighbourTable;
class ListeningAppsTable;
class Neighbour;

/**
 * CLASS BasicBundleProcessor
 * This class is an specification of the BundleProcessor.
 */
class BasicBundleProcessor : public BundleProcessor {
 public:
  /**
   * @brief Generates a BasicBundleProcessor.
   */
  BasicBundleProcessor();
  /**
   * Destructor of the class.
   */
  virtual ~BasicBundleProcessor();

  virtual void start(Config config, std::shared_ptr<BundleQueue> bundleQueue,
                     std::shared_ptr<NeighbourTable> neighbourTable,
                     std::shared_ptr<ListeningAppsTable> listeningAppsTable);

 protected:
  /**
   * Function that processes one given bundle container.
   *
   * @param bundleContainer The bundle container to process.
   */
  virtual void processBundle(std::unique_ptr<BundleContainer> bundleContainer);
  /**
   * Function that creates a bundle container.
   *
   * @param from The neighbour who has sent the bundle.
   * @param Bundle The bundle received.
   */
  std::unique_ptr<BundleContainer> createBundleContainer(
      std::shared_ptr<Neighbour> from, std::unique_ptr<Bundle> Bundle);
  /**
   * Function that checks the possible dispatching apps.
   *
   * @param bundleContainer The container with the bundle.
   * @return A list with the possible dispatching apps.
   */
  std::vector<std::string> checkDispatch(BundleContainer &bundleContainer);
  /**
   * Function that checks the lifetime of a bundle.
   *
   * @param bundleContainer The container with the bundle.
   * @return True if the lifetime has expired, false otherwise.
   */
  bool checkLifetime(BundleContainer &bundleContainer);
  /**
   * Function that checks the possible forwards.
   *
   * @param bundleContainer The container with the bundle.
   * @return A list with the possible forwards.
   */
  virtual std::vector<std::string> checkForward(
      BundleContainer &bundleContainer);
  /**
   * Function that checks if we are the destination node.
   *
   * @param bundleContainer The container with the bundle.
   * @return True if the bundle is for us.
   */
  bool checkDestination(BundleContainer &bundleContainer);
  /**
   * Worker to execute default forwarding code.
   */
  Worker<std::vector<std::string>, std::string, std::vector<std::string>> m_worker;

  static const std::string m_header;
  static const std::string m_footer;
  static const std::string m_commandLine;
};

#endif  // BUNDLEAGENT_NODE_BUNDLEPROCESSOR_BASICBUNDLEPROCESSOR_H_
