#include <iostream>
#include <WinSock2.h>
#include <process.h>
#include "utils.h"
#include "workThread.h"
#include "process.h"

#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
	}

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	SOCKET hSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error!");

	SOCKADDR_IN servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));
	int len = sizeof(servAddr);

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");
	else
		puts("Connected.");

	cv::Mat global_image(480, 640, CV_8UC3, cv::Scalar(0));
	threadParam param = { &global_image ,hSocket ,'1' };
	_beginthreadex(NULL, 0, WorkerThread, (LPVOID)&param, 0, NULL);

	printf("-------------------------------------\n");
	printf("Commmad           Function\n");
	printf("  1               start to video\n");
	printf("  2               close video\n");
	printf("  3               save current image\n");
	printf("  q               quit\n");
	printf("-------------------------------------\n");

	_beginthreadex(NULL, 0, ShowThread, (LPVOID)&param, 0, NULL);

	while (true) {
		cin.getline(param.command, 20);
		if (param.command[0] == 'q') break;
	}

	closesocket(hSocket);
	return 0;
}