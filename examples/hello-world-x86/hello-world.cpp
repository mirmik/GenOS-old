

char* videomem = (char*)0xB8000;
int cursor = 0;

struct videochar
{char c;
char f;};

void putchar(char c)
{
*(videomem + cursor * 2 + 1 ) = 10;
*(videomem + cursor * 2) = c;
cursor++; 
};



void outb(unsigned short port, unsigned char value)
{
asm volatile("outb %1, %0"::"dN"(port),"a"(value));
}

void move_cursor(unsigned char x, unsigned char y)
{
int cur = x + y*20;
outb(0x3D4, 0x0E);
outb(0x3D5, cur >> 8);
outb(0x3D4,0x0F);
outb(0x3D5,cur);
}

int main()
{
move_cursor(12,1);
putchar('M');
putchar('i');
putchar('r');
putchar('m');
putchar('i');
putchar('k');
putchar('\n');

return 0;
}
