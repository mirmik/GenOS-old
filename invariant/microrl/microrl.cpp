
/*
Author: Samoylov Eugene aka Helius (ghelius@gmail.com)
BUGS and TODO:
-- add echo_off feature
-- rewrite history for use more than 256 byte buffer
*/

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "microrl.h"
#ifdef _USE_LIBC_STDIO
#include <stdio.h>
#endif

//#define DBG(...) fprintf(stderr, "\033[33m");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\033[0m");

microrl_t::microrl_t ()
{
	prompt_str = _PROMPT_DEFAUTL;	
} 






#ifdef _USE_HISTORY

#ifdef _HISTORY_DEBUG
//*****************************************************************************
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
}
#endif

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
#ifdef _HISTORY_DEBUG
	print_hist (this);
#endif
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
#endif








//*****************************************************************************
// split cmdline to tkn array and return nmb of token
int microrl_t::split (int limit, char const ** tkn_arr)
{
	int i = 0;
	int ind = 0;
	while (1) {
		// go to the first whitespace (zerro for us)
		while ((this->cmdline [ind] == '\0') && (ind < limit)) {
			ind++;
		}
		if (!(ind < limit)) return i;
		tkn_arr[i++] = this->cmdline + ind;
		if (i >= _COMMAND_TOKEN_NMB) {
			return -1;
		}
		// go to the first NOT whitespace (not zerro for us)
		while ((this->cmdline [ind] != '\0') && (ind < limit)) {
			ind++;
		}
		if (!(ind < limit)) return i;
	}
	return i;
}


//*****************************************************************************
inline void microrl_t::print_prompt ()
{
	strm->print (this->prompt_str);
}

//*****************************************************************************
inline void microrl_t::terminal_backspace ()
{
		strm->print ("\033[D \033[D");
}

//*****************************************************************************
inline void microrl_t::terminal_newline ()
{
	strm->print (ENDL);
}

#ifndef _USE_LIBC_STDIO
//*****************************************************************************
// convert 16 bit value to string
// 0 value not supported!!! just make empty string
// Returns pointer to a buffer tail
static char *u16bit_to_str (unsigned int nmb, char * buf)
{
	char tmp_str [6] = {0,};
	int i = 0, j;
	if (nmb <= 0xFFFF) {
		while (nmb > 0) {
			tmp_str[i++] = (nmb % 10) + '0';
			nmb /=10;
		}
		for (j = 0; j < i; ++j)
			*(buf++) = tmp_str [i-j-1];
	}
	*buf = '\0';
	return buf;
}
#endif


//*****************************************************************************
// set cursor at position from begin cmdline (after prompt) + offset
void microrl_t::terminal_move_cursor (int offset)
{
	char str[16] = {0,};
#ifdef _USE_LIBC_STDIO 
	if (offset > 0) {
		snprintf (str, 16, "\033[%dC", offset);
	} else if (offset < 0) {
		snprintf (str, 16, "\033[%dD", -(offset));
	}
#else 
	char *endstr;
	strcpy (str, "\033[");
	if (offset > 0) {
		endstr = u16bit_to_str (offset, str+2);
		strcpy (endstr, "C");
	} else if (offset < 0) {
		endstr = u16bit_to_str (-(offset), str+2);
		strcpy (endstr, "D");
	} else
		return;
#endif	
	strm->print (str);
}

//*****************************************************************************
void microrl_t::terminal_reset_cursor ()
{
	char str[16];
#ifdef _USE_LIBC_STDIO
	snprintf (str, 16, "\033[%dD\033[%dC", \
						_COMMAND_LINE_LEN + _PROMPT_LEN + 2, _PROMPT_LEN);

#else
	char *endstr;
	strcpy (str, "\033[");
	endstr = u16bit_to_str ( _COMMAND_LINE_LEN + _PROMPT_LEN + 2,str+2);
	strcpy (endstr, "D\033["); endstr += 3;
	endstr = u16bit_to_str (_PROMPT_LEN, endstr);
	strcpy (endstr, "C");
#endif
	strm->print (str);
}

//*****************************************************************************
// print cmdline to screen, replace '\0' to wihitespace 
void microrl_t::terminal_print_line (int pos, int cursor)
{
	strm->print ("\033[K");    // delete all from cursor to end

	char nch [] = {0,0};
	int i;
	for (i = pos; i < this->cmdlen; i++) {
		nch [0] = this->cmdline [i];
		if (nch[0] == '\0')
			nch[0] = ' ';
		strm->print (nch);
	}
	
	terminal_reset_cursor ();
	terminal_move_cursor (cursor);
}

