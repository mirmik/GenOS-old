
#include "platform.h"

void debug_putchar(char c);

void debug_write(const char*c,int i);
void debug_printhex_halfbyte(char b);
void debug_printhex_byte (char b);
void debug_printhex_int32(int32_t a);
void debug_printhex_int16(int16_t a);
int debug_strlen(const char *c);
void debug_print(const char *c);
void debug_print_test();
void debug_print_memory_as_byte(int64_t start,int64_t count);
void debug_print_memory_as_char(int64_t start,int64_t count);
