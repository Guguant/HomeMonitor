#pragma once
#include <WinSock2.h>

unsigned int __stdcall WorkerThread(LPVOID param);
unsigned int __stdcall ShowThread(LPVOID param);

struct threadParam{
	void *cvMat;
	SOCKET hSocket;
	char command[20];
};