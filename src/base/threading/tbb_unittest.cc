// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#include <iostream>
#include <tbb/task_group.h>

#include "gtest/include/gtest/gtest.h"

namespace base {

namespace {

int calculate_fibonacci(int n) {
  if (n < 2) {
    return n;
  } else {
    int x, y;
    tbb::task_group g;
    g.run([&] { x = calculate_fibonacci(n - 1); });
    g.run([&] { y = calculate_fibonacci(n - 2); });
    g.wait();
    return x + y;
  }
}

}  // namespace

TEST(TBBTest, Compiles) {
  EXPECT_EQ(6765, calculate_fibonacci(20));
}

}  // namespace base
