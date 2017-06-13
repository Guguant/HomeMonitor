#pragma warning (disable:4996 )
#include <process.h>
#include <iostream>

#include "tcp_recv_image.h" 
#include "user_command.h"

using namespace std;

// work thread, ����ͼƬ����ʾ
DWORD WINAPI RecvImageThread(LPVOID lpParam);

// �������ݿ�
char g_user_command[20] = { '\0' };

int main(int argc, char *argv[])
{
	argv[1] = "127.0.0.10";
	argv[2] = "9000";
	SockRecvImage socket_mat;
	if (socket_mat.SocketConnect(argv[1], atoi(argv[2])) < 0)
	{
		return 0;
	}

	// �����߳�
	HANDLE hThread = CreateThread(NULL, 0, RecvImageThread, &socket_mat, 0, NULL);
	if (hThread == NULL)
	{
		printf("Create Thread Failed.\n");
	}
	CloseHandle(hThread);

	help();
	while (true)
	{
		// ��������
		cin.getline(g_user_command, 20);

		// ���� q �˳�����
		if (g_user_command[0] == 'q') { break; }
	}

	socket_mat.SocketDisconnect();
	system("pause");
	return 0;
}

/*******************************
 *���߳���ʾʵʱͼƬ
 *******************************/
DWORD WINAPI RecvImageThread(LPVOID lpParam)
{
	SockRecvImage * socket_mat = (SockRecvImage *) lpParam;

	cv::Mat image;
	while (true)
	{
		// ����ͼƬ
		(*socket_mat).RecvImage(image);
		if (!image.empty())
		{
			// ʱ���ˮӡ
			WaterMask(image);

			// ����
			UserCommand(g_user_command[0], image);
		}
		else {
			printf("fail to connect server :P\n");
			break;
		}
	}

	cvDestroyWindow("video from server");
	(*socket_mat).SocketDisconnect();

	return 0L;
}