// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/strings/string_util.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace base {

TEST(StringUtilTest, JoinString) {
  std::string separator(", ");
  std::vector<std::string> parts;
  EXPECT_EQ(std::string(), JoinString(parts, separator));

  parts.push_back("a");
  EXPECT_EQ("a", JoinString(parts, separator));

  parts.push_back("b");
  parts.push_back("c");
  EXPECT_EQ("a, b, c", JoinString(parts, separator));

  parts.push_back(std::string());
  EXPECT_EQ("a, b, c, ", JoinString(parts, separator));
  parts.push_back(" ");
  EXPECT_EQ("a|b|c|| ", JoinString(parts, "|"));
}

}  // namespace base
