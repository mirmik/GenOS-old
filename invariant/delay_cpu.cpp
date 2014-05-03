
extern "C" volatile void delay_cpu (unsigned int d)
{volatile unsigned long long dd;
	dd=d*2000;
while(1){
asm("nop");
dd--;
if ( dd == 0) return;
}
};

