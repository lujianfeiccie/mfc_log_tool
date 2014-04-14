#pragma once
#define MAX_SIZE 1024
class Command
{
public:	
	
	void WriteCommand(const char *cmd);
	BOOL ReadCommand(char *buffer,unsigned long* bytesRead);
	BOOL CloseRead();
	BOOL CloseWrite();
	Command(void);
	~Command(void);

	SECURITY_ATTRIBUTES sa;
	HANDLE hRead;
	HANDLE hWrite;
};

