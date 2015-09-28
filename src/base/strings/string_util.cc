// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/strings/string_util.h"

namespace base {

namespace {

template <typename T>
std::string JoinStringT(const std::vector<std::string>& parts,
		       const T& separator) {
  if (parts.empty())
    return std::string();

  std::string result(parts[0]);
  auto iter = parts.begin();
  ++iter;

  for (; iter != parts.end(); ++iter) {
    result += separator;
    result += *iter;
  }

  return result;
}

}  // namespace

std::string JoinString(const std::vector<std::string>& parts, char separator) {
  return JoinStringT(parts, separator);
}

std::string JoinString(const std::vector<std::string>& parts,
                       const std::string& separator) {
  return JoinStringT(parts, separator);
}

}  // namespace base
