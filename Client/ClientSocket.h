#pragma once
#include "framework.h"
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

class Game;

class ClientSocket {
public:
	ClientSocket();
	~ClientSocket();
	SOCKET ConnectSocket = INVALID_SOCKET;
	void SendInfo(const char* sendbuf);
	void ShutDown();
	void ReceiveInfo(Game* game, Players* player);
	void connectToServ(HWND hWnd);
	int index;
private:

	int iResult;
	WSADATA wsaData;

};