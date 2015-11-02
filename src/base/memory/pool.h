// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#ifndef BASE_MEMORY_POOL_H_
#define BASE_MEMORY_POOL_H_

#include <stddef.h>

#include "base/logging.h"
#include "base/macros.h"
#include "base/memory/stack.h"

namespace base {

template <typename T>
class Pool {
 public:
  Pool(size_t max_items) : max_items_(max_items), free_items_(max_items_) {
    DCHECK(max_items_ > 0) << "Can't create empty pool.";
    items_ = new T[max_items_];
    for(int i = 0; i < max_items_; i++)
      free_items_.Push(&items_[i]);
  } 

  ~Pool() {
    if (items_)
      delete[] items_;
  }

  size_t Size() const {
    return max_items_ - free_items_.Size();
  }

  template <typename... Params>
  T* Allocate(Params... parameters) {
    T** item = free_items_.Top();
    if (free_items_.Pop()) {
      new (*item) T(parameters...);
      return *item;
    } else {
      return nullptr;
    }
  }

  void Free(T* item) {
    DCHECK(item >= items_ && item < items_ + max_items_);
    item->~T();
    free_items_.Push(item); 
  }

 private:
  size_t max_items_;
  Stack<T*> free_items_;
  T* items_;

  DISALLOW_COPY_AND_ASSIGN(Pool);
};

}  // namespace base

#endif  // BASE_MEMORY_POOL_H_
