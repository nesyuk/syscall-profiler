#ifndef OPS_LOGGER
#define OPS_LOGGER

#include <string.h>
#include <stdio.h>

#include "opslib.h"
#include "opsconfig.h"

void log_stats(const char *msg);
void log_error(const char *msg);
void log_msg(const char *msg);

#endif
