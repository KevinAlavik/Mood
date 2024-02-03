#include "logger.h"
#include <stdarg.h> 

void mood_log(FILE* stream, const char* tag, const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stream, "[%s] ", tag);
    vfprintf(stream, format, args);
    fprintf(stream, "\n");
    va_end(args);
}