#ifndef __U_LOG_H__
#define __U_LOG_H__

#include <stdint.h>
#include <stddef.h>

typedef enum {
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR
} ulog_level_t;

void ulog_init(void);
void ulog_log(ulog_level_t log_level, const char *fmt);

/*  Macros for using the ulog  */
#define ULOG_INFO(fmt) ulog_log(LOG_INFO, fmt)
#define ULOG_WARN(fmt) ulog_log(LOG_WARN, fmt)
#define ULOG_ERROR(fmt) ulog_log(LOG_ERROR, fmt)

#endif
