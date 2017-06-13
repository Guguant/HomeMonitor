#include "tcp_connect.h"
#include "select_fd_list.h"
#include "send_image_thread.h"

int main(int argc, char *argv[])
{
	// ����socket
	SocketInit socket_mat;
	if (socket_mat.SocketConnect(atoi(argv[1])) < 0)
	{
		printf("Usage: server.exe [port]\n");
		return 0;
	}
	printf("server is running at port %d ...\n", (int)(atoi(argv[1])));

	// �����߳�
	SocketList socketList;
	HANDLE hThread = CreateThread(NULL, 0, workThread, &socketList, 0, NULL);
	if (hThread == NULL)
	{
		printf("Create Thread Failed.\n");
	}
	CloseHandle(hThread);

	// client
	SOCKADDR_IN addr_client;
	int length_addr_client = sizeof(addr_client);

	SOCKET socket_new_connect;
	while (true)
	{
		// ���������յ�����󣬽�client��Ϣ����addr_client����������current TCP ��socket
		socket_new_connect = accept(socket_mat.socket_entry(), (SOCKADDR*)&addr_client, &length_addr_client);
		if (INVALID_SOCKET == socket_new_connect)
		{
			printf("Accept Failed.\n");
			return -1;
		}
		printf("%s:%d connected.\n", inet_ntoa(addr_client.sin_addr), addr_client.sin_port);

		socketList.InsertNewSocket(socket_new_connect);
	}
	// closesocket(socket_mat)
	socket_mat.SocketDisconnect();
	return 0;
}

