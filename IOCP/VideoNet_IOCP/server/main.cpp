/*********************************
 * ������������ͼ������
 ********************************/
#pragma   warning   (   disable:4311) 
#include <process.h>

#include "protocol.h"		// Э��
#include "common.h"			// ȫ�ֱ���

#include "socketInit.h"		// socket���ӳ�ʼ��	
#include "socketList.h"		// SET_FD
#include "socketSendRecv.h" // ���ݷ���


#include "WorkThread.h"
#include "CaptureThread.h"

 // error code
int err = 0;



int main(int argc, char *argv[])
{
	// ���� socket
	SocketInit socketMat;
	if (socketMat.socketConnect(atoi(argv[1])) < 0)
	{
		return 0;
	}
	printf("server is running at port 8888 ...\n");


	// ������ɶ˿ھ��
	HANDLE hComPort;
	hComPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	SOCKET sockConn;
	HANDLE hThread;
	for (int i = 0;i < 2;i++) {
		// �����߳�
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

	// �ͻ��˵�ַ
	SOCKADDR_IN addrClient;
	int len = sizeof(addrClient);

	// ���տͻ��˵�����
	IO_DATA *ioInfo;
	HANDLE_DATA *handleInfo;

	int recvBytes;
	int flags = 0;

	while (true)
	{

		// ���������յ�����󣬽�client��Ϣ����addrClient����������current TCP ��socket
		sockConn = accept(socketMat.getsock(), (SOCKADDR*)&addrClient, &len);
		if (INVALID_SOCKET == sockConn)
		{
			printf("Accept Failed.\n");
			break;
		}
		// �����Ϣ��ʼ��
		handleInfo = new HANDLE_DATA();
		handleInfo->hClntSock = sockConn;
		memcpy(&(handleInfo->clntAdr), &addrClient, len);

		// ����socket�����֮ǰ��������ɶ˿ھ��
		CreateIoCompletionPort((HANDLE)sockConn, hComPort, (ULONG_PTR)handleInfo, 0);


		printf("%s:%d connected\n", inet_ntoa(addrClient.sin_addr), addrClient.sin_port);

		// overlapped�ͻ����ʼ��
		ioInfo = new IO_DATA();
		memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
		ioInfo->wsaBuf.len = BUF_SIZE;
		ioInfo->wsaBuf.buf = ioInfo->buffer;
		ioInfo->rwMode = MODE_READ;

		// ע���������
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