//*****************************************************************************
void microrl_t::init (Stream& _strm) 
{
	memset(this->cmdline, 0, _COMMAND_LINE_LEN);
#ifdef _USE_HISTORY
	memset(this->ring_hist.ring_buf, 0, _RING_HISTORY_LEN);
	this->ring_hist.begin = 0;
	this->ring_hist.end = 0;
	this->ring_hist.cur = 0;
#endif
	this->cmdlen =0;
	this->cursor = 0;
	this->execute = NULL;
	this->get_completion = NULL;
#ifdef _USE_CTLR_C
	this->sigint = NULL;
#endif
//	this->prompt_str = prompt_default;
	this->strm = &_strm;
#ifdef _ENABLE_INIT_PROMPT
	print_prompt ();
#endif
}

//*****************************************************************************
void microrl_t::set_complete_callback (char ** (*get_completion)(int, const char* const*))
{
	this->get_completion = get_completion;
}

//*****************************************************************************
void microrl_t::set_execute_callback (int (*execute)(int, const char* const*))
{
	this->execute = execute;
}
#ifdef _USE_CTLR_C
//*****************************************************************************
void microrl_t::set_sigint_callback (void (*sigintf)(void))
{
	this->sigint = sigintf;
}
#endif

#ifdef _USE_ESC_SEQ
void microrl_t::hist_search (int dir)
{
	int len = ring_hist.hist_restore_line (this->cmdline, dir);
	if (len >= 0) {
		this->cursor = this->cmdlen = len;
		terminal_reset_cursor ();
		terminal_print_line (0, this->cursor);
	}
}

//*****************************************************************************
// handling escape sequences
int microrl_t::escape_process (char ch)
{
	if (ch == '[') {
		this->escape_seq = _ESC_BRACKET;
		return 0;
	} else if (this->escape_seq == _ESC_BRACKET) {
		if (ch == 'A') {
#ifdef _USE_HISTORY
			hist_search (_HIST_UP);
#endif
			return 1;
		} else if (ch == 'B') {
#ifdef _USE_HISTORY
			hist_search (_HIST_DOWN);
#endif
			return 1;
		} else if (ch == 'C') {
			if (this->cursor < this->cmdlen) {
				terminal_move_cursor (1);
				this->cursor++;
			}
			return 1;
		} else if (ch == 'D') {
			if (this->cursor > 0) {
				terminal_move_cursor (-1);
				this->cursor--;
			}
			return 1;
		} else if (ch == '7') {
			this->escape_seq = _ESC_HOME;
			return 0;
		} else if (ch == '8') {
			this->escape_seq = _ESC_END;
			return 0;
		} 
	} else if (ch == '~') {
		if (this->escape_seq == _ESC_HOME) {
			terminal_reset_cursor ();
			this->cursor = 0;
			return 1;
		} else if (this->escape_seq == _ESC_END) {
			terminal_move_cursor (this->cmdlen-this->cursor);
			this->cursor = this->cmdlen;
			return 1;
		}
	}

	/* unknown escape sequence, stop */
	return 1;
}
#endif

//*****************************************************************************
// insert len char of text at cursor position
int microrl_t::insert_text (char * text, int len)
{
	int i;
	if (this->cmdlen + len < _COMMAND_LINE_LEN) {
		memmove (this->cmdline + this->cursor + len,
						 this->cmdline + this->cursor,
						 this->cmdlen - this->cursor);
		for (i = 0; i < len; i++) {
			this->cmdline [this->cursor + i] = text [i];
			if (this->cmdline [this->cursor + i] == ' ') {
				this->cmdline [this->cursor + i] = 0;
			}
		}
		this->cursor += len;
		this->cmdlen += len;
		this->cmdline [this->cmdlen] = '\0';
		return true;
	}
	return false;
}

//*****************************************************************************
// remove one char at cursor
void microrl_t::backspace ()
{
	if (this->cursor > 0) {
		terminal_backspace ();
		memmove (this->cmdline + this->cursor-1,
						 this->cmdline + this->cursor,
						 this->cmdlen-this->cursor+1);
		this->cursor--;
		this->cmdline [this->cmdlen] = '\0';
		this->cmdlen--;
	}
}


#ifdef _USE_COMPLETE

//*****************************************************************************
static int common_len (char ** arr)
{
	int len = 0;
	int i = 1;
	while (1) {
		while (arr[i]!=NULL) {
			if ((arr[i][len] != arr[i-1][len]) || 
					(arr[i][len] == '\0') || 
					(arr[i-1][len]=='\0')) 
				return len;
			len++;
		}
		i++;
	}
	return 0;
}

