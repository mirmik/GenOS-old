#ifndef __EXPORTS_H__
#define __EXPORTS_H__

#ifndef __ASSEMBLY__

typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;
 
 
#ifdef __cplusplus
extern "C" {
#endif
//#include <stdarg.h>
/* These are declarations of exported functions available in C code */
unsigned long get_version(void);
//int  getc(void);
int  tstc(void);
//int putc(const char);
int puts(const char*);
int printf(const char* fmt, ...);
void install_hdlr(int, void (*interrupt_handler_t)(void *), void*);
void free_hdlr(int);
void __udelay(unsigned long);
unsigned long get_timer(unsigned long);
int vprintf(const char *, va_list);
unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base);
int strict_strtoul(const char *cp, unsigned int base, unsigned long *res);
//char *getenv (const char *name);
//int setenv (const char *varname, const char *varvalue);
long simple_strtol(const char *cp,char **endp,unsigned int base);
unsigned long ustrtoul(const char *cp, char **endp, unsigned int base);
unsigned long long ustrtoull(const char *cp, char **endp, unsigned int base);


#ifdef __cplusplus
}
#endif

void app_startup(char * const *);

#endif    /* ifndef __ASSEMBLY__ */


#endif	/* __EXPORTS_H__ */
