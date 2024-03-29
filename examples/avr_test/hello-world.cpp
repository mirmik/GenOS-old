
#include "avr/io.h"
#include "platform.h"
#include "debug/debug.h"
#include "strm/StrmDebug.h"
#include "strm/DBStream.h"
#include "shed/u_esh.h"
#include "PrintTransformer/ASCII2KeyCom.h"
#include "PrintTransformer/KeyCom2ASCII.h"
#include "readline/rl_terminal.h"
#include "readline/readline.h"
#include "utility.h"
#include "intcom/command_list.h"
#include "CRIUS.h"
#include "shed/subst_shed.h"

int kkk=0;
TSH SH;

SubstShed S;

KeyCom2ASCII KCA(&Serial);
readline_t rl;
rl_terminal rt(&rl,&KCA);
ASCII2KeyCom AKC(&rt);

#define sbi(a,b) a|=(1<<b)
#define cbi(a,b) a&=~(1<<b)

extern HardwareSerial Serial;

Print* stdprint=&Serial;

void debug_putchar(char c){UDR0=c;delay(3);};

void blink1();
void blink(){SH.newTimer(blink1,500,ONCE);digitalWrite(13,1);};
void blink1(){SH.newTimer(blink,500,ONCE);digitalWrite(13,0);};

void task2()
{pr("p0");
	sysexecute("ledon green");
	pr("p1");
	S.change(0);
	pr("p2");
	S.change(0);	
	while(1);
};

uint8_t mas[200];
int main(){
	init();	
	pinMode(13,1);
	Serial.begin(9600);
CRIUS.leds_init();
	
	command("ledon",ledon);
	command("ledoff",ledoff);
	
	Serial.println("abcde12345abcde12345abcde12345abcde12345abcde12345");
	SH.newTimer(blink,500,ONCE);
	registry_standart_utility();
	
	
	S.create(mas,200,task2);
	S.change(1);
	pr("f2");
	S.change(1);
	while(1) 
	{//SH.start();
		
		
	int c=Serial.read(); if(c!=-1) AKC.write(c);
	};
	
	}




