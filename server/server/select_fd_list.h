#ifndef SELECT_FD_LIST_H_
#define SELECT_FD_LIST_H_
/**************************************************
 *
 * 类:  select_fd_list.h
 *		select 多路复用模型
 *************************************************/

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

class SocketList
{
private:
	int fd_set_num_;					// socket 描述符数目
	SOCKET socket_array_[FD_SETSIZE];	// FD_SETSIZE = 64

public:
	SocketList() {
		fd_set_num_ = 0;
		memset(socket_array_, 0, sizeof(SOCKET) * FD_SETSIZE);
	}
	~SocketList() {};

public:
	SOCKET socket_entry(int fd_i) const { return socket_array_[fd_i]; };
	void set_socket_entries(SOCKET socket_entry, int fd_i) { socket_array_[fd_i] = socket_entry; }

	// 将 new socket 插入 socket_array_[FD_SETSIZE]
	void InsertNewSocket(SOCKET);

	// 从 socket_array_[FD_SETSIZE] 删除断开连接的 socket
	void DeleteClosedSocket(SOCKET);

	// 将 socket_array_[FD_SETSIZE] 中的socket放入 fd_set
	void SetFdset(fd_set *);
};

#endif