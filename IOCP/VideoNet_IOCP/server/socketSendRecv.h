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
	// ����ͼ��  
	// params : sock	socket
	//			image   ������ͼ���ֵ����
	//			length	image��ֵ���ݵĳ���
	//			
	// return : -1      ����ʧ��  
	//          1       ���ճɹ�
	int send_whole_imagedata(SOCKET & sockClient, char * whole_image_data, int length);
	int send_difference_imagedata(SOCKET & sockClient, char * image_difference_data, int length);
};
