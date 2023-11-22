#pragma once
#include "framework.h"

class ServWebSock {
public:
	ServWebSock();
	void connectToServ();
	~ServWebSock();
	SOCKET m_servWebSock = INVALID_SOCKET;
	void ReceiveInfo();
private:
	int iResult;
	WSADATA wsaData;


};

