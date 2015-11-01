// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#include "base/debug/stack_trace.h"

#include <cxxabi.h>
#include <execinfo.h>

namespace base {

namespace {

const int kMaxFrames = 32;
const char kMangledSymbolPrefix[] = "_Z";
const char kSymbolCharacters[] =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";

void DemangleSymbols(std::string* text) {
  std::string::size_type search_from = 0;
  while (search_from < text->size()) {
    // Look for the start of a mangled symbol, from search_from.
    std::string::size_type mangled_start =
        text->find(kMangledSymbolPrefix, search_from);
    if (mangled_start == std::string::npos) {
      break;  // Mangled symbol not found.
    }

    // Look for the end of the mangled symbol.
    std::string::size_type mangled_end =
        text->find_first_not_of(kSymbolCharacters, mangled_start);
    if (mangled_end == std::string::npos) {
      mangled_end = text->size();
    }
    std::string mangled_symbol =
        text->substr(mangled_start, mangled_end - mangled_start);

    // Try to demangle the mangled symbol candidate.
    int status = 0;
    std::string demangled_symbol =
        abi::__cxa_demangle(mangled_symbol.c_str(), NULL, 0, &status);
    if (status == 0) {  // Demangling is successful.
      // Remove the mangled symbol.
      text->erase(mangled_start, mangled_end - mangled_start);
      // Insert the demangled symbol.
      text->insert(mangled_start, demangled_symbol);
      // Next time, we'll start right after the demangled symbol we inserted.
      search_from = mangled_start + demangled_symbol.size();
    } else {
      // Failed to demangle.  Retry after the "_Z" we just found.
      search_from = mangled_start + 2;
    }
  }
}

}  // namespace

StackTrace::StackTrace() : trace_(new void*[kMaxFrames])  {
  count_ = backtrace(trace_, kMaxFrames);
}

StackTrace::~StackTrace() {
  delete [] trace_;
}

void StackTrace::OutputToStream(std::ostream* os) const {
  char **strings;
  strings = backtrace_symbols(trace_, count_);
  for (int j = 0; j < count_; j++) {
    std::string backtrace_symbol = strings[j];
    DemangleSymbols(&backtrace_symbol);
    *os << backtrace_symbol << std::endl;
  }
}

}  // namespace base
