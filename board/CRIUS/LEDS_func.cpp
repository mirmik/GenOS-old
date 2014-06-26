
#include "CRIUS.h"

// ************************************************************************************************************
// LED func
// ************************************************************************************************************

void CRIUS_cls::leds_init()
{
  pinMode(LED_RED,1);
  pinMode(LED_GREEN,1);
  pinMode(LED_YELLOW,1);
}

void rnd_h()
{static int a;static int b=0;
a=(++a)%3;
switch(a){
case 0: {digitalWrite(13,b);break;}
case 2: {digitalWrite(30,b);b=(b+1)%2;break;}
case 1: {digitalWrite(31,b);break;}
}
}

/*
void ledround(char* c)
{static timer_t* t;
if (!strcmp(c,"off")) {SH.deleteTimer(t);t=0;ledoff(""); return;};
if (t==0) t=SH.newTimer(rnd_h,200,REPEAT);}
*/

/*void mountfs()
{
	//FileSystem_init();
}*/


void ledon(int argc, const char* const* argv)
{
if (argv[1]==0) CRIUS.all_leds_on();
else 
{
if (!strcmp("red",argv[1])){digitalWrite(13,1); goto ex;}
if (!strcmp("yellow",argv[1])){digitalWrite(31,1);goto ex;}
if (!strcmp("green",argv[1])){digitalWrite(30,1);goto ex;}
}
ex:return;
}


void ledoff(char *c)
{CRIUS.all_leds_off();}

