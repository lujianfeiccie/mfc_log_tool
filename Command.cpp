#include "StdAfx.h"
#include "Command.h"
#include "Util.h"

Command::Command(void)
{
}


Command::~Command(void)
{
}
BOOL Command::CloseRead()
{
	return CloseHandle(hRead);
}
BOOL Command::CloseWrite()
{
	return CloseHandle(hWrite);  //关闭管道句柄
}
BOOL Command::ReadCommand(char *buffer,unsigned long *bytesRead)
{
	return ReadFile(hRead,buffer,MAX_SIZE,bytesRead,NULL);
}
void Command::WriteCommand(const char *cmd)
{
 sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
 sa.lpSecurityDescriptor = NULL;  //使用系统默认的安全描述符 
 sa.bInheritHandle = TRUE;  //创建的进程继承句柄

 if (!CreatePipe(&hRead,&hWrite,&sa,0))  //创建匿名管道
 {  
	Util::LOG("CreatePipe Failed!");  
  return;
 }
 
 STARTUPINFO si; 
 PROCESS_INFORMATION pi;

 ZeroMemory(&si,sizeof(STARTUPINFO));
 si.cb = sizeof(STARTUPINFO); 
 GetStartupInfo(&si); 
 si.hStdError = hWrite; 
 si.hStdOutput = hWrite;  //新创建进程的标准输出连在写管道一端
 si.wShowWindow = SW_HIDE;  //隐藏窗口 
 si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;


 char cmdline[200]; 
 CString tmp;
 tmp.Format(TEXT("cmd /C %s"),cmd); 
 sprintf_s(cmdline,"%s",tmp);

 if (!CreateProcessA(NULL,cmdline,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))  //创建子进程
 {
  Util::LOG("CreateProcess Failed!");  
  return;
 }
 
 
}