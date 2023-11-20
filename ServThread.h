#pragma once
#include "framework.h"
#include "ServerSocket.h"
#include <string>

class Threads {
public:
	Threads();
	~Threads();
	bool createServerThread();
	bool Close();
	ServerSocket GetSock();
private:

	ServerSocket m_servSock;
	SOCKET tempClientSocket;
	std::string tempString;
	LPDWORD   dwThreadIdArray[3];
	HANDLE  hThreadArray[3];
};