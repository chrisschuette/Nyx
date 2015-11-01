// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#include <string>

#include "base/memory/pool.h"
#include "gtest/include/gtest/gtest.h"

namespace base {

namespace {

size_t max_items = 4;

class TestObject {
 public:
  TestObject() {
    constructor_called = true;
  }

  ~TestObject() {
    destructor_called = true;
  }

  static bool constructor_called;
  static bool destructor_called;

  DISALLOW_COPY_AND_ASSIGN(TestObject);
};

bool TestObject::constructor_called = false;
bool TestObject::destructor_called = false;

}  // namespace

TEST(PoolTest, AllocateAndFree) {
  Pool<std::string> pool(max_items);
  EXPECT_EQ(0u, pool.Size());
  std::string* item = pool.Allocate("Foo");
  EXPECT_EQ("Foo", *item);
  EXPECT_EQ(1u, pool.Size());
  pool.Free(item);
  EXPECT_EQ(0u, pool.Size());
  item = pool.Allocate("Bar");
  EXPECT_EQ("Bar", *item);
  EXPECT_EQ(1u, pool.Size());
}

TEST(PoolTest, ConstructorDestructorCalls) {
  Pool<TestObject> pool(max_items);
  TestObject::constructor_called = false;
  TestObject::destructor_called = false;
  TestObject* test_object = pool.Allocate();
  EXPECT_TRUE(TestObject::constructor_called);
  EXPECT_FALSE(TestObject::destructor_called);
  TestObject::constructor_called = false;
  pool.Free(test_object);
  EXPECT_FALSE(TestObject::constructor_called);
  EXPECT_TRUE(TestObject::destructor_called);
}

}  // namespace base 
