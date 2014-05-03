
#include "genoslib.h"

#define num2base_char(a) ((a < 10) ? a + '0' : a + 'A' - 10)


size_t strlen(const char *c)
{size_t i=0;
while(*(c+i)!=0) i++;
return i;};

#include "debug/debug.h"
char* strcpy(char * __dest, const char * __src)
{	
memmove(__dest,__src,strlen(__src)+1);
return(__dest);
};

/*-----------------------------------------------
// Число в строку. base - основание системы счисления
//---------------------------------------------*/
void num2base_str(char* base_str  ,uint32_t value, int base)
{
  uint32_t mod = 0;
  uint32_t res = value;
  
  int i = 0;
  int j = 0;
 
  do /* Аналогично предыдущей функции переводим число в 10-ричный*/
  /* формат*/
  {
    mod = res % base;
    res = res / base;
   
    base_str[i] = num2base_char(mod);
    i++;
   
  } while (res >= base);
 
  /* Пишем последнюю цифру если она не ноль то из таблицы */
  if (res != 0 )
  {
    base_str[i] = num2base_char(res);
    base_str[++i] = '\0';
  }   
  else /* если же ноль - то завершаем строку */
    base_str[i] = '\0';
   
  /* Записываем полученную строку в результирующую */
  /* используя обратный порядок символов */
  //for (j = 0; j < i; j++)
   // base_str[j] = tmp_str[i-j-1];
  /* Завершаем строку */
  str_reverse(base_str);
}


#include "debug/debug.h"
void str_reverse(char* str)
{
int f = strlen(str);
for (int i = 0; i < f/2 ; i++)
swap_char(str+i,str+f-i-1);
}

void swap_char(char* a, char* b)
{
*a=*a ^ *b;
*b=*a ^ *b;
*a=*a ^ *b;	
}

#include "debug/debug.h"
void strformat(char* str, int n,char c)
{
int l=strlen(str);
if (l<n) strcpy(str+n-l,str);
for (int i=0;i<(n-l);i++) *(str+i)=c;
}


int strcmp(const char * s1, const char * s2)
{
	while(*s1 && *s2)
	{
	if (*s1 < *s2)
			return (-1);
	if (*s1 > *s2)
			return ( 1);
	s1++; s2++;		
	}
	return *s1 ? -1 : *s2 ? 1: 0 ;
}



void* memmove(void * _dest, const void * _src, size_t __n)
{char* __dest = (char*) _dest;
char* __src = (char*) _src;	
if (__dest > __src)	
{
char* __tmp = (char*)__src + __n - 1;
int offset =__dest - __src;
for(;__n;__n--) *(__tmp + offset) = *__tmp--;
return (__dest);
}
if (__dest < __src)	{
char* __tmp=__dest;
for(;__n;__n--) *__dest++ =*__src++;
return(__tmp);
}
if (__dest == __src) return(__dest);
}


void* memcpy(void * __dest, const void * __src, size_t __n)
{char * __cd = (char*)__dest;char * __cs = (char*)__src;
for (;__n;__n--) *__cd++ = *__cs++;
return(0);
}

void* memset(void *__s,int __c, size_t __n)
{for (;__n;__n--) 
	*((char*)(__s + __n - 1)) = (char)__c;
}
