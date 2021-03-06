// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#include "resources/resource_manager.h"

#include "resources/file_server.h"

namespace resources {

ResourceManager::ResourceManager(FileServer* file_server)
    : file_server_(file_server) {
  }

}  // namespace resources
