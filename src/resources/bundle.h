// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef RESOURCES_BUNDLE_H_ 
#define RESOURCES_BUNDLE_H_

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "base/macros.h"

namespace resources {

using BundleId = std::string;
using AssetId = std::string;

// Bundle defines an read-only interface for containers of game assets.
class Bundle {
 public:
  Bundle(const BundleId& bundle_id);
  virtual ~Bundle();

  // Returns true if the bundle 
  virtual bool Contains(const AssetId& assetId) const = 0;

  // Reads the data for |assetId| into |contents| and returns true on success.
  // Otherwise returns false. When the file size exceeds |max_size|, the
  // function returns false with |contents| unaltered. |contents| may be NULL.
  virtual bool Read(const AssetId& assetId,
                    std::vector<uint8_t>* contents,
                    size_t max_size) const = 0;

 private:
  // The BundleId identifying this Bundle.
  const BundleId bundle_id_;

  DISALLOW_COPY_AND_ASSIGN(Bundle);
};

}  // namespace resources

#endif  // RESOURCES_BUNDLE_H_
