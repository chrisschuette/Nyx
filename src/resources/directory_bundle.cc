// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "resources/directory_bundle.h"

namespace resources {

DirectoryBundle::DirectoryBundle(const base::FilePath& directory)
    : Bundle(directory.string()), directory_(directory) {
}

}  // namespace resources 
