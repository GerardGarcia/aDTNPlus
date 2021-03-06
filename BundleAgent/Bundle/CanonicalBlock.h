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
 * FILE Block.h
 * AUTHOR Blackcatn13
 * DATE Jun 15, 2015
 * VERSION 1
 * This file contains the CanonicalBlock class.
 */
#ifndef BUNDLEAGENT_BUNDLE_CANONICALBLOCK_H_
#define BUNDLEAGENT_BUNDLE_CANONICALBLOCK_H_

#include <cstdint>
#include <bitset>
#include <string>
#include "Bundle/BundleTypes.h"
#include "Bundle/Block.h"

/**
 * CLASS CanonicalBlock
 * This class represents a canonical block as described into the RFC 5050.
 * This class is a base class for all the blocks that are not primary.
 */
class CanonicalBlock : public Block {
 public:
  /**
   * @ brief Empty constructor.
   *
   * Generates an empty CanonicalBlock.
   */
  CanonicalBlock();
  /**
   * @brief Constructor.
   *
   * Generates an canonical block.
   *
   * @param raw data of this block.
   */
  explicit CanonicalBlock(const std::string &rawData);
  /**
   * Destructor of the class.
   */
  virtual ~CanonicalBlock();
  /**
   * @brief Function to update the block in raw format.
   *
   * This function will generate a raw version of the piece of bundle raw that corresponds to this block.
   * It returns only the block type and flags of the block.
   *
   * @return the block in raw format.
   */
  virtual std::string toRaw();
  /**
   * This function returns the block type value.
   *
   * @return The block type field.
   */
  uint8_t getBlockType();
  /**
   * @brief Sets the given flag.
   *
   * This function sets the given flag to value 1.
   *
   * @param procFlag the flag to set.
   *
   * @sa BlockControlFlags
   */
  void setProcFlag(CanonicalBlockControlFlags procFlag);
  /**
   * @brief Unset the given flag.
   *
   * This function sets the given flag to value 0.
   *
   * @param procFlag the flag to unset.
   *
   * @sa BlockControlFlags
   */
  void unsetProcFlag(CanonicalBlockControlFlags procFlag);
  /**
   * @brief Checks whether a flag is set.
   *
   * This function checks whether the given flag is set.
   *
   * @param procFlag the flag to check.
   * @return True if the flag is set, false otherwise.
   *
   * @sa BlockControlFlags
   */
  bool checkProcFlag(CanonicalBlockControlFlags procFlag);
  /**
   * @brief Returns an string with a nice view of the block information.
   *
   * @return The string with the block information.
   */
  virtual std::string toString();

 protected:
  /**
   * @brief Parses a Canonical Block from raw.
   *
   * This function parses a canonical block from raw.
   * Saving the raw data into the block.
   *
   * @param rawData Raw data to parse.
   */
  void initFromRaw(const std::string &rawData);
  /**
   * Variable that holds the Block Type value.
   */
  uint8_t m_blockType;
  /**
   * Variable that hold the bodyDataIndex of the rawData
   */
  int m_bodyDataIndex;
  /**
   * Block processing control flags, as described into the RFC 5050.
   */
  std::bitset<7> m_procFlags;
};

#endif  // BUNDLEAGENT_BUNDLE_CANONICALBLOCK_H_
