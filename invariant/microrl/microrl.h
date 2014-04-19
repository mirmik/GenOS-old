
#ifndef _MICRORL_H_
#define _MICRORL_H_

#include "microrl_config.h"
#include "Stream.h"
//#include "Print.h"

#define true  1
#define false 0

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

#ifdef _USE_HISTORY
// history struct, contain internal variable
// history store in static ring buffer for memory saving
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
#endif

// microrl struct, contain internal library data
class  microrl_t
{
	Stream *strm;
	
int	escape_process (char ch);
int	insert_text (char * text, int len);
 void	backspace ();
	void hist_search (int dir);
	void terminal_move_cursor (int offset);
	void get_complite ();
	inline void terminal_newline ();
inline void terminal_backspace ();
	void new_line_handler();
inline void print_prompt ();
int split (int limit, char const ** tkn_arr);
void terminal_print_line (int pos, int cursor);
void terminal_reset_cursor ();


	public:
	
microrl_t();	
#ifdef _USE_ESC_SEQ
	char escape_seq;
	char escape;
#endif
#if (defined(_ENDL_CRLF) || defined(_ENDL_LFCR))
	char tmpch;
#endif
#ifdef _USE_HISTORY
	ring_history_t ring_hist;          // history object
#endif
	char * prompt_str;                 // pointer to prompt string
	char cmdline [_COMMAND_LINE_LEN];  // cmdline buffer
	int cmdlen;                        // last position in command line
	int cursor;                        // input cursor
	int (*execute) (int argc, const char * const * argv );            // ptr to 'execute' callback
	char ** (*get_completion) (int argc, const char * const * argv ); // ptr to 'completion' callback
	void (*print) (const char *);                                     // ptr to 'print' callback
#ifdef _USE_CTLR_C
	void (*sigint) (void);
#endif


// init internal data, calls once at start up
void init (Stream & strm);

// set echo mode (true/false), using for disabling echo for password input
// echo mode will enabled after user press Enter.
void set_echo (int);

// set pointer to callback complition func, that called when user press 'Tab'
// callback func description:
//   param: argc - argument count, argv - pointer array to token string
//   must return NULL-terminated string, contain complite variant splitted by 'Whitespace'
//   If complite token found, it's must contain only one token to be complitted
//   Empty string if complite not found, and multiple string if there are some token
void set_complete_callback (char ** (*get_completion)(int, const char* const*));

// pointer to callback func, that called when user press 'Enter'
// execute func param: argc - argument count, argv - pointer array to token string
void set_execute_callback (int (*execute)(int, const char* const*));

// set callback for Ctrl+C terminal signal
#ifdef _USE_CTLR_C
void set_sigint_callback (void (*sigintf)(void));
#endif

// insert char to cmdline (for example call in usart RX interrupt)
void insert_char (int ch);
};

#endif
