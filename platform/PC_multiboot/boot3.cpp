
extern int main();
#include "descriptor_tables/descriptor_tables.h"
#include "debug/debug.h"
#include "error/error.h"

void boot3()
{
printd("boot3 OK\r\n");
printd("PLATFORM:");printd(PLATFORM_NAME);dln;
printd("CPU:");printd(CPU_NAME);dln;
init_descriptor_tables();
dln;
printd("Call main function...\r\n");
main();	

systemError("BOOT3 FUNCTION END. Kernel bewilderment :)");	
}
