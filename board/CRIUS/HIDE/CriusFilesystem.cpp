
#include "CRIUS.h"



#define MAPSIZE (df_Info.pages/8)
df_LinearSpace LS;


Record_t fileInterpr(char* c)
{
Record_t rec;
for (int i=1;(i<df_Info.page_size/16);i++){
rec = FileSystem_readRecord(directory,i);
if (rec.type==0xFF) {return(rec);}
if (rec.type=='X') {continue;}
if (!strcmp(c,rec.mnem)) return(rec);
};
rec.type=0xFF; return(rec);
}

uint16_t directory=1;

void FileSystem_listDir(uint16_t directory)
{
Record_t rec;
for (int i=1;(i<df_Info.page_size/16);i++){
rec = FileSystem_readRecord(directory,i);
if (rec.type==0xFF) return;
if (rec.type=='X') continue;
Serial.print(rec.mnem); if (strlen(rec.mnem)<=INTcorrect) Serial.print('\t'); 
Serial.print('\t');Serial.print((char)rec.type);Serial.print('\t');Serial.println(rec.address);
}
}

void readFile(uint16_t a,char* &c){
df_FlashRead(a, 16, 512, (uint8_t*)c);}

Record_t FileSystem_readRecord(uint16_t directory,uint16_t count)
{Record_t rec;
uint8_t* buffer;
buffer = (uint8_t*) malloc(16);

df_FlashRead(directory, count*16, 16, buffer);
strlcpy(rec.mnem,(char*)(buffer+3),14);
rec.type=buffer[0];
rec.address=*(buffer+1);
rec.page=directory;
rec.pos=count;
free(buffer);   
return(rec);
}


void FileSystem_writeRecord(Record_t rec)
{uint16_t directory,count;
uint8_t* buffer;
buffer = (uint8_t*) malloc(16);
buffer[0]=rec.type;
*(buffer+1)=rec.address;
strlcpy((char*)(buffer+3),rec.mnem,14);
directory=rec.page;
count=rec.pos;
openPage(directory);
df_WriteStr(1, count*16, 16, buffer);
closePage(directory);
free(buffer);   
}


uint8_t FileSystem_createFile(char* c,char type)
{
if(fileInterpr(c).type!=0xFF && fileInterpr(c).type!='X') {Serial.println(F("This mnemonic was using."));return(0);}
if(c==0) {Serial.println(F("empty mnemonic. error."));return(0);}
if(strlen(c)>=14) {Serial.println(F("long name. Error. 13 symbols max."));return(0);}
uint8_t* buffer;
buffer = (uint8_t*) malloc(sizeof(char)*df_Info.page_size);
df_FlashRead( directory, 0,df_Info.page_size, buffer);
uint16_t i=0;
while(buffer[i]!=0xFF && buffer[i]!='X') {i=i+16; if (i>=df_Info.page_size) {Serial.println(F("fullDirectory")); free(buffer); return(0);}}
openPage(directory);
uint16_t addr=freeBlockSearch();
FileSystem_newRecordAtBuffer(c,type,addr,i/16);
closePage(directory);
FileSystem_newFileAtPage(addr, c, type);
free(buffer);   
}

uint16_t freeBlockSearch()
{
LS.GoTo(9);
uint16_t j;
uint16_t i;
uint8_t* buffer;
buffer = (uint8_t*) malloc(sizeof(char)*MAPSIZE);
df_FlashRead(0, 9, MAPSIZE, buffer);
for(i=0;i<MAPSIZE;i++)
for(j=0;j<8;j++) 
if (((buffer[i]>>j)&(1))==0) goto ex;
ex: free(buffer);
return(i*8+j);
}

void openPage(uint16_t Page)
{df_PageFunc(0x53, Page);}

void closePage(uint16_t Page)
{df_PageFunc(0x83, Page);}

   
void FileSystem_listBlockMap(void)
{
LS.GoTo(9);
uint8_t* buffer;
buffer = (uint8_t*) malloc(sizeof(char)*MAPSIZE);
df_FlashRead(0, 9, MAPSIZE, buffer);
for(uint16_t i=0;i<MAPSIZE;i++)
for(uint16_t j=0;j<8;j++) 
{Serial.print((uint8_t)((buffer[i]>>j)&(1)));
if (((i*8+j)%(128))==127) Serial.println();}
free(buffer);   
}

void FileSystem_format()
{LS.GoToZero();
uint8_t c=3;
LS.UnsafeWrite((uint8_t*)"MirmOS_FS",9);
LS.UnsafeWrite(&c,1);
c=0;
for (int i=0;i<MAPSIZE-2;i++) LS.UnsafeWrite(&c,1);
LS.Finalize();   
FileSystem_newFileAtPage(1,"root",'D');
}

void FileSystem_newFileAtPage(uint8_t Page,char *c, uint8_t type)
{int i=0;
df_PageFunc(0x53, Page);
FileSystem_newRecordAtBuffer(c,type,0,0);
for(i=0 ;i<df_Info.page_size-1;i++) df_WriteByte( 1, 16+i, 0xFF);
df_PageFunc(0x83, Page);
FileSystem_BlockBit(Page,1);
}

void FileSystem_newRecordAtBuffer(char *c, uint8_t type,uint16_t addr,uint8_t pos)
{int i;
df_WriteByte( 1, 0+pos*16, type );
df_WriteStr( 1, 1+pos*16, 2,(uint8_t*)&addr );
df_WriteStr( 1, 3+pos*16, strlen(c), (uint8_t*)c );
for(i=0 ;i<(13-strlen(c));i++) df_WriteByte( 1, 15-i+pos*16, 0x00);
}

void FileSystem_printPage(char *c)
{uint8_t* buffer;
buffer = (uint8_t*) malloc(sizeof(char)*df_Info.page_size);
df_FlashRead(atoi(c), 0, df_Info.page_size, buffer);
for(uint16_t i;i<df_Info.page_size;i++) 
{Serial.print(buffer[i],HEX);Serial.print('\t');Serial.print((char)buffer[i]);Serial.print('\t');
if ((i%(8))==7) Serial.println();}
free(buffer);
};


void FileSystem_BlockBit(uint16_t a,uint8_t b)
{
df_PageFunc(DF_FLASH_TO_BUF1, 0);
uint8_t c=0;
LS.GoTo(9+a/8);
LS.Read(&c,1);
LS.GoTo(9+a/8);
if (b==1) c = c | (1<<(a%8));
if (b==0) c = c & (~(1<<(a%8))); 
LS.Write(&c,1);
}


void FileSystem_SetByte(uint16_t page,uint16_t pos,uint8_t c)
{
openPage(page);
df_WriteByte( 1, pos, c);
closePage(page);
}

void FileSystem_init()
{
df_Init();
//strcpy(addr_str,"/root/");
commandList.add("fs_format",(size_t)FileSystem_format,ROOT);
commandList.add("fs_listBM",(size_t)FileSystem_listBlockMap);
commandList.add("printP",(size_t)FileSystem_printPage);
//commandFSinit();
}

