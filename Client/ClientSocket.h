#pragma once
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>


class ClientSocket {
public:
	ClientSocket();
	~ClientSocket();
	SOCKET ConnectSocket = INVALID_SOCKET;

private:
	int iResult;
	WSADATA wsaData;

};