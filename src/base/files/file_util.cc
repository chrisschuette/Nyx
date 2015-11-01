// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/files/file_util.h"

#include <memory>

namespace base {

bool ReadFileToMemory(const FilePath& path,
                      std::vector<uint8_t>* contents) {
  if (contents)
        contents->clear();
  FILE* file = fopen(path.string().c_str(), "rb");
  if (!file)
    return false;
  
  // Obtain the file size.
  fseek (file , 0 , SEEK_END);
  size_t size = ftell (file);
  rewind (file);

  if (contents) {
    try {
      contents->resize(size);
    } catch (std::bad_alloc& e) {
      fclose(file);
      return false;
    }
    size_t size_read = fread(contents->data(), 1, size, file);
    if (size_read != size) {
      fclose(file);
      return false;
    }
  }

  fclose(file);
  return true;
}

}  // namespace base
