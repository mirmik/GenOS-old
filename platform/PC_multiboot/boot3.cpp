#include "descriptor_tables/descriptor_tables.h"
#include "debug_print.h"
#include "platform.h"

void platform_init()
{
debug_print(">>PLATFORM_INIT\r\n");
debug_print("PLATFORM:");debug_print(PLATFORM_NAME);dln;
debug_print("CPU:");debug_print(CPU_NAME);dln;
init_descriptor_tables();
}
