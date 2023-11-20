#include "multi-threading.h"

Threads::Threads() {

}

Threads::~Threads()
{

}

bool Threads::createServerThread()
{
	return false;
}

DWORD WINAPI Threads::ThreadProc(LPVOID* lpParameters)
{
	//WSAAsyncSelect(servSock.ListenSocket, _hWnd, WM_USER, FD_ACCEPT | FD_CLOSE | FD_READ);
	InitializeCriticalSection(m_cs);

	// pour bloquer un bloc d'instructions
	EnterCriticalSection(m_cs);
	while (true)
	{

	}
	return 0;
	// pour libérer le bloc
	LeaveCriticalSection(m_cs);

	// quand c'est fini
	DeleteCriticalSection(m_cs);

}

bool Threads::Close() {
	return true;
}
