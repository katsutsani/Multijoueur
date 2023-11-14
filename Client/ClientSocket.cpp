#include "ClientSocket.h"
#define DEFAULT_PORT 05213
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

	iResult = inet_pton(hints.sin_family, "10.1.1.61", &hints.sin_addr);
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

	iResult = connect(ConnectSocket, (struct sockaddr*)&hints , sizeof(hints));
	if (iResult == SOCKET_ERROR) {
		std::cout << ("connect failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;

		return;
	}

	if (ConnectSocket == INVALID_SOCKET) {
		std::cout << ("Unable to connect to server!\n");
		WSACleanup();
		return;
	}

}

ClientSocket::~ClientSocket()
{
}
