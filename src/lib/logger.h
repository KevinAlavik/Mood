#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>

#ifdef DEBUG_LOGGING
#define DEBUG_LOG(...) mood_log(stdout, "Mood Debug", __VA_ARGS__)
#else
#define DEBUG_LOG(...) ((void)0)
#endif

void mood_log(FILE* stream, const char* tag, const char* format, ...);

#endif // __LOGGER_H__
