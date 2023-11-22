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
	void Close();
	bool needToExit = false;
private:
	ServWebSock servWebSock;
	HANDLE ghMutex;
};