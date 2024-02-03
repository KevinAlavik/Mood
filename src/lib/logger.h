#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>

void mood_log(FILE* stream, const char* tag, const char* format, ...);

#endif // __LOGGER_H__
