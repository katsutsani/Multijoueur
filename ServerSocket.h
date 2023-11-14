#pragma once
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>


class ServerSocket {
	public:
		ServerSocket();
		~ServerSocket();
		SOCKET ListenSocket = INVALID_SOCKET;

	private:
		int iResult;
		WSADATA wsaData;

};