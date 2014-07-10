
#include "genoslib/genoslib.h"
#include "genoslib/string.h"

#define num2base_char(a) ((a < 10) ? a + '0' : a + 'A' - 10)
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

void strformat(char* str, int n,char c)
{
int l=strlen(str);
if (l<n) strcpy(str+n-l,str);
for (int i=0;i<(n-l);i++) *(str+i)=c;
}


int limitation(int a,int min,int max){
		if (a<min) return min;
		if (a>max) return max;
		return a;
	}

uint64_t factorial[16]={1,1,2,6,24,120,720,5040,40320,362880,3628800,
	39916800,479001600,6227020800,87178291200};

	
float exp(float x, int iter)
{
float _x=x;
float sum=1+x,prevsum=x;
uint i=1;

	//while (abs(sum-prevsum) > eps)
	while(iter--)
		{
		prevsum=sum;
		i++;
		_x=_x*x;
		sum=sum+_x/factorial[i];
		}	
return sum;
};


int abs( int __x){return (__x>0 ? __x : -__x);}
