// Copyright 2015 Christoph Schuette. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file.

#include <cstdlib>
#include <iostream>

#include "base/debug/stack_trace.h"
#include "base/logging.h"

namespace logging {

int g_min_log_level = 0;

void SetMinLogLevel(int level) {
  g_min_log_level = std::min(LOG_FATAL, level);
}

int GetMinLogLevel() {
  return g_min_log_level;
}

LogMessage::LogMessage(const char* file, int line, LogSeverity severity)
    : severity_(severity) {
  Init(file, line);
}

void LogMessage::Init(const char* file, int line) {
  stream_ << file << " : " << line << " -- ";
}

LogMessage::~LogMessage() {
  // For log message with a severity of LOG_FATAL generate a StackTrace.
  if (severity_ == LOG_FATAL) {
    base::StackTrace trace;
    stream_ << std::endl;
    trace.OutputToStream(&stream_);
  }

  std::cout << stream_.str() << std::endl;

  if (severity_ == LOG_FATAL)
    abort();
}

}  // namespace logging
