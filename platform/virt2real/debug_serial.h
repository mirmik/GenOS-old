#ifndef DEBUG_SERIAL_H
#define DEBUG_SERIAL_H
#include <inttypes.h>


#define dln {debug_serial_putchar('\r');debug_serial_putchar('\n');}
#define dln_c {debug_serial_putchar_c('\r');debug_serial_putchar_c('\n');}
#define dtab {debug_serial_putchar('\t');}
#define dpr_inthex debug_serial_printhex_int
#define dtab_c {debug_serial_putchar_c('\t');}
#define dpr_inthex_c debug_serial_printhex_int_c



void printd(const char *c);

void debug_serial_putchar(char c);
void debug_serial_printhex_int(int a);


void debug_serial_write_c(const char* c, int a);
void printd_c(const char* c);





#endif
