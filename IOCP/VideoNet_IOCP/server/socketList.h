#pragma once
/**************************************************
 *
 * 类:  SocketList
 *		select 多路复用模型
 *
 *
 *************************************************/

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

class SocketList
{
private:
	int num;						// socket 描述符数目
	SOCKET socketArray[FD_SETSIZE]; // FD_SETSIZE = 64

	SOCKADDR_IN sockClientArray[FD_SETSIZE];  // 客户端地址



public:
	// 构造函数初始化
	SocketList() {
		num = 0;
		memset(socketArray, 0, FD_SETSIZE * sizeof(SOCKET));
		memset(sockClientArray, 0, FD_SETSIZE * sizeof(SOCKADDR_IN));
	}
	~SocketList() {};

public:
	// 获取socket
	SOCKET getSocket(int);

	// 将 new socket 插入 socketArray
	void insertSocket(SOCKET);

	// 从 socketArray 删除一个 socket
	void deleteSocket(SOCKET);

	// 将 socketArray 中的socket放入 fd_set
	void setfd(fd_set *);
};