// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/files/file_path.h"
#include "resources/bundle.h"

#ifndef RESOURCES_DIRECTORY_BUNDLE_H_
#define RESOURCES_DIRECTORY_BUNDLE_H_

namespace resources {

// A directory-backed implementation of Bundle. The AssetIds correspond to
// filenames in that directory.
class DirectoryBundle : public Bundle {
 public:
  DirectoryBundle(const base::FilePath& directory);  

 private:
  // FilePath for the base directory.
  base::FilePath directory_;

  DISALLOW_COPY_AND_ASSIGN(DirectoryBundle);
};

}  // namespace resources

#endif  // RESOURCES_DIRECTORY_BUNDLE_H_
