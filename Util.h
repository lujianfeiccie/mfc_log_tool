#pragma once

class Util
{
public:
 Util(void);
    static void __cdecl LOG(const char *format, ...);
	static int UTF8ToGBK(CString &strOut,const char* szSrc);
public:
 ~Util(void);
};
