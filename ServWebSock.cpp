#include "ServWebSock.h"
#define DEFAULT_PORT 05213
struct sockaddr_in servWebHints;
struct hostent *host;
ServWebSock::ServWebSock() {

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cout << ("WSAStartup failed: %d\n", iResult);
		return;
	}

	ZeroMemory(&servWebHints, sizeof(servWebHints));
	servWebHints.sin_family = AF_INET;
	servWebHints.sin_port = htons(5001);

	iResult = inet_pton(servWebHints.sin_family, "10.1.170.51", &servWebHints.sin_addr);
	if (iResult != 1) {
		WSAGetLastError();
		printf("inet_pton failed %d\n", iResult);
		WSACleanup();
		return;
	}

	m_servWebSock = socket(AF_INET, SOCK_STREAM, 0);

	if (bind(m_servWebSock, (struct sockaddr*)&servWebHints, sizeof(servWebHints)) == SOCKET_ERROR) {
		closesocket(m_servWebSock);
		WSACleanup();
		return;
	}
	if (listen(m_servWebSock, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "Can't listen on socket! Quitting...\n";
		closesocket(m_servWebSock);
		return ;
	}
	if (m_servWebSock == INVALID_SOCKET) {
		std::cout << ("Error at socket(): %ld\n", WSAGetLastError());
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

