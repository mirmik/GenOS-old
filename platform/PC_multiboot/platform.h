#ifndef PLATFORM_H
#define PLATFORM_H

#define PLATFORM_NAME "PC_multiboot"

#include "cpu.h"
#include "video_page.h"
#include "timer.h"

void platform_init();

#include "isr.h"
static void platform_abstract_irq_handler(interrupt_info_t * info)
{
if (info->int_num >= 40) outb (0xA0,0x20);
if (info->int_num >= 32) outb (0x20,0x20);
};

#define SEI() asm("sti");

void debug_reset_cursor();

uint64_t millis();

#endif
