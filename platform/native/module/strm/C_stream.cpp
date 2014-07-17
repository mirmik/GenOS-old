



#include "C_stream.h"
#include "stdio.h"
#include "string.h"

C_stream_t term;

	
size_t C_stream_t::write(uint8_t c)
{putchar(c);}


 int C_stream_t::available(){};
 int C_stream_t::read(){return(fgetc(stdin));};
 int C_stream_t::peek(){};
 void C_stream_t::flush(){};


int C_stream_t::begin()
{
	
    //int character;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);
	
	
	
}

int C_stream_t::end()
{
   tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);	
	
}
