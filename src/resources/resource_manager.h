// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#ifndef RESOURCES_RESOURCE_MANAGER_H_
#define RESOURCES_RESOURCE_MANAGER_H_

#include <memory>
#include <unordered_map>

#include "base/macros.h"
#include "resources/bundle.h"
#include "resources/resource.h"

namespace resources {

// Forward declarations.
class FileServer;

class ResourceManager {
 public:
  // |file_server| must outlive this instance. 
  ResourceManager(FileServer* file_server);

  // Retrieves a handle to a resource.
  // template <typename T>
  // Handle<T> getResource(const AssetId asset_it) {
  //
  // }

 private:
  // The FileServer responsible for loading assets from bundles.
  FileServer* file_server_;

  // Maps asset ids to resources.
  std::unordered_map<AssetId, ResourceBase*> resources_;

  DISALLOW_COPY_AND_ASSIGN(ResourceManager);
};

}  // namespace resources

#endif  // RESOURCES_RESOURCE_MANAGER_H_
