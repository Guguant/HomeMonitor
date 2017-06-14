#include "socketInit.h"  

/*****************************
 * ��ȡ��ǰsocket
 ****************************/
SOCKET SocketInit::getsock()
{
	return (sockSrv);
}

/*************************************************
 * ���� socket connect
 ************************************************/
int SocketInit::socketConnect(int PORT)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	// ����socket��
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return -1;
	}

	//if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	//{
	//	WSACleanup();
	//	return -1;
	//}

	// ���� socket �׽���
	//SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET sock = WSASocketW(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	
	if (INVALID_SOCKET == sock)
	{
		printf("Create Socket Failed.\n");
		return -1;
	}

	// server�˵�ַ�Ͷ˿ں�
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT);

	// �� socket
	err = bind(sock, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (err != 0)
	{
		printf("Bind Socket Failed\n");
		return -1;
	}
	
	// ����
	err = listen(sock, 5);
	if (err != 0)
	{
		printf("Listen Socket Failed.\n");
		return -1;
	}
	sockSrv = sock;
}

/***************************************
 * �ͷ� socket
 **************************************/
void SocketInit::socketDisconnect(void)
{
	closesocket(sockSrv);
}