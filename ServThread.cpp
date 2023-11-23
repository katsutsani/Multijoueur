#include "ServThread.h"
CRITICAL_SECTION m_servCS;
DWORD WINAPI servThreadProc(LPVOID lpParameters)
{
	ServThread* thread = (ServThread*)lpParameters;

	WSAAsyncSelect(thread->GetSock().ListenSocket, thread->GetWindow(), WM_USER, FD_ACCEPT | FD_CLOSE | FD_READ);

	InitializeCriticalSection(&m_servCS);

	// pour bloquer un bloc d'instructions
	EnterCriticalSection(&m_servCS);

	while (thread->GetSock().ListenSocket != SOCKET_ERROR && !thread->needToExit)
	{
		DWORD dwWaitResult = WaitForSingleObject(thread->GetMutex(), INFINITE);
		switch (dwWaitResult)
		{
		case WAIT_OBJECT_0:
			if (!ReleaseMutex(thread->GetMutex())) {

			}
			if (listen(thread->GetSock().ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
				printf("listen failed with error: %ld\n", WSAGetLastError());
				closesocket(thread->GetSock().ListenSocket);
				WSACleanup();
			}
			break;
		case WAIT_ABANDONED:
			// pour libérer le bloc
			LeaveCriticalSection(&m_servCS);

			// quand c'est fini
			DeleteCriticalSection(&m_servCS);
			return 0;
		default:
			break;
		}
	}

	// pour libérer le bloc
	LeaveCriticalSection(&m_servCS);

	// quand c'est fini
	DeleteCriticalSection(&m_servCS);
	return 0;
}


ServThread::ServThread() {

}

ServThread::~ServThread()
{

}

void ServThread::createThread()
{

}

bool ServThread::createServerThread(HWND hWnd)
{
	ghMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex

	if (ghMutex == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return false;
	}
	_hWnd = hWnd;
	hThread = CreateThread(
		NULL,
		0,
		servThreadProc,
		this,
		0,
		dwThreadId);
	return true;
}



void ServThread::Close() {
	needToExit = true;
}

ServerSocket ServThread::GetSock()
{
	return m_servSock;
}

HWND ServThread::GetWindow()
{
	return _hWnd;
}

HANDLE ServThread::GetMutex()
{
	return ghMutex;
}

HANDLE ServThread::GetThread()
{
	return hThread;
}