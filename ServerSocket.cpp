#include "ServerSocket.h"
#define DEFAULT_PORT 05213
struct sockaddr_in hints;

ServerSocket::ServerSocket() {

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.sin_family = AF_INET;
	hints.sin_port = htons(DEFAULT_PORT);

	iResult = inet_pton(hints.sin_family, "10.1.170.51", &hints.sin_addr);
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

void ServerSocket::ReceiveInfo()
{
	char recvbuf[512];
	do {
		for (size_t i = 0; i < ClientSocket.size(); i++)
		{
			iResult = recv(ClientSocket[i], recvbuf, 512, 0);
			if (iResult > 0) {
				std::cout << "Bytes received: %d\n", iResult;
			}
			else if (iResult == 0) {
				std::cout << "Closing Connection %d\n";
			}
			else {
				std::cout << "receive failed: %d\n", WSAGetLastError();
				closesocket(ClientSocket[i]);
				WSACleanup();
				return;
			}
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

