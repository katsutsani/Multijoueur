#pragma once
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <winsock2.h>
#include <vector>


class ServerSocket {
	public:
		ServerSocket();
		~ServerSocket();
		SOCKET ListenSocket = INVALID_SOCKET;
		void ReceiveInfo(SOCKET ClientSocket);
		void SendInfo(SOCKET clientSocket, const char* sendBuf);
		int players = 0;
		int actualPlayer = 0;
		std::vector<SOCKET> ClientSocket = {};
	private:
		int iResult;
		WSADATA wsaData;


};