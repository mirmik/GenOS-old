/*************************************************************************************
*
*  ������� Atmel DataFlash
*
*  ���������� � Strict ANSI C, MISRA-C 2004
*
*  by:      BSVi
*  version: 1.00
*
*************************************************************************************/

#include "dataflash.h"

#define SELECT()  PORTB &= ~DF_SS_PB;  // ����� SS
#define DESELECT() PORTB |= DF_SS_PB;

//------------------------------------------------------------------------------------
//  ����������� ���� dataflash
//------------------------------------------------------------------------------------

//df_Info_t df_Info;
/*
PROGMEM const df_Info_t df_table [] =
{
   { 512,  264,  9,  (0x3<<2) }, // 1M  AT45DB011
   { 1024, 264,  9,  (0x5<<2) }, // 2M  AT45DB021
   { 2048, 264,  9,  (0x7<<2) }, // 4M  AT45DB041
   { 4096, 264,  9,  (0x9<<2) }, // 8M  AT45DB081
   { 4096, 528,  10, (0xB<<2) }, // 16M AT45DB161
   { 8192, 528,  10, (0xD<<2) }, // 32M AT45DB321
   { 8192, 1056, 11, (0xF<<2) }, // 64M AT45DB642
};*/


// ���������� ���� ��������������� ������� �� ������� ���� �
// ���������������� ��������� �� ������
df_Info_t df_Info = { 4096, 528,  10, (0xB<<2) };


//------------------------------------------------------------------------------------
//  ���� ������� ��� ����������� �������������
//------------------------------------------------------------------------------------
#define FlashPageRead			0x52	// Main memory page read
#define ContArrayRead			0x68	// Continuous Array Read (Note : Only A/B/D-parts supported)
#define StatusReg			0x57	// Status register
#define Buf1Read			0x54	// Buffer 1 read
#define Buf2Read			0x56	// Buffer 2 read
#define Buf1Write			0x84	// Buffer 1 write
#define Buf2Write			0x87	// Buffer 2 write

#define DF_STATUS_READY 0x80


//------------------------------------------------------------------------------------
//  ���������� �������
//------------------------------------------------------------------------------------
//static Result df_DetectParams();
static uint8 DF_SPI_RW( uint8 tx );


//------------------------------------------------------------------------------------
//  �������������� SPI ��� ������ � dataflash
//------------------------------------------------------------------------------------
void df_Init()
{
   SPCR = 0; // ��������� SPI ����� ���������������� ����������� �����
   DESELECT();

   DDRB &= ~(DF_MISO_PB);

   DDRB |= DF_MOSI_PB + DF_SCK_PB + DF_SS_PB;    /* MOSI, SS, RESET, SCK - ������ */
DDRG |= DF_RESET_PB;
   
   PORTG &= ~DF_RESET_PB;  // ���������� dataflsah
   delay(10);          // RESET Pulse Width = 10us
   PORTG |= DF_RESET_PB;
   delay(1);           // RESET Recovery Time = 1us

   // ������������ ������� dataflash 15���, ����������� ������ ��� ����� ������ ����������
   SPCR = (1<<SPE) | (1<<MSTR) | (1<<CPHA) | (1<<CPOL);	// Enable SPI in Master mode, mode 3
   SPSR = (1<<SPI2X);
   return;
}


//------------------------------------------------------------------------------------
//  �������� ��������� � ���������� �������� ����
//------------------------------------------------------------------------------------
static uint8 DF_SPI_RW( uint8 tx )
{
   uint8 rx;

   SPDR = tx;
   while(!(SPSR & 0x80));
   rx = SPDR;
   return rx;
}		

//------------------------------------------------------------------------------------
//  ���������, ������ �� ������
//------------------------------------------------------------------------------------
uint8 df_isReady()
{
   return df_GetStatus() &  DF_STATUS_READY;
}


//------------------------------------------------------------------------------------
//  ������ ���� ��������� Dataflash. � ���������� ����� ����� ����� ������ �
//  ������� STATUS REGISTER READ.
//------------------------------------------------------------------------------------
uint8 df_GetStatus()
{
   uint8 status;

   SELECT();
   status = DF_SPI_RW(StatusReg);
   status = DF_SPI_RW(0x00);
   DESELECT();

   return status;
}

//------------------------------------------------------------------------------------
//  ������������ ��� dataflash
//------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------
//  ������ ���� ���� �� SRAM-������� dataflash
//	���������: BufferNo -> ����� ������� (1 ��� 2)
//                  Addr  -> ����� � �������
//------------------------------------------------------------------------------------
uint8 df_GetChar(uint8 BufferNo, uint16 Addr )
{
   uint8 data;

   SELECT();

   if ( BufferNo == 1 )	{ DF_SPI_RW(Buf1Read); }       // ������ 1
   else	if ( BufferNo == 2 ) { DF_SPI_RW(Buf2Read); }  // ������ 2
   else { DESELECT(); return 0; }                      // �������� � ������� �������

   DF_SPI_RW(0x00);              // ���� ������ ������ � ��������
   DF_SPI_RW((uint8)(Addr>>8));
   DF_SPI_RW((uint8)(Addr));
   DF_SPI_RW(0x00);
   data = DF_SPI_RW(0x00);

   DESELECT();

   return data;
}



