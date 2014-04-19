/* --------------------------------------------------------------------------
  FILE        : boot.h
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : ARM926EJ-S entry point functionality header
 ----------------------------------------------------------------------------- */

#ifndef _BOOT_H_
#define _BOOT_H_

//#include "tistdtypes.h"

// Prevent C++ name mangling
/*
 * boot() has naked attribute (doesn't save registers since it is the entry point
 * out of boot and it doesn't have an exit point). This setup requires
 * that the gnu compiler uses the -nostdlib option. 
 */
void boot( void ) __attribute__((naked,section(".boot")));


#endif //_BOOT_H_

