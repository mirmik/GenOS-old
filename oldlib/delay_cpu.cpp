
extern "C" volatile void delay_cpu (unsigned long long d)
{volatile unsigned long long ddd;
ddd=d;
while(1){
ddd--;
if ( ddd == 0) return;
}
};

