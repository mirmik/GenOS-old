#ifndef GENOSLIB_H
#define GENOSLIB_H


#include "types.h"
#ifndef NULL
#define NULL 0
#endif

size_t strlen(const char *c);

void swap_char(char* a, char* b);
void num2base_str(char* dec_str, uint32_t value, int base);
void str_reverse(char* str);
int scan2ascii(int scan);

void strformat(char* str, int n, char c);
char* strcpy(char * __dest, const char * __src);
int  strcmp(const char * __s1, const char * __s2);
void* memmove(void * __dest, const void * __src, size_t __n);
void* memcpy(void * __dest, const void * __src, size_t __n);
void* memset(void *__s,int __c, size_t __n);

#endif
