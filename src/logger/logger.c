#include <log.c>
#include <logger/logger.h>
#include <stdarg.h>

void be_log(BeLogger *_logger, enum BeLogTypeId _logType, const char *fmt,
            ...) {
  va_list(args);
  va_start(args, fmt);

  char buf[BE_MAX_LOGGER_CHARS];

  int prefixLength = snprintf(buf, sizeof(buf), "[%s] ", _logger->prefix);
  vsnprintf(buf + prefixLength, sizeof(buf) - prefixLength, fmt, args);
  if (_logType == BE_LOG_TRACE) {
    log_trace(buf);
  } else if (_logType == BE_LOG_DEBUG) {
    log_debug(buf);
  } else if (_logType == BE_LOG_INFO) {
    log_info(buf);
  } else if (_logType == BE_LOG_ERROR) {
    log_error(buf);
  } else if (_logType == BE_LOG_FATAL) {
    log_fatal(buf);
  }
  va_end(args);
}
