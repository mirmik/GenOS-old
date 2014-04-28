#ifndef PLATFORM_H
#define PLATFORM_H


#include "time.h"
static unsigned long millis(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts );
    return ( ts.tv_sec * 1000 + ts.tv_nsec / 1000000L );
}


static unsigned long micros(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts );
    return ( ts.tv_sec * 1000000L + ts.tv_nsec / 1000L );
}

extern "C" void debug_putchar(char c);

#include "stdlib.h"
#define kmalloc(a) malloc(a)
#define kfree(a) free(a)

void SystemError_platform();

#endif
