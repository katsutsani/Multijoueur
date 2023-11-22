#include "ServWebSock.h"
#define DEFAULT_PORT 05213
struct sockaddr_in servWebHints;

ServWebSock::ServWebSock() {

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cout << ("WSAStartup failed: %d\n", iResult);
		return;
	}

	ZeroMemory(&servWebHints, sizeof(servWebHints));
	servWebHints.sin_family = AF_INET;
	servWebHints.sin_port = htons(DEFAULT_PORT);

	iResult = inet_pton(servWebHints.sin_family, "10.1.170.51", &servWebHints.sin_addr);
	if (iResult != 1) {
		WSAGetLastError();
		printf("inet_pton failed %d\n", iResult);
		WSACleanup();
		return;
	}

	m_servWebSock = socket(PF_INET, SOCK_STREAM, 0);

	if (m_servWebSock == INVALID_SOCKET) {
		std::cout << ("Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup();
		return;
	}

}

void ServWebSock::connectToServ() {
	iResult = connect(m_servWebSock, (struct sockaddr*)&servWebHints, sizeof(servWebHints));
	//if (iResult == SOCKET_ERROR) {
	//	std::cout << ("connect failed with error: %d\n", WSAGetLastError());
	//	closesocket(ConnectSocket);
	//	ConnectSocket = INVALID_SOCKET;

	//	return;
	//}

	if (m_servWebSock == INVALID_SOCKET) {
		std::cout << ("Unable to connect to server!\n");
		WSACleanup();
		return;
	}
}

ServWebSock::~ServWebSock()
{
}

void ServWebSock::ReceiveInfo()
{
	char recvbuf[512];
	do {
		iResult = recv(m_servWebSock, recvbuf, 512, 0);
	} while (iResult < 0);
}

