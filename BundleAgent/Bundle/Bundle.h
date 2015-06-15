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
 * FILE Bundle.h
 * AUTHOR Blackcatn13
 * DATE Jun 15, 2015
 * VERSION 1
 * This file contains the class Bundle.
 */
#ifndef BUNDLEAGENT_BUNDLE_BUNDLE_H_
#define BUNDLEAGENT_BUNDLE_BUNDLE_H_

#include <cstdint>
#include <string>
#include <vector>

#include "PrimaryBlock.h"
#include "Block.h"
/**
 * CLASS Bundle
 * This class represents a Bundle as defined into the RFC 5050.
 */
class Bundle {
 public:
  /**
   * @brief Empty constructor.
   *
   * This constructor will create an empty bundle, with an empty primaryBlock, and a payloadBlock.
   */
  Bundle();
  /**
   * @brief Raw constructor.
   *
   * This constructor will take a raw bundle and reconstruct the bundle from it.
   *
   * @param rawData the bundle in raw to covnert to a Bundle class.
   */
  explicit Bundle(uint8_t* rawData);
  /**
   * @brief Constructs a bundle with the provided information.
   *
   * This constructor will create a bundle with a source, a destination and a payload.
   *
   * @param origin of the bundle to generate.
   * @param destination to send the bundle.
   * @param payload information to add to the bundle.
   */
  Bundle(std::string origin, std::string destination, std::string payload);
  /**
   * Destructor of the class
   */
  virtual ~Bundle();
  /**
   * @brief Function to get the bundle in raw format.
   *
   * This function will generate a raw version of the current bundle.
   *
   * @return the bundle in raw format.
   */
  uint8_t* getRaw();
  /**
   * @brief Function to get the PrimaryBlock.
   *
   * This function returns a pointer to the primary block of the bundle.
   *
   * @return a pointer to the primary block.
   */
  PrimaryBlock* getPrimaryBlock();
  /**
   * @brief Function to get the other blocks of the bundle.
   *
   * This function returns all the blocks that the bundle holds.
   *
   * @return a vector with all the blocks.
   */
  std::vector<Block *> getBlocks();

 private:
  /**
   * Pointer to the primary block of the bundle.
   */
  PrimaryBlock* m_primaryBlock;
  /**
   * Vector containing the pointers to all the blocks that the bundle holds.
   */
  std::vector<Block *> m_blocks;
  /**
   * Pointer with the raw bundle.
   */
  uint8_t* m_raw;
};

#endif  // BUNDLEAGENT_BUNDLE_BUNDLE_H_
