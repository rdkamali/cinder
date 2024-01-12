// Copyright (c) Facebook, Inc. and its affiliates. (http://www.facebook.com)
#include <gtest/gtest.h>

#include "cinderx/Jit/bytecode_offsets.h"

using namespace jit;

TEST(BytecodeOffsetsTest, Basic) {
  EXPECT_EQ(BCOffset{6}.value(), 6);
  EXPECT_EQ(BCIndex{10}.value(), 10);
}

TEST(BytecodeOffsetsTest, Comparison) {
  // The comparison operators are autogenerated from <=>,. Sanity-check a few of
  // them.
  EXPECT_EQ(BCOffset{4}, BCOffset{4});
  EXPECT_EQ(BCIndex{12}, BCIndex{12});
  EXPECT_LT(BCOffset{1}, BCOffset{4});
  EXPECT_GT(BCIndex{20}, BCIndex{10});

  EXPECT_EQ(BCOffset{123}, 123);
  EXPECT_EQ(BCIndex{456}, 456);
  EXPECT_LT(40, BCOffset{50});
  EXPECT_GT(60, BCIndex{59});
}

TEST(BytecodeOffsetsTest, Conversion) {
  BCOffset offset_12{12};
  BCIndex index_12{12};

  BCOffset converted_offset = index_12;
  EXPECT_EQ(converted_offset.value(), 12 * sizeof(_Py_CODEUNIT));

  BCIndex converted_index = offset_12;
  EXPECT_EQ(converted_index.value(), 12 / sizeof(_Py_CODEUNIT));
}

TEST(BytecodeOffsetsTest, Arithmetic) {
  // All arithmetic operators are defined in the base class. Exercise them using
  // BCOffset.
  BCOffset offset_4{4}, offset_6{6};
  EXPECT_EQ(offset_4 + 5, BCOffset{9});

  EXPECT_EQ(offset_6 - 3, BCOffset{3});
  EXPECT_EQ(offset_6 - offset_4, 2);

  EXPECT_EQ(offset_6 * 3, BCOffset{18});

  EXPECT_EQ(++offset_4, BCOffset{5});
  EXPECT_EQ(offset_4++, BCOffset{5});

  EXPECT_EQ(offset_4--, BCOffset{6});
  EXPECT_EQ(--offset_4, BCOffset{4});
}
