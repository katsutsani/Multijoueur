#pragma once
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <winsock2.h>

class ClientSocket {
public:
	ClientSocket();
	~ClientSocket();
	SOCKET ConnectSocket = INVALID_SOCKET;
	void SendInfo(const char* sendbuf);
	void ShutDown();
	void ReceiveInfo();
private:
	int iResult;
	WSADATA wsaData;

};