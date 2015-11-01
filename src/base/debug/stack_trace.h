// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#ifndef BASE_DEBUG_STACK_TRACE_H_
#define BASE_DEBUG_STACK_TRACE_H_

#include <ostream>
#include <stddef.h>

#include "base/macros.h"

namespace base {

class StackTrace {
 public:
  // Creates a stacktrace from the current location.
  StackTrace();
  ~StackTrace();

  void OutputToStream(std::ostream* os) const;

 private:
  void** trace_;

  // The number of valid frames in |trace_|.
  size_t count_;

  DISALLOW_COPY_AND_ASSIGN(StackTrace); 
};

}  // namespace base

#endif  // BASE_DEBUG_STACK_TRACE_H_
