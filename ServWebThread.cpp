#include "ServWebThread.h"
CRITICAL_SECTION m_servWebCS;
DWORD WINAPI servWebThreadProc(LPVOID lpParameters)
{
	ServWebThread* thread = (ServWebThread*)lpParameters;

	//WSAAsyncSelect(thread->GetSock().ListenSocket, thread->GetWindow(), WM_USER, FD_ACCEPT | FD_CLOSE | FD_READ);

	InitializeCriticalSection(&m_servWebCS);

	// pour bloquer un bloc d'instructions
	EnterCriticalSection(&m_servWebCS);
	while (thread->GetSock().m_servWebSock != INVALID_SOCKET && !thread->needToExit)
	{
		DWORD dwWaitResult = WaitForSingleObject(thread->GetMutex(), INFINITE);
		switch (dwWaitResult)
		{
		case WAIT_OBJECT_0:
			if (!ReleaseMutex(thread->GetMutex())) {

			}
			break;
		case WAIT_ABANDONED:
			// pour libérer le bloc
			LeaveCriticalSection(&m_servWebCS);

			// quand c'est fini
			DeleteCriticalSection(&m_servWebCS);
			return 0;
		default:
			break;
		}
	}

	// pour libérer le bloc
	LeaveCriticalSection(&m_servWebCS);

	// quand c'est fini
	DeleteCriticalSection(&m_servWebCS);
	return 0;
}
ServWebThread::ServWebThread()
{

	ghMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex

	if (ghMutex == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return;
	}
	hThread = CreateThread(
		NULL,
		0,
		servWebThreadProc,
		this,
		0,
		dwThreadId);
}

ServWebThread::~ServWebThread()
{
}

void ServWebThread::createThread()
{
	//WSAAsyncSelect(m_servWebSock, hWnd, WM_USER, FD_READ | FD_CONNECT);

}
void ServWebThread::Close() {
	needToExit = true;
}
ServWebSock ServWebThread::GetSock()
{
	return servWebSock;
}

HANDLE ServWebThread::GetMutex()
{
	return ghMutex;
}

HANDLE ServWebThread::GetThread()
{
	return hThread;
}


