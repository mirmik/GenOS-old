
#include "text_framebuffer.h"
#include "video_page.h"
#include "debug/debug.h"

/*-------------------------------------------
// Печать байта
//-----------------------------------------*/
void debug_print_byte(uint8_t value)
{
  char tmp[3];
 
  num2base_str(tmp,value, 16);
  strformat(tmp, 2, 0);
  debug_print(tmp);
}

/*--------------------------------------------
// Печать дампа памяти заданного размера
//------------------------------------------*/
void debug_print_dump(void* address, uint32_t size)
{
  /* Преобразуем указатель в массив байт */
  uint8_t* dump = (uint8_t*) address; 
  /* Преобразуем указатель просто в число */  
  uint32_t addr_tmp = (uint32_t) address;
  /* Вспомогательные переменные */
  uint32_t i = 0;
  uint32_t mark = 0;
 
  for (i = 0; i < size; i++)
  {
    //set_text_color(LIGHT_GRAY);
   
    if (mark == 0)
    {
    dpr_inthex(addr_tmp);
    debug_print(": ");
    }
   
    if (dump[i] != 0)
   ;//   set_text_color(LIGHT_GREEN);
    else
     // set_text_color(LIGHT_GRAY);
   ;
    print_byte(dump[i]);
   
    //set_text_color(LIGHT_GRAY);
   
    if ( mark == 7 )
    {
      print_text("|");
      mark++;
    }
    else if ( mark == 15 )
    {
      print_text("\n");
      mark = 0;
     
      addr_tmp += 0x10;
    }
    else
    {
      print_text(" ");
      mark++;
    }
  } 
}
