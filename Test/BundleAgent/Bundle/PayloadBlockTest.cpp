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
 * FILE PayloadBlockTest.cpp
 * AUTHOR Blackcatn13
 * DATE Jun 18, 2015
 * VERSION 1
 * This file contains the test of the PayloadBlock class.
 */

#include <string>
#include "gtest/gtest.h"
#include "Bundle/PayloadBlock.h"

/**
 * Check the default constructor.
 * The payload must be empty, and the block type must be
 * a PAYLOAD_BLOCK type.
 */
TEST(PayloadBlockTest, DefaultConstructor) {
  PayloadBlock pb = PayloadBlock("");
  ASSERT_EQ("", pb.getPayload());
  ASSERT_EQ(static_cast<uint8_t>(CanonicalBlockTypes::PAYLOAD_BLOCK),
            pb.getBlockType());
}

/**
 * Check the payload set.
 * After setting a payload and then retrieving it, they must have
 * the same value.
 */
TEST(PayloadBlockTest, SetGetPayload) {
  PayloadBlock pb = PayloadBlock("");
  ASSERT_EQ("", pb.getPayload());
  pb = PayloadBlock("This is a test payload");
  ASSERT_EQ("This is a test payload", pb.getPayload());
  pb = PayloadBlock("This is a new test payload");
  ASSERT_EQ("This is a new test payload", pb.getPayload());
}

/**
 * Test that after calling toRaw, getRaw returns this new raw
 */
TEST(PayloadBlockTest, RawTest) {
  PayloadBlock pb = PayloadBlock("This is");
  ASSERT_EQ("", pb.getRaw());
  std::string raw = pb.toRaw();
  ASSERT_EQ(raw, pb.getRaw());
}

/**
 * Test a bad block construction
 */
TEST(PayloadBlockTest, PayloadBadBlockConstruction) {
  PayloadBlock pb = PayloadBlock("This is a big payload");
  std::stringstream ss;
    ss << (uint8_t)CanonicalBlockTypes::PAYLOAD_BLOCK;
    ss << "Canonical Block without flags and length SDNV";
  ASSERT_THROW(PayloadBlock(ss.str(), true),
               BlockConstructionException);
}

/**
 * Check the raw functions.
 * Generate a PayloadBlock, convert it to raw.
 * Generate a new PayloadBlock from the raw.
 * The new PayloadBlock must contain the same as the original.
 */
TEST(PayloadBlockTest, RawFunctions) {
  PayloadBlock pb = PayloadBlock("This is a test payload");
  std::string rawBlock = pb.toRaw();
  PayloadBlock pb1 = PayloadBlock(rawBlock, true);
  ASSERT_EQ(static_cast<uint8_t>(CanonicalBlockTypes::PAYLOAD_BLOCK),
            pb1.getBlockType());
  ASSERT_EQ("This is a test payload", pb1.getPayload());
}

/**
 * Check Flags
 */
TEST(PayloadBlockTest, FlagTest) {
  PayloadBlock pb = PayloadBlock("");
  pb.setProcFlag(CanonicalBlockControlFlags::LAST_BLOCK);
  pb.setProcFlag(CanonicalBlockControlFlags::BLOCK_NOT_PROCESSED);
  ASSERT_TRUE(pb.checkProcFlag(CanonicalBlockControlFlags::LAST_BLOCK));
  ASSERT_FALSE(pb.checkProcFlag(CanonicalBlockControlFlags::DELETE_BUNDLE));
  ASSERT_TRUE(
      pb.checkProcFlag(CanonicalBlockControlFlags::BLOCK_NOT_PROCESSED));
  ASSERT_FALSE(
      pb.checkProcFlag(CanonicalBlockControlFlags::REPLICATE_FRAGMENT));
  pb.unsetProcFlag(CanonicalBlockControlFlags::BLOCK_NOT_PROCESSED);
  ASSERT_FALSE(
      pb.checkProcFlag(CanonicalBlockControlFlags::BLOCK_NOT_PROCESSED));
}
