// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#ifndef RESOURCES_RESOURCE_H_
#define RESOURCES_RESOURCE_H_

#include "resources/resource_base.h"

namespace resources {

template <typename T>
class Resource : public ResourceBase {
 public:
  Resource() {
  }
};

}  // namespace resources

#endif  // RESOURCES_RESOURCE_H_
