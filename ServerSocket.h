#pragma once
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <winsock2.h>
#include <map>

class ServerSocket {
	public:
		ServerSocket();
		~ServerSocket();
		SOCKET ListenSocket = INVALID_SOCKET;
		void ReceiveInfo();
		void SendInfo(SOCKET clientSocket, const char* sendBuf);
		void SendInfoBis(const char* sendBuf);
		int players = 0;
		int actualPlayer = 0;
		void changeKey();
		std::map<int,SOCKET> ClientSocket = {};
		int indexToRemove;
	private:
		int iResult;
		WSADATA wsaData;


};