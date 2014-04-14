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
	return CloseHandle(hWrite);  //�رչܵ����
}
BOOL Command::ReadCommand(char *buffer,unsigned long *bytesRead)
{
	return ReadFile(hRead,buffer,MAX_SIZE,bytesRead,NULL);
}
void Command::WriteCommand(const char *cmd)
{
 sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
 sa.lpSecurityDescriptor = NULL;  //ʹ��ϵͳĬ�ϵİ�ȫ������ 
 sa.bInheritHandle = TRUE;  //�����Ľ��̼̳о��

 if (!CreatePipe(&hRead,&hWrite,&sa,0))  //���������ܵ�
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
 si.hStdOutput = hWrite;  //�´������̵ı�׼�������д�ܵ�һ��
 si.wShowWindow = SW_HIDE;  //���ش��� 
 si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;


 char cmdline[200]; 
 CString tmp;
 tmp.Format(TEXT("cmd /C %s"),cmd); 
 sprintf_s(cmdline,"%s",tmp);

 if (!CreateProcessA(NULL,cmdline,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))  //�����ӽ���
 {
  Util::LOG("CreateProcess Failed!");  
  return;
 }
 
 
}