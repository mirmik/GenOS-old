#ifndef RL_TERMINAL_H
#define RL_TERMINAL_H


#include "Stream.h"
#include "readline/readline.h"

 /* define the Key codes */
#define KEY_NUL 0 /**< ^@ Null character */
#define KEY_SOH 1 /**< ^A Start of heading, = console interrupt */
#define KEY_STX 2 /**< ^B Start of text, maintenance mode on HP console */
#define KEY_ETX 3 /**< ^C End of text */
#define KEY_EOT 4 /**< ^D End of transmission, not the same as ETB */
#define KEY_ENQ 5 /**< ^E Enquiry, goes with ACK; old HP flow control */
#define KEY_ACK 6 /**< ^F Acknowledge, clears ENQ logon hand */
#define KEY_BEL 7 /**< ^G Bell, rings the bell... */
#define KEY_BS  8 /**< ^H Backspace, works on HP terminals/computers */
#define KEY_HT  9 /**< ^I Horizontal tab, move to next tab stop */
#define KEY_LF  10  /**< ^J Line Feed */
#define KEY_VT  11  /**< ^K Vertical tab */
#define KEY_FF  12  /**< ^L Form Feed, page eject */
#define KEY_CR  13  /**< ^M Carriage Return*/
#define KEY_SO  14  /**< ^N Shift Out, alternate character set */
#define KEY_SI  15  /**< ^O Shift In, resume defaultn character set */
#define KEY_DLE 16  /**< ^P Data link escape */
#define KEY_DC1 17  /**< ^Q XON, with XOFF to pause listings; "okay to send". */
#define KEY_DC2 18  /**< ^R Device control 2, block-mode flow control */
#define KEY_DC3 19  /**< ^S XOFF, with XON is TERM=18 flow control */
#define KEY_DC4 20  /**< ^T Device control 4 */
#define KEY_NAK 21  /**< ^U Negative acknowledge */
#define KEY_SYN 22  /**< ^V Synchronous idle */
#define KEY_ETB 23  /**< ^W End transmission block, not the same as EOT */
#define KEY_CAN 24  /**< ^X Cancel line, MPE echoes !!! */
#define KEY_EM  25  /**< ^Y End of medium, Control-Y interrupt */
#define KEY_SUB 26  /**< ^Z Substitute */
#define KEY_ESC 27  /**< ^[ Escape, next character is not echoed */
#define KEY_FS  28  /**< ^\ File separator */
#define KEY_GS  29  /**< ^] Group separator */
#define KEY_RS  30  /**< ^^ Record separator, block-mode terminator */
#define KEY_US  31  /**< ^_ Unit separator */

#define KEY_DEL 127 /**< Delete (not a real control character...) */

#define IS_CONTROL_CHAR(x) ((x)<=31)


// direction of history navigation
#define _HIST_UP   0
#define _HIST_DOWN 1
// esc seq internal codes
#define _ESC_BRACKET  1
#define _ESC_HOME     2
#define _ESC_END      3

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

class rl_terminal{
	public:
	readline_t* rl; 	
	Stream* strm;
	int mode;
	void terminal_rewrite();
	void terminal_move_cursor (int offset);
inline void terminal_write (char* c, int len);
void hist_search (int dir);
	ring_history_t ring_hist;
	
   void	print_prompt();
void set_execute_callback (int (*_execute)(int, const char* const*));
	char escape;
	char escape_seq;
	void listen();
	   void	new_line_handler();

	rl_terminal(Stream* _strm,readline_t* _rl);
	void init(Stream* _strm,readline_t* _rl);
	
	inline void terminal_backspace ();	
inline void terminal_char (char c);

inline void terminal_del ();
int escape_process (char ch);	
};

#endif
