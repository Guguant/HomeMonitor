/**********************************************
* Copyright 2017 zqh
* License:
* Author :
*
* class: SocketInit
*		1. SocketConnect(),	����socket�׽���
*		2. SocketDisconnect(), �ͷ�socket�׽���
************************************************/

#ifndef TCP_CONNECT_H_
#define TCP_CONNECT_H_

#include <stdio.h>  
#include <Winsock2.h>  
#pragma comment(lib,"WS2_32.lib")  

class SocketInit
{
private:
	SOCKET socket_server_;

public:
	SocketInit() { socket_server_ = 0; }
	~SocketInit() {}

public:
	SOCKET socket_entry() const { return socket_server_; };
	void set_socket_entries(SOCKET socket_entry) { socket_server_ = socket_entry; }

	// ����socket����
	// params : PORT    ����˿� 
	//
	// return :	-1      failed to conncet  
	//			 1		success to connect	
	int SocketConnect(int PORT);

	// �Ͽ�socket����
	// closesocket(socket_server_)
	void SocketDisconnect(void);
};

#endif