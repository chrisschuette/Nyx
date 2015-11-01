// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_FILES_FILE_UTIL_H_
#define BASE_FILES_FILE_UTIL_H_

#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "base/files/file_path.h"

namespace base {

bool ReadFileToMemory(const FilePath& path,
                      std::vector<uint8_t>* contents);

}  // namespace base

#endif  // BASE_FILES_FILE_UTIL_H_
