#pragma once
#include "framework.h"
#include "ServerSocket.h"
class Threads {
public:
	Threads();
	~Threads();
	virtual HANDLE GetMutex();
	virtual void createThread();
	LPDWORD   dwThreadId;
	HANDLE  hThread;

private:
	SOCKET tempClientSocket;
	std::string tempString;
	HANDLE ghMutex;
};

