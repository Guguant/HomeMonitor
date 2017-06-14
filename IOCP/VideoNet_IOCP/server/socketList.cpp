#include "SocketList.h"

// 获取socket
SOCKET SocketList::getSocket(int i)
{
	return (socketArray[i]);
}

// 将 new socket 插入 socketArray
void SocketList::insertSocket(SOCKET sock)
{
	for (int i = 0;i < FD_SETSIZE;i++)
	{
		// socketArry[i] = 0 表示 socket 未使用
		if (SocketList::socketArray[i] == 0)
		{
			SocketList::socketArray[i] = sock;
			num++;
			break;
		}
	}
}

// 从 socketArray 删除一个 socket
void SocketList::deleteSocket(SOCKET sock)
{
	for (int i = 0;i < FD_SETSIZE;i++)
	{
		if (socketArray[i] == sock)
		{
			socketArray[i] = 0;
			num--;
			break;
		}
	}
}

// 将 socketArray 中的socket放入 fd_set
void SocketList::setfd(fd_set * fd_list)
{
	// 清 0
	FD_ZERO(fd_list);

	// 将 socket 加入到 fd_list
	for (int i = 0;i < FD_SETSIZE; i++)
	{
		if (socketArray[i] > 0)
		{
			FD_SET(socketArray[i], fd_list);
		}
	}
}