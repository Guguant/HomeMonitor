/*********************************
 * 服务器负责发送图像数据
 ********************************/
#pragma   warning   (   disable:4311) 
#include <process.h>

#include "protocol.h"		// 协议
#include "common.h"			// 全局变量

#include "socketInit.h"		// socket连接初始化	
#include "socketList.h"		// SET_FD
#include "socketSendRecv.h" // 数据发送


#include "WorkThread.h"
#include "CaptureThread.h"

 // error code
int err = 0;



int main(int argc, char *argv[])
{
	// 监听 socket
	SocketInit socketMat;
	if (socketMat.socketConnect(atoi(argv[1])) < 0)
	{
		return 0;
	}
	printf("server is running at port 8888 ...\n");


	// 创建完成端口句柄
	HANDLE hComPort;
	hComPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	SOCKET sockConn;
	HANDLE hThread;
	for (int i = 0;i < 2;i++) {
		// 创建线程
		hThread = CreateThread(NULL, 0, workThread, hComPort, 0, NULL);
		if (hThread == NULL)
		{
			printf("Create RecvCompleteThread Failed.\n");
		}
	}

	HANDLE_DATA *handleInfoPtr[64] = {0};
	hThread = CreateThread(NULL, 0, captureThread, handleInfoPtr, 0, NULL);
	if (hThread == NULL)
	{
		printf("Create CaptureThread Failed.\n");
	}

	// 客户端地址
	SOCKADDR_IN addrClient;
	int len = sizeof(addrClient);

	// 接收客户端的连接
	IO_DATA *ioInfo;
	HANDLE_DATA *handleInfo;

	int recvBytes;
	int flags = 0;

	while (true)
	{

		// 接收请求，收到请求后，将client信息存入addrClient，返回描述current TCP 的socket
		sockConn = accept(socketMat.getsock(), (SOCKADDR*)&addrClient, &len);
		if (INVALID_SOCKET == sockConn)
		{
			printf("Accept Failed.\n");
			break;
		}
		// 句柄信息初始化
		handleInfo = new HANDLE_DATA();
		handleInfo->hClntSock = sockConn;
		memcpy(&(handleInfo->clntAdr), &addrClient, len);

		// 连接socket句柄和之前创建的完成端口句柄
		CreateIoCompletionPort((HANDLE)sockConn, hComPort, (ULONG_PTR)handleInfo, 0);


		printf("%s:%d connected\n", inet_ntoa(addrClient.sin_addr), addrClient.sin_port);

		// overlapped和缓冲初始化
		ioInfo = new IO_DATA();
		memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
		ioInfo->wsaBuf.len = BUF_SIZE;
		ioInfo->wsaBuf.buf = ioInfo->buffer;
		ioInfo->rwMode = MODE_READ;

		// 注册接收数据
		WSARecv(handleInfo->hClntSock, &(ioInfo->wsaBuf), 1, (LPDWORD)&recvBytes, (LPDWORD)&flags, &(ioInfo->overlapped), NULL);
		for (int i = 0;i < 64;i++) {
			if (handleInfoPtr[i] == NULL) {
				handleInfoPtr[i] = handleInfo;
				break;
			}
		}
	}
	return 0;
}