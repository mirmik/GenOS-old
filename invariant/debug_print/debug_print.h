
//#include "platform.h"
//#include "genoslib.h"
#include <inttypes.h>
#include <stdio.h> // for size_t
//#include "delay.h"

#define dpr_tab() {debug_putchar('\t');}
#define dwr(a,b) {debug_write(a,b);}
#define dpr_inthex(a) debug_printhex_int32((int32_t)a)
#define printd(a) {debug_print(a);}
#define dpr_str(a) {debug_print(a);}
#define dpr(a) {debug_print(a);}
#define dpc(a) {debug_putchar(a);}


extern "C" void debug_putchar(char c);
extern "C" void debug_write(const char*c,int i);
extern "C" void debug_printhex_halfbyte(char b);
extern "C" void debug_printhex_byte (char b);
extern "C" void debug_printhex_int32(int32_t a);
extern "C" void debug_printhex_int16(int16_t a);
extern "C" int debug_strlen(const char *c);
extern "C" void debug_print(const char *c);
extern "C" void debug_print_test();
extern "C" void debug_print_memory_as_byte(int64_t start,int64_t count);
extern "C" void debug_print_memory_as_char(int64_t start,int64_t count);
extern "C" void debug_print_dump(void* address, uint32_t size);


#define dln debug_write("\r\n",2);
