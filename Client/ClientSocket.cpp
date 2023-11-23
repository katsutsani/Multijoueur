#include "ClientSocket.h"
#include <string>
#define DEFAULT_PORT 05213
#include <cstdio>
#include "Game.h"

Players players;
Game game;

Players player;
struct sockaddr_in hints;

ClientSocket::ClientSocket() {
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cout << ("WSAStartup failed: %d\n", iResult);
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.sin_family = AF_INET;
	hints.sin_port = htons(DEFAULT_PORT);

	iResult = inet_pton(hints.sin_family, "10.1.2.10", &hints.sin_addr);
	if (iResult != 1) {
		WSAGetLastError();
		printf("inet_pton failed %d\n", iResult);
		WSACleanup();
		return;
	}

	ConnectSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (ConnectSocket == INVALID_SOCKET) {
		std::cout << ("Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup();
		return;
	}
}

ClientSocket::~ClientSocket()
{
}

void ClientSocket::connectToServ(HWND hWnd) {

	WSAAsyncSelect(ConnectSocket, hWnd, WM_USER, FD_READ | FD_CONNECT);

	iResult = connect(ConnectSocket, (struct sockaddr*)&hints, sizeof(hints));
	//if (iResult == SOCKET_ERROR) {
	//	std::cout << ("connect failed with error: %d\n", WSAGetLastError());
	//	closesocket(ConnectSocket);
	//	ConnectSocket = INVALID_SOCKET;

	//	return;
	//}

	if (ConnectSocket == INVALID_SOCKET) {
		std::cout << ("Unable to connect to server!\n");
		WSACleanup();
		return;
	}
}

void ClientSocket::SendInfo(const char* sendbuf)
{

	int iResult;
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		std::cout << "send failed %d\n", WSAGetLastError();
		closesocket(ConnectSocket);
		WSACleanup();
		return;
	}
}

void ClientSocket::ShutDown()
{
	int iResult = shutdown(ConnectSocket, SD_SEND); {
		if (iResult == SOCKET_ERROR) {
			std::cout << "Shutdown failed %d\n", WSAGetLastError();
			closesocket(ConnectSocket);
			WSACleanup();
			return;
		}
	}
}

void ClientSocket::ReceiveInfo()
{
	char recvbuf[512];
	do {
		iResult = recv(ConnectSocket, recvbuf, 512, 0);
		if (iResult > 0) {
			index << recvbuf[0];
			if (recvbuf[1] == 'S') {
				SendInfo("i'm Spectator");
			}
			else if (recvbuf[1] == 'P') {
				std::string tempString = "I'm player " + std::to_string(index);
				SendInfo(tempString.c_str());
			}
			if (recvbuf[9] == '1' || recvbuf[9] == '2')
			{
				int ID;
				if (recvbuf[9] == '1')
				{
					ID = 1;
				}
				else
				{
					ID = 2;
				}
				players.RenderWinner(ID);
			}
			std::string pos;
			for (int j = 0; j < 2; j++)
			{
				pos = recvbuf[j];
			}
			std::string token;
			token = recvbuf[2];

			if (pos == "A1" || pos == "A2" || pos == "A3" || pos == "B1" || pos == "B2" || pos == "B3" || pos == "C1" || pos == "C2" || pos == "C3")
			{
				game.BoardModif(pos, token);
			}
			std::cout << "Bytes received: %d\n", iResult;
		}
		else if (iResult == 0) {
			std::cout << "Connection closed %d\n";
		}
		else {
			std::cout << "receive failed: %d\n", WSAGetLastError();
		}
	} while (iResult < 0);
}
