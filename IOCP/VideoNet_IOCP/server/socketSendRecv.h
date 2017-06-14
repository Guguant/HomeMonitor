#pragma once
#pragma warning(disable:4996)

#include <stdio.h>
#include <Winsock2.h>
#include "common.h"

#pragma comment(lib,"WS2_32.lib")

class SocketSendRecv
{
public:
	SocketSendRecv() {}
	~SocketSendRecv() {}

public:
	// 发送图像  
	// params : sock	socket
	//			image   待传输图像差值数据
	//			length	image差值数据的长度
	//			
	// return : -1      接收失败  
	//          1       接收成功
	int send_whole_imagedata(SOCKET & sockClient, char * whole_image_data, int length);
	int send_difference_imagedata(SOCKET & sockClient, char * image_difference_data, int length);
};
