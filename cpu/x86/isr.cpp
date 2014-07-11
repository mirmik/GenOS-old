


#include    "isr.h"
#include 	"debug_print.h"
#include 	"error.h"
#include 	"abstract_irq.h"
/*----------------------------------------------------------
// Наш простецкий обработчик, для иллюстрации и тестирования
//--------------------------------------------------------*/
extern "C" void isr_handler(interrupt_info_t regs)
{
	abstract_irq_controller(regs);
	
	
  /* Просто пишем на экране что произошло прерывание */
  /* и выводим его номер */
/*  debug_print("unhandled interrupt: ");dpr_inthex(regs.int_num);dln;
  debug_print("PROC_STATE: ");dln;
  printd("eax        :");dpr_inthex(regs.eax);dln;
  printd("ebx        :");dpr_inthex(regs.ebx);dln;
  printd("esx        :");dpr_inthex(regs.esx);dln;
  printd("edx        :");dpr_inthex(regs.edx);dln;
  printd("esp        :");dpr_inthex(regs.esp);dln;
  printd("esi        :");dpr_inthex(regs.esi);dln;
  printd("edi        :");dpr_inthex(regs.edi);dln;
  printd("num        :");dpr_inthex(regs.int_num);dln;
  printd("err        :");dpr_inthex(regs.err_code);dln;
  printd("ds,es,fs,gs:");dpr_inthex(regs.ds);dln;
  printd("eip        :");dpr_inthex(regs.eip);dln;
  printd("cs         :");dpr_inthex(regs.cs);dln;
  printd("eflags     :");dpr_inthex(regs.eflags);dln;
  printd("user_esp   :");dpr_inthex(regs.useresp);dln;
  printd("ss         :");dpr_inthex(regs.ss);dln;  
  debug_print("\n");
  while(1);*/
  //systemError("Uinterrupt");
}
