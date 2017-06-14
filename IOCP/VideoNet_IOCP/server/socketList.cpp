#include "SocketList.h"

// ��ȡsocket
SOCKET SocketList::getSocket(int i)
{
	return (socketArray[i]);
}

// �� new socket ���� socketArray
void SocketList::insertSocket(SOCKET sock)
{
	for (int i = 0;i < FD_SETSIZE;i++)
	{
		// socketArry[i] = 0 ��ʾ socket δʹ��
		if (SocketList::socketArray[i] == 0)
		{
			SocketList::socketArray[i] = sock;
			num++;
			break;
		}
	}
}

// �� socketArray ɾ��һ�� socket
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

// �� socketArray �е�socket���� fd_set
void SocketList::setfd(fd_set * fd_list)
{
	// �� 0
	FD_ZERO(fd_list);

	// �� socket ���뵽 fd_list
	for (int i = 0;i < FD_SETSIZE; i++)
	{
		if (socketArray[i] > 0)
		{
			FD_SET(socketArray[i], fd_list);
		}
	}
}