//------------------------------------------------------------------------------------
//  ������ ���� ������ �� SRAM-������� dataflash
//	���������: BufferNo   -> ����� ������� (1 ��� 2)
//                  Addr       -> ����� � ������� � �������� �������� ������
//                  Count      -> ���������� ����, ������� ���������� ���������
//  		   *BufferPtr -> ����� ������� � ������� �������� ������
//------------------------------------------------------------------------------------
void df_GetStr( uint8 BufferNo, uint16 Addr, uint16 Count, uint8 *BufferPtr )
{
   SELECT();

   if ( BufferNo == 1 )	{ DF_SPI_RW(Buf1Read); }       // ������ 1
   else	if ( BufferNo == 2 ) { DF_SPI_RW(Buf2Read); }  // ������ 2
   else { DESELECT(); return; }                        // �������� � ������� �������

   DF_SPI_RW(0x00);
   DF_SPI_RW((unsigned char)(Addr>>8));
   DF_SPI_RW((unsigned char)(Addr));
   DF_SPI_RW(0x00);

   for( uint16 i=0; i<Count; i++)
   {
      *(BufferPtr) = DF_SPI_RW(0x00);
      BufferPtr++;
   }

   DESELECT();
}


//------------------------------------------------------------------------------------
//  ���������� ���� � SRAM-������ dataflash
//	���������: BufferNo   -> ����� ������� (1 ��� 2)
//                  Addr       -> ����� � ������� � �������� �������� ������
//                  Data       -> ���� ������� ����� ��������
//------------------------------------------------------------------------------------
void df_WriteByte( uint8 BufferNo, uint16 Addr, uint8 Data )
{
   SELECT();

   if ( BufferNo == 1 )	{ DF_SPI_RW(Buf1Write); }       // ������ 1
   else	if ( BufferNo == 2 ) { DF_SPI_RW(Buf2Write); }  // ������ 2
   else { DESELECT(); return; }                         // �������� � ������� �������

   DF_SPI_RW(0x00);
   DF_SPI_RW((unsigned char)(Addr>>8));
   DF_SPI_RW((unsigned char)(Addr));
   DF_SPI_RW(Data);

   DESELECT();
}


//------------------------------------------------------------------------------------
//  ���������� ���� ������ � SRAM-������ dataflash
//	���������: BufferNo   -> ����� ������� (1 ��� 2)
//                  Addr       -> ����� � ������� � �������� �������� ������
//                  Count      -> ���������� ����, ������� ���������� ��������
//  		   *BufferPtr -> ������, ������ �� �������� ����� ��������
//------------------------------------------------------------------------------------
void df_WriteStr( uint8 BufferNo, uint16 Addr, uint16 Count, uint8 *BufferPtr )
{
   SELECT();

   if ( BufferNo == 1 )	{ DF_SPI_RW(Buf1Write); }       // ������ 1
   else	if ( BufferNo == 2 ) { DF_SPI_RW(Buf2Write); }  // ������ 2
   else { DESELECT(); return; }                         // �������� � ������� �������

   DF_SPI_RW(0x00);
   DF_SPI_RW((unsigned char)(Addr>>8));
   DF_SPI_RW((unsigned char)(Addr));
   for( uint16 i=0; i<Count; i++)
   {
      DF_SPI_RW(*(BufferPtr));
      BufferPtr++;
   }


   DESELECT();
}


//------------------------------------------------------------------------------------
//  ����������� �� ����������
//	���������: Page�md  -> �������
//                  PageAdr  -> ����� ��������
//------------------------------------------------------------------------------------
void df_PageFunc( uint16 PageCmd, uint16 PageAdr )
{
   SELECT();

   DF_SPI_RW(PageCmd);
   DF_SPI_RW((uint8)(PageAdr >> (16 - df_Info.page_bit)));
   DF_SPI_RW((uint8)(PageAdr << (df_Info.page_bit - 8)));
 //  DF_SPI_RW((uint8)0);
 //  DF_SPI_RW((uint8)(PageAdr));
   DF_SPI_RW(0x00);

   DESELECT();

   while(!( df_GetStatus() & DF_STATUS_READY )); // ������� ���������� ��������
}

