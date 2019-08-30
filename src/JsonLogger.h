#ifndef json_builder_h
#define json_builder_h

// stuff you should know
#define json(buf, ...) build_json(buf, sizeof(buf), __VA_ARGS__, NULL)     // returns json length if all good, negative number if error
#define jsonHeap(buf, size, ...) build_json(buf, size, __VA_ARGS__, NULL)  // same as json() but user supplies buffer size for malloc-ed buffer

#ifdef __cplusplus
extern "C" {
#endif

void logAddSender(void (*sender)(int level, const char* json));

#ifdef __cplusplus
}
#endif

#define logFatal(...) logJson(LEVEL_FATAL, __VA_ARGS__)
#define logError(...) logJson(LEVEL_ERROR, __VA_ARGS__)
#define logWarn(...) logJson(LEVEL_WARN, __VA_ARGS__)
#define logInfo(...) logJson(LEVEL_INFO, __VA_ARGS__)
#define logDebug(...) logJson(LEVEL_DEBUG, __VA_ARGS__)
#define logTrace(...) logJson(LEVEL_TRACE, __VA_ARGS__)

#ifndef LOG_TIME_VALUE
// You should define LOG_TIME_VALUE (e.g. -DLOG_TIME_VALUE=System.getDateTime()) which is used to log time string
#define LOG_TIME_VALUE "1970-01-01T00:00:00Z"
#endif

//#define LOG_ID_VALUE ( "value" or getId() )if you want to log an ID

#define JSON_ERR_BUF_SIZE -1

#ifndef EMPTY_KEY
#define EMPTY_KEY "_"
#endif

#ifndef LOG_MIN_LEVEL
#define LOG_MIN_LEVEL 1
#endif

#ifndef LOG_MAX_LEN
#define LOG_MAX_LEN 512
#endif

#ifndef LOG_ID_KEY
#define LOG_ID_KEY "i"
#endif

#ifndef LOG_TIME_KEY
#define LOG_TIME_KEY "t"
#endif

#ifndef LOG_LEVEL_KEY
#define LOG_LEVEL_KEY "l"
#endif

#ifndef LOG_SOURCE_KEY
#define LOG_SOURCE_KEY "s"
#endif

#ifndef LOG_FUNC_KEY
#define LOG_FUNC_KEY "f"
#endif

// stuff you shouldn't know
#define LEVEL_FATAL 5
#define LEVEL_ERROR 4
#define LEVEL_WARN 3
#define LEVEL_INFO 2
#define LEVEL_DEBUG 1
#define LEVEL_TRACE 0

#define logJson(level, ...) \
  if (level >= LOG_MIN_LEVEL) log_json(level, "", "s", __FILE__ ":" TOSTRING(__LINE__), "f", __func__, __VA_ARGS__, NULL)

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int build_json(char* json, size_t buf_size, const char* item, ...);
int vbuild_json(char* json, size_t buf_size, const char* item, va_list args);

void log_json(int level, const char* placeholder, ...);

char* str_replace(char* orig, char* rep, char* with);

#ifdef __cplusplus
}
#endif

#endif  // json_builder_h
