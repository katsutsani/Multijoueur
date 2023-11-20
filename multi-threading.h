#pragma once
#include "framework.h"
#include "ServerSocket.h"

class Threads {
public:
	Threads();
	~Threads();
	bool createServerThread();
	DWORD WINAPI ThreadProc(LPVOID* lpParameters);
	bool Close();

private:
	ServerSocket servSock;
	SOCKET tempClientSocket;
	std::string tempString;
	LPCRITICAL_SECTION m_cs;
};