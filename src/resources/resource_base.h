// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#ifndef RESOURCES_RESOURCE_BASE_H_
#define RESOURCES_RESOURCE_BASE_H_

#include "base/macros.h"

namespace resources {

class ResourceBase {
 public:
  enum ResourceType {
    TYPE_TEXTURE = 0,
    TYPE_SOUND = 1,
  };

 private:
  DISALLOW_COPY_AND_ASSIGN(ResourceBase);
};

}  // namespace resources

#endif  // RESOURCES_RESOURCE_BASE_H_
