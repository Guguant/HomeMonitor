#include "select_fd_list.h"

// �� new socket ���� socket_array_[FD_SETSIZE]
void SocketList::InsertNewSocket(SOCKET sock)
{
	for (int i = 0;i < FD_SETSIZE;i++)
	{
		// socketArry[i] = 0 ��ʾ socket δʹ��
		if (socket_array_[i] == 0)
		{
			socket_array_[i] = sock;
			fd_set_num_++;
			break;
		}
	}
}

// �� socket_array_[FD_SETSIZE] ɾ�� ��������Ͽ����ӵ� socket
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

// �� socketArray �е�socket���� fd_set
void SocketList::SetFdset(fd_set * fd_list)
{
	FD_ZERO(fd_list);

	// �� socket ���뵽 fd_list
	for (int i = 0;i < FD_SETSIZE; i++)
	{
		if (socket_array_[i] > 0)
		{
			FD_SET(socket_array_[i], fd_list);
		}
	}
}