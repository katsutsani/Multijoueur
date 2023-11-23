#pragma once
#include "framework.h"


class ServerSocket {
	public:
		ServerSocket();
		~ServerSocket();
		void addClient();
		void removeClient();
		SOCKET ListenSocket = INVALID_SOCKET;
		void ReceiveInfo();
		void SendInfo(SOCKET clientSocket, const char* sendBuf);
		void SendInfoBis(const char* sendBuf);
		int players = 0;
		int actualPlayer = 0;
		void changeKey();
		std::map<int,SOCKET> ClientSocket = {};
		int indexToRemove;
		SOCKET webSocket = INVALID_SOCKET;
	private:
		int iResult;
		WSADATA wsaData;


};