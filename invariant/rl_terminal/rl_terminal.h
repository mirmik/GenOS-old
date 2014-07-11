#ifndef RL_TERMINAL_H
#define RL_TERMINAL_H


#include "KeyCom.h"
#include "readline.h"

// direction of history navigation
#define _HIST_UP   0
#define _HIST_DOWN 1

#define _COMMAND_LINE_LEN 50
#define _RING_HISTORY_LEN 256

class ring_history_t{
	public:
	char ring_buf [_RING_HISTORY_LEN];
	int begin;
	int end;
	int cur;
void hist_erase_older ();
int hist_is_space_for_new (int len);
void print_hist ();
void hist_save_line (char * line, int len);
int hist_restore_line (char * line, int dir);
} ;

class rl_terminal : public KeyCom{
	public:
	readline_t* rl; 	
	KeyCom* echo;
	int mode;
	void hist_search (int dir);
	ring_history_t ring_hist;
	
	size_t write(uint8_t);
	int left	(int i);
	int right	(int i);
	int up	(int i);
	int down	(int i);
	int del	(int i);
	
	void rl_rewrite();
	void	print_prompt();
	rl_terminal(readline_t* _rl,KeyCom* _echo=0);
	void init(readline_t* _rl,KeyCom* _echo=0);
	};

#endif
