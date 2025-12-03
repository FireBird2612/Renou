#ifndef __U_LOG_H__
#define __U_LOG_H__

#include <stdint.h>
#include <stddef.h>

typedef enum {
  ULOG_INFO,
  ULOG_WARN,
  ULOG_ERROR
} ulog_level_t;

void ulog_init(void);
void ulog_log(ulog_level_t log_level, const char *fmt);

#endif
