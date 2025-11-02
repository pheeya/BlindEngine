#ifndef BE_LOGGER
#define BE_LOGGER

typedef struct BeLogger {
  char* name;
  char* prefix;
} BeLogger;

enum BeLogTypeId {
BE_LOG_TRACE,
BE_LOG_DEBUG,
BE_LOG_INFO,
BE_LOG_WARN,
BE_LOG_ERROR,
BE_LOG_FATAL
};

#define BE_MAX_LOGGER_CHARS 512

void be_log(BeLogger* _logger, enum BeLogTypeId _logType, const char *fmt, ...);
#endif
