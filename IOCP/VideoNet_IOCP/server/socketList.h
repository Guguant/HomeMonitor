#pragma once
/**************************************************
 *
 * ��:  SocketList
 *		select ��·����ģ��
 *
 *
 *************************************************/

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

class SocketList
{
private:
	int num;						// socket ��������Ŀ
	SOCKET socketArray[FD_SETSIZE]; // FD_SETSIZE = 64

	SOCKADDR_IN sockClientArray[FD_SETSIZE];  // �ͻ��˵�ַ



public:
	// ���캯����ʼ��
	SocketList() {
		num = 0;
		memset(socketArray, 0, FD_SETSIZE * sizeof(SOCKET));
		memset(sockClientArray, 0, FD_SETSIZE * sizeof(SOCKADDR_IN));
	}
	~SocketList() {};

public:
	// ��ȡsocket
	SOCKET getSocket(int);

	// �� new socket ���� socketArray
	void insertSocket(SOCKET);

	// �� socketArray ɾ��һ�� socket
	void deleteSocket(SOCKET);

	// �� socketArray �е�socket���� fd_set
	void setfd(fd_set *);
};