//*****************************************************************************
void microrl_t::get_complite () 
{
	char const * tkn_arr[_COMMAND_TOKEN_NMB];
	char ** compl_token; 
	
	if (this->get_completion == NULL) // callback was not set
		return;
	
	int status = split (this->cursor, tkn_arr);
	if (this->cmdline[this->cursor-1] == '\0')
		tkn_arr[status++] = "";
	compl_token = this->get_completion (status, tkn_arr);
	if (compl_token[0] != NULL) {
		int i = 0;
		int len;

		if (compl_token[1] == NULL) {
			len = strlen (compl_token[0]);
		} else {
			len = common_len (compl_token);
			terminal_newline ();
			while (compl_token [i] != NULL) {
				this->print (compl_token[i]);
				this->print (" ");
				i++;
			}
			terminal_newline ();
			print_prompt ();
		}
		
		if (len) {
			insert_text (compl_token[0] + strlen(tkn_arr[status-1]), 
																	len - strlen(tkn_arr[status-1]));
			if (compl_token[1] == NULL) 
				insert_text ((char*)" ", 1);
		}
		terminal_reset_cursor ();
		terminal_print_line (0, this->cursor);
	} 
}
#endif

//*****************************************************************************
void microrl_t::new_line_handler(){
	char const * tkn_arr [_COMMAND_TOKEN_NMB];
	int status;

	terminal_newline ();
#ifdef _USE_HISTORY
	if (this->cmdlen > 0)
		ring_hist.hist_save_line (this->cmdline, this->cmdlen);
#endif
	status = split (this->cmdlen, tkn_arr);
	if (status == -1){
		//          this->print ("ERROR: Max token amount exseed\n");
		this->print ("ERROR:too many tokens");
		this->print (ENDL);
	}
	if ((status > 0) && (this->execute != NULL))
		this->execute (status, tkn_arr);
	print_prompt ();
	this->cmdlen = 0;
	this->cursor = 0;
	memset(this->cmdline, 0, _COMMAND_LINE_LEN);
#ifdef _USE_HISTORY
	this->ring_hist.cur = 0;
#endif
}

//*****************************************************************************

void microrl_t::insert_char (int ch)
{
#ifdef _USE_ESC_SEQ
	if (this->escape) {
		if (escape_process(ch))
			this->escape = 0;
	} else {
#endif
		switch (ch) {
			//-----------------------------------------------------
#ifdef _ENDL_CR
			case KEY_CR:
				new_line_handler();
			break;
			case KEY_LF:
			break;
#elif defined(_ENDL_CRLF)
			case KEY_CR:
				this->tmpch = KEY_CR;
			break;
			case KEY_LF:
			if (this->tmpch == KEY_CR)
				new_line_handler();
			break;
#elif defined(_ENDL_LFCR)
			case KEY_LF:
				this->tmpch = KEY_LF;
			break;
			case KEY_CR:
			if (this->tmpch == KEY_LF)
				new_line_handler();
			break;
#else
			case KEY_CR:
			break;
			case KEY_LF:
				new_line_handler();
			break;
#endif
			//-----------------------------------------------------
#ifdef _USE_COMPLETE
			case KEY_HT:
				get_complite ();
			break;
#endif
			//-----------------------------------------------------
			case KEY_ESC:
#ifdef _USE_ESC_SEQ
				this->escape = 1;
#endif
			break;
			//-----------------------------------------------------
			case KEY_NAK: // ^U
					while (this->cursor > 0) {
					backspace ();
				}
				terminal_print_line (0, this->cursor);
			break;
			//-----------------------------------------------------
			case KEY_VT:  // ^K
				this->print ("\033[K");
				this->cmdlen = this->cursor;
			break;
			//-----------------------------------------------------
			case KEY_ENQ: // ^E
				terminal_move_cursor (this->cmdlen-this->cursor);
				this->cursor = this->cmdlen;
			break;
			//-----------------------------------------------------
			case KEY_SOH: // ^A
				terminal_reset_cursor ();
				this->cursor = 0;
			break;
			//-----------------------------------------------------
			case KEY_ACK: // ^F
			if (this->cursor < this->cmdlen) {
				terminal_move_cursor (1);
				this->cursor++;
			}
			break;
			//-----------------------------------------------------
			case KEY_STX: // ^B
			if (this->cursor) {
				terminal_move_cursor (-1);
				this->cursor--;
			}
			break;
			//-----------------------------------------------------
			case KEY_DLE: //^P
#ifdef _USE_HISTORY
			hist_search (_HIST_UP);
#endif
			break;
			//-----------------------------------------------------
			case KEY_SO: //^N
#ifdef _USE_HISTORY
			hist_search (_HIST_DOWN);
#endif
			break;
			//-----------------------------------------------------
			case KEY_DEL: // Backspace
			case KEY_BS: // ^U
				backspace ();
				terminal_print_line (this->cursor, this->cursor);
			break;
#ifdef _USE_CTLR_C
			case KEY_ETX:
			if (this->sigint != NULL)
				this->sigint();
			break;
#endif
			//-----------------------------------------------------
			default:
			if (((ch == ' ') && (this->cmdlen == 0)) || IS_CONTROL_CHAR(ch))
				break;
			if (insert_text ((char*)&ch, 1))
				terminal_print_line (this->cursor-1, this->cursor);
			
			break;
		}
#ifdef _USE_ESC_SEQ
	}
#endif
}
