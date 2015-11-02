// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#ifndef BASE_LOGGING_H_
#define BASE_LOGGING_H_

#include <sstream>

#include "base/macros.h"

namespace logging {

#if defined(NDEBUG) && !defined(DCHECK_ALWAYS_ON)
#define DCHECK_IS_ON() 0
#else
#define DCHECK_IS_ON() 1
#endif

#define DCHECK(condition)                                                \
  LAZY_STREAM(LOG_STREAM(FATAL), DCHECK_IS_ON() ? !(condition) : false) \
      << "Check failed: " #condition ". "

typedef int LogSeverity;

const LogSeverity LOG_INFO = 0;
const LogSeverity LOG_WARNING = 1;
const LogSeverity LOG_ERROR = 2;
const LogSeverity LOG_FATAL = 3;

#define LOG_IS_ON(severity) \
  ((::logging::LOG_ ## severity) >= ::logging::GetMinLogLevel())

#define LAZY_STREAM(stream, condition) \
  !(condition) ? (void)0 : ::logging::LogMessageVoidify() & (stream)

#define LOG(severity) LAZY_STREAM(LOG_STREAM(severity), LOG_IS_ON(severity))

#define LOG_STREAM(severity) \
  ::logging::LogMessage(__FILE__, __LINE__, logging::LOG_ ## severity).stream()

// Sets the log level. Anything at or above this level will be written to the
// log file/displayed to the user (if applicable). Anything below this level
// will be silently ignored. The log level defaults to 0 (everything is logged
// up to level INFO) if this function is not called.
void SetMinLogLevel(int level);

// Gets the current log level.
int GetMinLogLevel();

class LogMessage {
 public:
  LogMessage(const char* file, int line, LogSeverity severity); 
  ~LogMessage();

  std::ostream& stream() { return stream_; }
 private:
  // Generates the message header (including source file and line number).
  void Init(const char* file, int line);

  // Severity of the message.
  LogSeverity severity_;

  // The output stringstream message will be piped into.
  std::ostringstream stream_;

  DISALLOW_COPY_AND_ASSIGN(LogMessage);
};

// This class is used to explicitly ignore values in the conditional
// logging macros.  This avoids compiler warnings like "value computed
// is not used" and "statement has no effect".
class LogMessageVoidify {
 public:
  LogMessageVoidify() { }
  // This has to be an operator with a precedence lower than << but
  // higher than ?:
  void operator&(std::ostream&) {}
};

}  // namespace logging 

#endif  // BASE_LOGGING_H_
