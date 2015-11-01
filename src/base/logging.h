// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#ifndef BASE_LOGGING_H_
#define BASE_LOGGING_H_

#if defined(NDEBUG) && !defined(DCHECK_ALWAYS_ON)
#define DCHECK_IS_ON() 0
#else
# DCHECK_IS_ON() 1
#endif


// Helper macro which avoids evaluating the arguments to a stream if
// the condition doesn't hold. Condition is evaluated once and only once.
#define LAZY_STREAM(stream, condition)                                  \
  !(condition) ? (void) 0 : ::logging::LogMessageVoidify() & (stream)

#define DCHECK(condition)                                                \
  LAZY_STREAM(LOG_STREAM(DCHECK), DCHECK_IS_ON() ? !(condition) : false) \
      << "Check failed: " #condition ". "

#endif  // BASE_LOGGING_H_
