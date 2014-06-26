


#include "CRIUS.h"

void commandFSinit(){
/*
commandList.add("create",(size_t)createf);

commandList.add("createdir",(size_t)createdir);

commandList.add("ls",(size_t)ls);

commandList.add("cd",(size_t)cd);

commandList.add("cat",(size_t)cat);

commandList.add("delete",(size_t)deletefile);

commandList.add("exec",(size_t)exec);
*/
}








void WriteTextInFile( uint8 Page, uint16 Addr, uint16 Count, uint8 *BufferPtr ){
openPage(Page);

df_WriteStr(1,Addr,Count,BufferPtr );
df_WriteByte(1,Addr+Count,0);

closePage(Page);
}


void cat(char* c)
{Record_t rec;
char* d=0;

char* e=0;
char* f=0;
char* p=0;
uint8_t t1,t2,t3;
if (c==0x00) {Serial.println(F("not op"));
return;}
t1=stringAnalize(c,d);
if (d!=0) t2=stringAnalize(d,e); else t2=0;
if (e!=0) t3=stringAnalize(e,f);
else t3=0;
if (f!=0) {Serial.println("many op"); return;}
if (t1==1 && t2==0) 
{Serial.println(c); return;} 
if (t1==2 && t2==0) 
	{rec=fileInterpr(c);  
	if (rec.type==0xFF) Serial.println("wrong mnemonic");
	
else {
char* buffer;
buffer = (char*) malloc(512);
readFile(rec.address,buffer);

p=buffer;
while( p = strchr(p, '\\') ) {if (*(p+1)=='\\') {*p=' ';*(p+1)='\n'; p=p+2;} 
else p=p+1;}
Serial.println(buffer);
free(buffer);
}
	
return;}



if (t1==1 && t2==3 && t3==2) 
	{rec=fileInterpr(e);
	
if (rec.type==0xFF) 
Serial.println("wrong mnemonic");
	
else WriteTextInFile(rec.address,16,strlen(c),(uint8_t*)c);

	return;}
}



void exec(char* c)
{Record_t rec = fileInterpr(c);
  
char* buffer,*buf2;
buffer = (char*) malloc(512);
buf2=buffer;

if (rec.type==0xFF) Serial.println("wrong mnemonic");
else {
readFile(rec.address,buffer);
char* s=0;
do {
s = strchr((char*)buffer, '\\');
*s=0;
extsyscall(buffer);
buffer=s+1;
} while (s!=0);
	}
free(buf2);  		

	return;}

void createf(char* c)
{
FileSystem_createFile(c,'F');
}


void deletefile(char* c)
{Record_t rec;
rec = fileInterpr(c);
if (rec.type==0xFF || rec.type=='X') Serial.println (F("not enough mnemonic"));
rec.type='X';
FileSystem_BlockBit(rec.address,0);
FileSystem_writeRecord(rec);
}

void createdir(char* c)
{
FileSystem_createFile(c,'D');
}

void ls(char* c)
{
FileSystem_listDir(directory);
}
