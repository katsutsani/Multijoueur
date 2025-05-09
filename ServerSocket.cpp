#include "ServerSocket.h"
#include "JSON.h"
#define DEFAULT_PORT 05213
#define _WINSOCK_DEPRECATED_NO_WARNINGS
struct sockaddr_in hints;
JSON jsonGame;

ServerSocket::ServerSocket() {
	jsonGame.RestartGame();
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.sin_family = AF_INET;
	hints.sin_port = htons(DEFAULT_PORT);

	iResult = inet_pton(hints.sin_family, "10.189.141.66", &hints.sin_addr);
	if (iResult != 1) {
		WSAGetLastError();
		printf("inet_pton failed %d\n", iResult);
		WSACleanup();
		return;
	}

	ListenSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup();
		return;
	}

	iResult = bind(ListenSocket, (struct sockaddr*)&hints, sizeof(hints));
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}
}

ServerSocket::~ServerSocket()
{
}

void ServerSocket::addClient()
{
	players++;
}

void ServerSocket::removeClient()
{
	players--;
}

void ServerSocket::ReceiveInfo()
{
	char recvbuf[512];
	do {
		for (size_t i = 0; i < ClientSocket.size(); i++)
		{
			iResult = recv(ClientSocket[i], recvbuf, 512, 0);
			if (iResult > 0) {
				//--------------------------------------------------------------
				std::string checkname;
				if (recvbuf[1] == '1' || recvbuf[1] == '2' || recvbuf[1] == '3') 
				{
					std::string pos;
					pos.push_back(recvbuf[0]);
					pos.push_back(recvbuf[1]);
					// change board
					jsonGame.UpdateGame(pos, std::to_string(i + 1));
					std::string pIndex = std::to_string(i+1);
					pos.push_back(pIndex.c_str()[0]);
					SendInfoBis(pos.c_str());
					pos.clear();
					std::string win;
					for (int j = 2; j < 11; j++)
					{
						win.push_back(recvbuf[j]);
					}
					if (win == "playerWin")
					{
						int ID = i + 1;
						win = win + std::to_string(ID);
						//jsonGame.victory(i);
						SendInfoBis(win.c_str());
						jsonGame.RestartGame();
						win.clear();
					}
				}
		
				for (int j = 0; j < 4; j++)
				{
					checkname.push_back(recvbuf[j]);
				}
				if (checkname == "name")
				{
					checkname.clear();

					for (int j = 4; j < iResult; j++)
					{
						checkname.push_back(recvbuf[j]);
					}

					jsonGame.CheckPlayer(checkname);

					checkname.clear();

					std::string tempChar = "player2" + jsonGame.GetPlayerFromGame("player2");
					if (tempChar != "" && ClientSocket[0]) {
						SendInfo(ClientSocket[0], tempChar.c_str());
					}
					tempChar = "player1" + jsonGame.GetPlayerFromGame("player1");
					if (tempChar != "" && ClientSocket[1]) {
						SendInfo(ClientSocket[1], tempChar.c_str());
					}
				}

				//----------------------------------------------------------------------------
				std::cout << "Bytes received: %d\n", iResult;
			}
			else if (iResult == 0) {
				std::cout << "Closing Connection %d\n";
			}
			else {
				iResult = 0;
				continue;
			}
			//else {
			//	std::cout << "receive failed: %d\n", WSAGetLastError();
			//	closesocket(ClientSocket[i]);
			//	WSACleanup();
			//	return;
			//}
		}
	} while (iResult < 0);
}

void ServerSocket::SendInfo(SOCKET clientSocket, const char* sendBuf)
{
	iResult = send(clientSocket, sendBuf, (int)strlen(sendBuf), 0);
	if (iResult == SOCKET_ERROR) {
		std::cout << "send failed %d\n", WSAGetLastError();
		closesocket(clientSocket);
		WSACleanup();
		return;
	}
}

void ServerSocket::SendInfoBis(const char* sendBuf)
{
	for (int i = 0; i < ClientSocket.size(); i++)
	{
		iResult = send(ClientSocket[i], sendBuf, (int)strlen(sendBuf), 0);
		if (iResult == SOCKET_ERROR) {
			std::cout << "send failed %d\n", WSAGetLastError();
			closesocket(ClientSocket[i]);
				WSACleanup();
				return;
			}
	}
	
}

