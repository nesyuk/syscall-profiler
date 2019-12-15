#ifndef OPS_LOGGER
#define OPS_LOGGER

#include <stdio.h>
#include <string.h>

#include "opsconfig.h"
#include "opslib.h"

void log_stats(const char *msg);
void log_error(const char *msg);
void log_msg(const char *msg);

#endif
