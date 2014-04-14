#include "StdAfx.h"
#include "Config.h"


Config::Config(void)
{
}


Config::~Config(void)
{
	
}
void Config::WriteConfig(const char* appname,const char* keyname,const char* value,const char* file)
{
	WritePrivateProfileString(appname,keyname,value,file);
}
void Config::WriteConfig(const char* keyname,const char* value)
{
	///////////////获取当前文件夹路径//////////////////////
	char bufferCurDir[1024];
	GetCurrentDirectory(1024,bufferCurDir);
	strcat(bufferCurDir,"\\");
	strcat(bufferCurDir,FILE_NAME);
	WriteConfig(APP_NAME,keyname,value,bufferCurDir);
}
void Config::ReadConfig(const char* appname,const char* keyname,char* value,unsigned int size,const char* file)
{
	GetPrivateProfileString(APP_NAME,keyname,"",value,size,file);
}
void Config::ReadConfig(const char* keyname,char* value)
{
	///////////////获取当前文件夹路径//////////////////////
	char bufferCurDir[1024];
	GetCurrentDirectory(1024,bufferCurDir);
	strcat(bufferCurDir,"\\");
	strcat(bufferCurDir,FILE_NAME);
	
	ReadConfig(APP_NAME,keyname,value,1024,bufferCurDir);	
}