// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#ifndef RESOURCES_FILE_SERVER_H_
#define RESOURCES_FILE_SERVER_H_

#include "base/macros.h"
#include "resources/bundle.h"

namespace resources {

// The FileServer class is responsible for loading asset data from Bundles.
class FileServer {
 public:
  void AttachBundle(Bundle& bundle);

 private:
  DISALLOW_COPY_AND_ASSIGN(FileServer);
};

}  // namespace resources

#endif  // RESOURCES_FILE_SERVER_H_
