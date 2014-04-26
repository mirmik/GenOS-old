
#ifndef _READLINE_H_
#define _READLINE_H_

#undef ENDL
#define ENDL '\n'


#define true  1
#define false 0

// microrl struct, contain internal library data
class  readline_t
{public:
char cmdline[50];
int cursor;
int cmdlen;
//int (*execute)(int, const char* const*);

char* get_line();	
//void split();
void backspace ();
int move_cursor (int offset);
				
				
readline_t();
void init();
void insert_char(char c);
void insert_text(char* c);
void set_execute_callback (int (*_execute)(int, const char* const*));
};
#endif
