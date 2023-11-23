#pragma once
#include "framework.h"
#include "ServerSocket.h"


class ServThread : Threads {
public:
	ServThread();
	~ServThread();
	void createThread() override;
	bool createServerThread(HWND hWnd);
	void Close();
	ServerSocket GetSock();
	HWND GetWindow();
	HANDLE GetMutex();
	HANDLE GetThread();
	bool needToExit = false;
private:
	HWND _hWnd;
	ServerSocket m_servSock;
	HANDLE ghMutex;
};