// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// This file defines utility functions for working with strings.

#ifndef BASE_STRINGS_STRING_UTIL_H_
#define BASE_STRINGS_STRING_UTIL_H_

#include <string>
#include <vector>

namespace base {

// Does the opposite of SplitString().
std::string JoinString(const std::vector<std::string>& parts,
                       char separator);
std::string JoinString(const std::vector<std::string>& parts,
                       const std::string& separator);

}  // namespace base

#endif  // BASE_STRINGS_STRING_UTIL_H_
