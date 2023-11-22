#pragma once
#include "framework.h"
#include "ServWebSock.h"

class ServWebThread : Threads {
public:
	ServWebThread();
	~ServWebThread();
	void createThread() override;
	ServWebSock GetSock();
	HANDLE GetMutex();
	HANDLE GetThread();
	bool createServerWebThread(HWND hWnd);
	void Close();
	bool needToExit = false;
	HWND _hWnd;
private:

	ServWebSock m_servWebSock;
	HANDLE ghMutex;
};