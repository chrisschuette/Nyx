// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#include "base/memory/stack.h"
#include "gtest/include/gtest/gtest.h"

namespace base {

namespace {

const size_t kMaxItems = 4;

}  // namespace

TEST(StackTest, PushTopPop) {
  Stack<int> stack(kMaxItems);
  EXPECT_TRUE(stack.Push(1)); 
  EXPECT_TRUE(stack.Push(2)); 
  EXPECT_EQ(2u, stack.Size());
  EXPECT_EQ(2, *stack.Top());
  EXPECT_TRUE(stack.Pop());
  EXPECT_EQ(1u, stack.Size());
  EXPECT_EQ(1, *stack.Top());
  EXPECT_TRUE(stack.Pop());
  EXPECT_TRUE(stack.IsEmpty());
}

TEST(StackTest, CannotPopEmpty) {
  Stack<int> stack(kMaxItems);
  EXPECT_FALSE(stack.Pop());
}

TEST(StackTest, CannotTopEmpty) {
  Stack<int> stack(kMaxItems);
  EXPECT_FALSE(stack.Top());
}

TEST(StackTest, CannotPushFull) {
  Stack<int> stack(kMaxItems);
  for(int i = 0; i < 4; i++)
    EXPECT_TRUE(stack.Push(i));
  EXPECT_FALSE(stack.Push(4));
}

TEST(StackTest, Clear) {
  Stack<int> stack(kMaxItems);
  for(int i = 0; i < 4; i++)
    EXPECT_TRUE(stack.Push(i));
  stack.Clear();
  EXPECT_EQ(0u, stack.Size());
}

}  // namespace base
