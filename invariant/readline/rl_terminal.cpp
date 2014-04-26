
#include "readline/rl_terminal.h"







/*
// print buffer content on screen
void ring_history_t::print_hist ()
{
	printf ("\n");
	for (int i = 0; i < _RING_HISTORY_LEN; i++) {
		if (i == this->begin)
			printf ("b");
		else 
			printf (" ");
	}
	printf ("\n");
	for (int i = 0; i < _RING_HISTORY_LEN; i++) {
		if (isalpha(this->ring_buf[i]))
			printf ("%c", this->ring_buf[i]);
		else 
			printf ("%d", this->ring_buf[i]);
	}
	printf ("\n");
	for (int i = 0; i < _RING_HISTORY_LEN; i++) {
		if (i == this->end)
			printf ("e");
		else 
			printf (" ");
	}
	printf ("\n");
}*/

//*****************************************************************************
// remove older message from ring buffer
void ring_history_t::hist_erase_older ()
{
	int new_pos = this->begin + this->ring_buf [this->begin] + 1;
	if (new_pos >= _RING_HISTORY_LEN)
		new_pos = new_pos - _RING_HISTORY_LEN;
	
	this->begin = new_pos;
}

//*****************************************************************************
// check space for new line, remove older while not space
int ring_history_t::hist_is_space_for_new (int len)
{
	if (this->ring_buf [this->begin] == 0)
		return true;
	if (this->end >= this->begin) {
		if (_RING_HISTORY_LEN - this->end + this->begin - 1 > len)
			return true;
	}	else {
		if (this->begin - this->end - 1> len)
			return true;
	}
	return false;
}

//*****************************************************************************
// put line to ring buffer
void ring_history_t::hist_save_line (char * line, int len)
{
	if (len > _RING_HISTORY_LEN - 2)
		return;
	while (!hist_is_space_for_new (len)) {
		hist_erase_older ();
	}
	// if it's first line
	if (this->ring_buf [this->begin] == 0) 
		this->ring_buf [this->begin] = len;
	
	// store line
	if (len < _RING_HISTORY_LEN-this->end-1)
		memcpy (this->ring_buf + this->end + 1, line, len);
	else {
		int part_len = _RING_HISTORY_LEN-this->end-1;
		memcpy (this->ring_buf + this->end + 1, line, part_len);
		memcpy (this->ring_buf, line + part_len, len - part_len);
	}
	this->ring_buf [this->end] = len;
	this->end = this->end + len + 1;
	if (this->end >= _RING_HISTORY_LEN)
		this->end -= _RING_HISTORY_LEN;
	this->ring_buf [this->end] = 0;
	this->cur = 0;
}

//*****************************************************************************
// copy saved line to 'line' and return size of line
int ring_history_t::hist_restore_line (char * line, int dir)
{
	int cnt = 0;
	// count history record	
	int header = this->begin;
	while (this->ring_buf [header] != 0) {
		header += this->ring_buf [header] + 1;
		if (header >= _RING_HISTORY_LEN)
			header -= _RING_HISTORY_LEN; 
		cnt++;
	}

	if (dir == _HIST_UP) {
		if (cnt >= this->cur) {
			int header = this->begin;
			int j = 0;
			// found record for 'this->cur' index
			while ((this->ring_buf [header] != 0) && (cnt - j -1 != this->cur)) {
				header += this->ring_buf [header] + 1;
				if (header >= _RING_HISTORY_LEN)
					header -= _RING_HISTORY_LEN;
				j++;
			}
			if (this->ring_buf[header]) {
					this->cur++;
				// obtain saved line
				if (this->ring_buf [header] + header < _RING_HISTORY_LEN) {
					memset (line, 0, _COMMAND_LINE_LEN);
					memcpy (line, this->ring_buf + header + 1, this->ring_buf[header]);
				} else {
					int part0 = _RING_HISTORY_LEN - header - 1;
					memset (line, 0, _COMMAND_LINE_LEN);
					memcpy (line, this->ring_buf + header + 1, part0);
					memcpy (line + part0, this->ring_buf, this->ring_buf[header] - part0);
				}
				return this->ring_buf[header];
			}
		}
	} else {
		if (this->cur > 0) {
				this->cur--;
			int header = this->begin;
			int j = 0;

			while ((this->ring_buf [header] != 0) && (cnt - j != this->cur)) {
				header += this->ring_buf [header] + 1;
				if (header >= _RING_HISTORY_LEN)
					header -= _RING_HISTORY_LEN;
				j++;
			}
			if (this->ring_buf [header] + header < _RING_HISTORY_LEN) {
				memcpy (line, this->ring_buf + header + 1, this->ring_buf[header]);
			} else {
				int part0 = _RING_HISTORY_LEN - header - 1;
				memcpy (line, this->ring_buf + header + 1, part0);
				memcpy (line + part0, this->ring_buf, this->ring_buf[header] - part0);
			}
			return this->ring_buf[header];
		} else {
			/* empty line */
			return 0;
		}
	}
	return -1;
}















inline void rl_terminal::terminal_backspace ()
{
	strm->print ("\033[D \033[D");
}


inline void rl_terminal::terminal_char (char c)
{
	strm->write (c);
}


inline void rl_terminal::terminal_write (char* c, int len)
{
	strm->write (c,len);
}

