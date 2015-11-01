// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#ifndef BASE_MEMORY_STACK_H_
#define BASE_MEMORY_STACK_H_

#include <stddef.h>

#include "base/macros.h"

namespace base {

template <class T>
class Stack {
 public:
  Stack(size_t max_items) : max_items_(max_items), top_(0) {
    if (max_items_ > 0)
      data_ = new T[max_items_];
    else
      data_ = nullptr;
  }

  ~Stack() {
    if (data_)
      delete [] data_;
  }

  void Clear() {
    top_ = 0;
  }

  bool IsEmpty() {
    return top_ == 0;
  }

  bool Push(T item) {
    if (top_ >= max_items_) {
      // TODO(cschuet): Handle error.
      return false;
    }

    data_[top_++] = item;
    return true;
  }

  bool Pop() {
    if (top_ == 0) {
      // TODO(cschuet): Handle error.
      return false;
    }

    --top_;
    return true;
  }

  size_t Size() const {
    return top_;
  }

  T* Top() {
    if (top_ == 0) {
      // TODO(cschuet): Handle error.
      return nullptr;
    }

    return &data_[top_-1];
  }

  const T* Top() const {
    if (top_ == 0) {
      // TODO(cschuet): Handle error.
      return nullptr;
    }

    return &data_[top_-1];
  }

 private:
  T* data_;
  size_t max_items_;
  size_t top_;

  DISALLOW_COPY_AND_ASSIGN(Stack);
};

}  // namespace base

#endif  // BASE_MEMORY_STACK_H_
