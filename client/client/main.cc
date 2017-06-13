#pragma warning (disable:4996 )
#include <process.h>
#include <iostream>

#include "tcp_recv_image.h" 
#include "user_command.h"

using namespace std;

// work thread, 接收图片并显示
DWORD WINAPI RecvImageThread(LPVOID lpParam);

// 共享数据块
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

	// 创建线程
	HANDLE hThread = CreateThread(NULL, 0, RecvImageThread, &socket_mat, 0, NULL);
	if (hThread == NULL)
	{
		printf("Create Thread Failed.\n");
	}
	CloseHandle(hThread);

	help();
	while (true)
	{
		// 输入命令
		cin.getline(g_user_command, 20);

		// 输入 q 退出程序
		if (g_user_command[0] == 'q') { break; }
	}

	socket_mat.SocketDisconnect();
	system("pause");
	return 0;
}

/*******************************
 *多线程显示实时图片
 *******************************/
DWORD WINAPI RecvImageThread(LPVOID lpParam)
{
	SockRecvImage * socket_mat = (SockRecvImage *) lpParam;

	cv::Mat image;
	while (true)
	{
		// 接收图片
		(*socket_mat).RecvImage(image);
		if (!image.empty())
		{
			// 时间戳水印
			WaterMask(image);

			// 命令
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