#include "GenOS.h"
void	rl_terminal::print_prompt()
{
	strm->print("\033[36m"); strm->print(MACHINE_NAME); strm->print(":");strm->print("\033[0m");
}


	rl_terminal::rl_terminal(Stream* _strm,readline_t* _rl)
	{init(_strm,_rl);}
	
   void	rl_terminal::init(Stream* _strm,readline_t* _rl)
	{strm=_strm; rl=_rl; mode=0;}

#include "intcom/command_list.h"
   void	rl_terminal::new_line_handler()
   {Stream* strmtemp=stdio;
	stdio=strm;
	char* str=rl->get_line();
	if (rl->cmdlen > 0)
	ring_hist.hist_save_line (str, rl->cmdlen);
	
	execute(str);
	stdio=strmtemp;
	print_prompt();
	
	ring_hist.cur = 0;
	rl->init();
	}




//#define terminal_print_line(a,b);  

   void	rl_terminal::listen()
	{
		if (mode==0) {print_prompt();mode=1;}
		
		int c;
		c= strm->read();
		if (c!=-1) {
			
			
			if (escape) {
		if (escape_process(c))
			escape = 0;
	} else 
{
			
		switch(c){			
			
		case KEY_CR:
		break;
		case KEY_LF:
			terminal_char('\n');
			new_line_handler();
		break;		
		
		case KEY_ESC:
				escape = 1;
		break;
			//-----------------------------------------------------
			case KEY_NAK: // ^U
					//while (cursor > 0) {
					rl->backspace ();
				
				//terminal_print_line (0, this->cursor);
			break;
			//-----------------------------------------------------
			case KEY_VT:  // ^K
				//this->print ("\033[K");
				//this->cmdlen = this->cursor;
			break;
			//-----------------------------------------------------
			case KEY_ENQ: // ^E
				//terminal_move_cursor (this->cmdlen-this->cursor);
				//this->cursor = this->cmdlen;
			break;
			//-----------------------------------------------------
			case KEY_SOH: // ^A
				//terminal_reset_cursor ();
				//this->cursor = 0;
			break;
			//-----------------------------------------------------
			case KEY_ACK: // ^F
			//if (this->cursor < this->cmdlen) {
				//terminal_move_cursor (1);
				//this->cursor++;
			//}
			break;
			//-----------------------------------------------------
			case KEY_STX: // ^B
			//if (this->cursor) {
				//terminal_move_cursor (-1);
				//this->cursor--;
			
			break;
			//-----------------------------------------------------
			
		
		
		
		
		
			case KEY_DLE: //^P
//			hist_search (_HIST_UP);
			break;
			//-----------------------------------------------------
			case KEY_SO: //^N
//			hist_search (_HIST_DOWN);
			break;
			//-----------------------------------------------------
			case KEY_DEL: // Backspace
			case KEY_BS: // ^U
				rl->backspace ();
	//			terminal_print_line (this->cursor, this->cursor);
			break;

			case KEY_ETX:
			//if (this->sigint != NULL)
			//	this->sigint();
			break;

		
		
		
		default:
		rl->insert_char((char)c);	
		
		if (rl->cmdlen != rl->cursor) terminal_rewrite();
		else terminal_char(c);
		}
	}
}}

void rl_terminal::terminal_rewrite(){
terminal_write(rl->cmdline + rl->cursor - 1, rl->cmdlen - rl->cursor +1);
terminal_move_cursor(-rl->cmdlen + rl->cursor);
}		


//*****************************************************************************
// set cursor at position from begin cmdline (after prompt) + offset
void rl_terminal::terminal_move_cursor (int offset)
{
	if (offset==0) return;
	strm->print ("\033[");
	strm->print (abs(offset));
	if (offset > 0) strm->print ("C");
	if (offset < 0) strm->print ("D");
}


// handling escape sequences
int rl_terminal::escape_process (char ch)
{
	if (ch == '[') {
		escape_seq = _ESC_BRACKET;
		return 0;
	} else if (escape_seq == _ESC_BRACKET) {
		if (ch == 'A') {
			hist_search (_HIST_UP);
			return 1;
		} else if (ch == 'B') {
			hist_search (_HIST_DOWN);
			return 1;
		} else if (ch == 'C') {
			//if (cursor < cmdlen) {
				terminal_move_cursor (rl->move_cursor(1));
				//cursor++;
			//}
			return 1;
		} else if (ch == 'D') {
			//if (cursor > 0) {
				terminal_move_cursor (rl->move_cursor(-1));
				//cursor--;
			//}
			return 1;
		} else if (ch == '7') {
			//escape_seq = _ESC_HOME;
			return 0;
		} else if (ch == '8') {
			//escape_seq = _ESC_END;
			return 0;
		} 
	} else if (ch == '~') {
		if (escape_seq == _ESC_HOME) {
			//terminal_reset_cursor ();
			//cursor = 0;
			return 1;
		} else if (escape_seq == _ESC_END) {
			//terminal_move_cursor (cmdlen-cursor);
			//cursor = cmdlen;
			return 1;
		}
	}
}

void rl_terminal::hist_search (int dir)
{
	int len = ring_hist.hist_restore_line (rl->cmdline, dir);
	if (len >= 0) {
		terminal_move_cursor(- rl->cursor);
		rl->cursor = rl->cmdlen = len;
	
		strm->print ("\033[K");
		strm->print(rl->get_line());
	}
}
