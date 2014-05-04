#include "descriptor_tables/descriptor_tables.h"
#include "debug/debug.h"

void platform_init()
{
printd(">>PLATFORM_INIT\r\n");
printd("PLATFORM:");printd(PLATFORM_NAME);dln;
printd("CPU:");printd(CPU_NAME);dln;
init_descriptor_tables();
}
