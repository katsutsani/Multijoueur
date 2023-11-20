#include "ServThread.h"
CRITICAL_SECTION m_cs;

DWORD WINAPI ThreadProc(LPVOID lpParameters)
{
	//WSAAsyncSelect(servSock.ListenSocket, _hWnd, WM_USER, FD_ACCEPT | FD_CLOSE | FD_READ);
	InitializeCriticalSection(&m_cs);

	// pour bloquer un bloc d'instructions
	EnterCriticalSection(&m_cs);

	Threads* thread = (Threads*)lpParameters;

	if (listen(thread->GetSock().ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("listen failed with error: %ld\n", WSAGetLastError());
		closesocket(thread->GetSock().ListenSocket);
		WSACleanup();
	}

	// pour libérer le bloc
	LeaveCriticalSection(&m_cs);

	// quand c'est fini
	DeleteCriticalSection(&m_cs);
	return 0;
}


Threads::Threads() {
	hThreadArray[1] = CreateThread(
		NULL,
		0,
		ThreadProc,
		this,
		0,
		dwThreadIdArray[1]);
}

Threads::~Threads()
{

}



bool Threads::createServerThread()
{

	return false;
}



bool Threads::Close() {
	return true;
}

ServerSocket Threads::GetSock()
{
	return m_servSock;
}
