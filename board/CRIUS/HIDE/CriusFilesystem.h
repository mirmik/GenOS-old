#ifndef FILESYSTEM_H
#define FILESYSTEM_H


#include "../CRIUS/dataflash.h"




extern uint16_t directory;


struct Record_t
{
char mnem[14];
uint8_t type;
uint16_t address;
uint16_t page;
uint16_t pos;
};


void exec(char* c);


Record_t fileInterpr(char* c);
//void FileSystem_listBlockMap();
void FileSystem_init();
void FileSystem_newFileAtPage(uint8_t Page,char *c,uint8_t);
void FileSystem_newRecordAtBuffer(char *c, uint8_t type,uint16_t addr,uint8_t pos);
void FileSystem_BlockBit(uint16_t a,uint8_t b);
void FileSystem_SetByte(uint16_t page,uint16_t pos,uint8_t c);
void readFile(uint16_t,char* &c);
uint16_t freeBlockSearch();
uint8_t FileSystem_createFile(char*,char);
void FileSystem_writeRecord(Record_t rec);
void FileSystem_printPage(char *c);
void openPage(uint16_t Page);
void closePage(uint16_t Page);
void commandFSinit();
void createf(char* c);
void createdir(char* c);
void readFile(uint16_t rec,char* &c);
void cat(char* c);
void deletefile(char* c);
Record_t fileInterpr(char* c);
void WriteTextInFile(uint8_t BufferNo, uint16_t Addr, uint16_t Count, uint8_t *BufferPtr);

void FileSystem_listDir(uint16_t directory);
Record_t FileSystem_readRecord(uint16_t directory,uint16_t count);


//#include "../CRIUS_FS/Filesystem.cpp"
#endif