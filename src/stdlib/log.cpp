/*
 * ================================
 * eli960@163.com
 * http://www.mailhonor.com/
 * 2016-11-13
 * ================================
 */

#include "zcc.h"

namespace zcc
{
static volatile int fatal_times = 0;
static void vprintf_default(const char *source_fn, size_t line_number, const char *fmt, va_list ap);

static void vprintf_default(const char *source_fn, size_t line_number, const char *fmt, va_list ap)
{
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, " [%s:%zu]\n", source_fn, line_number);
}
void (*log_vprintf) (const char *source_fn, size_t line_number, const char *fmt, va_list ap) = vprintf_default;

void log_info(const char *source_fn, size_t line_number, const char *fmt, ...)
{
    va_list ap;
    if (log_vprintf) {
        va_start(ap, fmt);
        log_vprintf(source_fn, line_number, fmt, ap);
        va_end(ap);
    }
}

void log_fatal(const char *source_fn, size_t line_number, const char *fmt, ...)
{
    va_list ap;

    if (fatal_times++ == 0) {
        if (log_vprintf) {
            va_start(ap, fmt);
            log_vprintf(source_fn, line_number, fmt, ap);
            va_end(ap);
        }
    }

    if (var_log_fatal_catch) {
        /* 段错误,方便 gdb 调试 */
        char *p = 0;
        *p = 0;
    }

    _exit(1);
}

}
