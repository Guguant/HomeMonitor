#include "select_fd_list.h"

// 将 new socket 插入 socket_array_[FD_SETSIZE]
void SocketList::InsertNewSocket(SOCKET sock)
{
	for (int i = 0;i < FD_SETSIZE;i++)
	{
		// socketArry[i] = 0 表示 socket 未使用
		if (socket_array_[i] == 0)
		{
			socket_array_[i] = sock;
			fd_set_num_++;
			break;
		}
	}
}

// 从 socket_array_[FD_SETSIZE] 删除 与服务器断开连接的 socket
void SocketList::DeleteClosedSocket(SOCKET sock)
{
	for (int i = 0;i < FD_SETSIZE;i++)
	{
		if (socket_array_[i] == sock)
		{
			socket_array_[i] = 0;
			fd_set_num_--;
			break;
		}
	}
}

// 将 socketArray 中的socket放入 fd_set
void SocketList::SetFdset(fd_set * fd_list)
{
	FD_ZERO(fd_list);

	// 将 socket 加入到 fd_list
	for (int i = 0;i < FD_SETSIZE; i++)
	{
		if (socket_array_[i] > 0)
		{
			FD_SET(socket_array_[i], fd_list);
		}
	}
}