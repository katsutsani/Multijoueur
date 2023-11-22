#include "ServWebThread.h"
CRITICAL_SECTION m_servWebCS;
DWORD WINAPI servWebThreadProc(LPVOID lpParameters)
{
	ServWebThread* thread = (ServWebThread*)lpParameters;
	WSAAsyncSelect(thread->GetSock().m_servWebSock, thread->_hWnd, WM_USER, FD_ACCEPT | FD_CLOSE);

	InitializeCriticalSection(&m_servWebCS);

	// pour bloquer un bloc d'instructions
	EnterCriticalSection(&m_servWebCS);

	std::string message = R"(
	<html>
		<header>
			<meta http-equiv="refresh" content="1" />
		</header>
		<body>
			<h1> Bienvenue sur le serveur de jeu </h1>
		</body>
	</html>)";


	while (thread->GetSock().m_servWebSock != INVALID_SOCKET && !thread->needToExit)
	{

		SOCKET clientWebSocket = accept(thread->GetSock().m_servWebSock, nullptr, nullptr);
		if (clientWebSocket != INVALID_SOCKET) {
			std::cout << "Web client connected!\n";

			// Répondre à la requête avec un message HTML
			std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
			response += message;

			send(clientWebSocket, response.c_str(), response.size(), 0);

			// Fermer la connexion avec le client web
			closesocket(clientWebSocket);
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

}

bool ServWebThread::createServerWebThread(HWND hWnd) {
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
		servWebThreadProc,
		this,
		0,
		dwThreadId);
	return true;
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
	return m_servWebSock;
}

HANDLE ServWebThread::GetMutex()
{
	return ghMutex;
}

HANDLE ServWebThread::GetThread()
{
	return hThread;
}


