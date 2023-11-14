#pragma once
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <winsock2.h>


class ServerSocket {
	public:
		ServerSocket();
		~ServerSocket();
		SOCKET ListenSocket = INVALID_SOCKET;
		void ReceiveInfo(SOCKET ClientSocket);

	private:
		int iResult;
		WSADATA wsaData;

};