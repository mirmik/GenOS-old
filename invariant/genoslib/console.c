/*
 * (C) Copyright 2000
 * Paolo Scaffardi, AIRVENT SAM s.p.a - RIMINI(ITALY), arsenio@tin.it
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include "types.h"
#include <stdarg.h>
#include "linuxlist.h"
#include <genoslib/exports.h>

#define CONFIG_SYS_PBSIZE 128

/** U-Boot INITIAL CONSOLE-COMPATIBLE FUNCTION *****************************/

#include "genoslib/vsprintf.h"
#include "debug/debug.h"
#include "simple.h"
void puts(const char *s)
{
if (stdprint==0) debug_print(s);
else pr(s);
}

int printf(const char *fmt, ...)
{
	va_list args;
	uint i;
	char printbuffer[CONFIG_SYS_PBSIZE];

	va_start(args, fmt);

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vscnprintf(printbuffer, sizeof(printbuffer), fmt, args);
	va_end(args);

	/* Print the string */
	puts(printbuffer);
	return i;
}

int vprintf(const char *fmt, va_list args)
{
	uint i;
	char printbuffer[CONFIG_SYS_PBSIZE];

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vscnprintf(printbuffer, sizeof(printbuffer), fmt, args);

	/* Print the string */
	puts(printbuffer);
	return i;
}

