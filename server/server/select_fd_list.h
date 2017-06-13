#ifndef SELECT_FD_LIST_H_
#define SELECT_FD_LIST_H_
/**************************************************
 *
 * ��:  select_fd_list.h
 *		select ��·����ģ��
 *************************************************/

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

class SocketList
{
private:
	int fd_set_num_;					// socket ��������Ŀ
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

	// �� new socket ���� socket_array_[FD_SETSIZE]
	void InsertNewSocket(SOCKET);

	// �� socket_array_[FD_SETSIZE] ɾ���Ͽ����ӵ� socket
	void DeleteClosedSocket(SOCKET);

	// �� socket_array_[FD_SETSIZE] �е�socket���� fd_set
	void SetFdset(fd_set *);
};

#endif