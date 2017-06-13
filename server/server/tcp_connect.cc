#include "tcp_connect.h"  

/*************************************************
 * ���� socket connect
 ************************************************/
int SocketInit::SocketConnect(int PORT)
{
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(1, 1);

	int err;
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return -1;
	}

	// ���� socket �׽���
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
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
	socket_server_ = sock;
}

// closesocket
void SocketInit::SocketDisconnect(void)
{
	closesocket(socket_server_);
}