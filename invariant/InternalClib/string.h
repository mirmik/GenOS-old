#ifndef _INTERNAL_LINUX_STRING_H_
#define _INTERNAL_LINUX_STRING_H_


#ifdef __cplusplus
extern "C" {
#endif

extern char * strcpy(char *,const char *);
extern char * strncpy(char *,const char *, __kernel_size_t);
extern char * strcat(char *, const char *);
extern char * strncat(char *, const char *, __kernel_size_t);
extern int strcmp(const char *,const char *);
extern int strncmp(const char *,const char *,__kernel_size_t);
int strcasecmp(const char *s1, const char *s2);
extern int strncasecmp(const char *s1, const char *s2, __kernel_size_t len);
extern char * strchr(const char *,int);
extern char * strrchr(const char *,int);
extern char * strstr(const char *,const char *);
extern size_t strlen(const char *);
extern size_t strnlen(const char *,__kernel_size_t);
extern char * strdup(const char *);
extern char * strswab(const char *);
extern void * memset(void *,int,__kernel_size_t);
extern void * memcpy(void *,const void *,__kernel_size_t);
extern void * memmove(void *,const void *,__kernel_size_t);
extern void * memscan(void *,int,__kernel_size_t);
extern int memcmp(const void *,const void *,__kernel_size_t);
extern void * memchr(const u8 *,int, size_t);
void *memchr_inv(const u8 *, int, size_t);

#ifdef __cplusplus
}
#endif

#endif /* _LINUX_STRING_H_ */