//------------------------------------------------------------------------------------
//  ��������� ���� ������ ��������������� �� Flash - ������
//	���������: PageAdr    -> ����� ��������, � ������� �������� ������
//                  Addr       -> ����� � ��������, � �������� �������� ������
//                  Count      -> ���������� ����, ������� ���������� ���������
//  		   *BufferPtr -> ����� ������� � ������� �������� ������
//------------------------------------------------------------------------------------
void df_FlashRead( uint16 PageAdr, uint16 Addr, uint16 Count, uint8 *BufferPtr )
{
   SELECT();

   DF_SPI_RW(ContArrayRead);
   DF_SPI_RW((unsigned char)(PageAdr >> (16 - df_Info.page_bit)));
   DF_SPI_RW((unsigned char)((PageAdr << (df_Info.page_bit - 8))+ (Addr>>8)));
   DF_SPI_RW((unsigned char)(Addr));
   DF_SPI_RW(0x00);
   DF_SPI_RW(0x00);
   DF_SPI_RW(0x00);
   DF_SPI_RW(0x00);

   for( uint16 i=0; i < Count; i++ )
   {
      *(BufferPtr) = DF_SPI_RW(0x00);
      BufferPtr++;
   }

   DESELECT();
}

/*****************************************************************************/
/*****************************************************************************/
/*             ���������� ��� �������� ������ � ������ ����������            */
/*****************************************************************************/
/*****************************************************************************/
#ifdef DF_ENABLE_LINEAR_SPACE
uint16 df_LinearSpace::page_in_buffer1 = 0xffff;

//------------------------------------------------------------------------------------
//  ��������� ��������� �� ������ ������
//------------------------------------------------------------------------------------
void df_LinearSpace::GoToZero()
{
   page = 0;
   address = 0;
}

//------------------------------------------------------------------------------------
//  ��� ������� ���������� ���������� ���� �� ����� dataflash.
//  ��������� ������� �� ���������� �������� �� ����������� ������� ������.
//  ��������� ������������ ������ ����������� ����� ��������.
//------------------------------------------------------------------------------------
uint32 df_LinearSpace::SpaceToEnd()
{
   return (uint32)df_Info.page_size*(df_Info.pages - page) - (uint32)address;
}

//------------------------------------------------------------------------------------
//  ������� ������
//	���������: count      -> ���������� ����, ������� ���������� ���������
//  		   *buffer    -> ����� ������� � ������� �������� ������
//------------------------------------------------------------------------------------
void df_LinearSpace::Read( uint8 *buffer, uint16 count )
{
   df_FlashRead( page, address, count, buffer );
   address += count;

   while( address >= df_Info.page_size )
   {
      address -= df_Info.page_size;
      page++;
   }
}

//------------------------------------------------------------------------------------
//  �������� ������
//	���������: count     -> ���������� ����, ������� ���������� ��������
//  		   *buffer    -> ����� ������� � ������� ��������� �������� ������
//------------------------------------------------------------------------------------
void df_LinearSpace::UnsafeWrite( uint8 *buffer, uint16 count )
{
   uint16 page_space_left = df_Info.page_size - address;

   // ��������� ������ � ������, ���� ��� ��� �� ���.
   if ( page != page_in_buffer1 )
   {
      df_PageFunc(DF_FLASH_TO_BUF1, page);
      page_in_buffer1 = page;
   }

   while (count)
   {
      page_space_left = df_Info.page_size - address;

      if ( count > page_space_left )   // ����� �������� ������ ������ ��� �������� ����� �� �������� ������.
      {
         // ���������� ��� ������� �� ����� � �������
         df_WriteStr(1, address, page_space_left, buffer);
         count -= page_space_left;
         buffer += page_space_left;

         // ���������� ������ �� ����
         df_PageFunc(DF_BUF1_TO_FLASH_WITH_ERASE, page);
         address = 0;
         page++;

         // ��������� ��������� ��������
         df_PageFunc(DF_FLASH_TO_BUF1, page);
         page_in_buffer1 = page;

      }
      else
      {
         df_WriteStr(1, address, count, buffer);
         address += count;
         count = 0;
      }
   }
}

//------------------------------------------------------------------------------------
//  ��������� ������ ������ � ���������� ������.
//------------------------------------------------------------------------------------
void df_LinearSpace::Finalize()
{
   df_PageFunc(DF_BUF1_TO_FLASH_WITH_ERASE, page);
}

//------------------------------------------------------------------------------------
//  ����������� ��������� ���������� ������
//	���������: displacement -> ��������
//------------------------------------------------------------------------------------
void df_LinearSpace::SeekForward( uint32 displacement )
{
   page += (displacement / df_Info.page_size);
   address += (displacement % df_Info.page_size);
}

//------------------------------------------------------------------------------------
//  ����������� ��������� ���������� �����
//	���������: displacement -> ��������
//------------------------------------------------------------------------------------
void df_LinearSpace::SeekBackward( uint32 displacement )
{
   page -= (displacement / df_Info.page_size);
   address -= (displacement % df_Info.page_size);
}


//------------------------------------------------------------------------------------
//  ����������� ��������� � �������� �����
//------------------------------------------------------------------------------------
void df_LinearSpace::GoTo( uint32 location )
{
   page = (location / df_Info.page_size);
   address = (location % df_Info.page_size);
}


#endif /* DF_ENABLE_LINEAR_SPACE */




