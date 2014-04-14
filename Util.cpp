#include "StdAfx.h"
#include "Util.h"
#define DEBUG_LOG
Util::Util(void)
{
}
Util::~Util(void)
{
}
void __cdecl Util::LOG(const char* fmt, ...)
{
#ifdef DEBUG_LOG
    char buf[4096], *p = buf;
    va_list args;
 
 
    va_start(args, fmt);
    p += vsnprintf_s(p, sizeof(buf), _TRUNCATE, fmt, args);
    va_end(args);
 
 
    while ( p > buf && isspace(p[-1]) )
        *--p = '\0';
    *p++ = '\r';
    *p++ = '\n';
    *p = '\0';
 
 
    OutputDebugStringA(buf); //output as ANSI string //OutputDebugString
#endif
}  

int Util::UTF8ToGBK(CString &strOut,const char* szSrc)
{
	if(szSrc==NULL)
	{
	strOut="";
	return -1;
	}
	WCHAR *strSrc;
	TCHAR *szRes;
	int i = MultiByteToWideChar(CP_UTF8, 0, szSrc, -1, NULL, 0);
	strSrc = new WCHAR[i+1];
	MultiByteToWideChar(CP_UTF8, 0, szSrc, -1, strSrc, i);
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new TCHAR[i+1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);
	strOut = szRes;
	delete []strSrc;
	delete []szRes;
return 0;
}