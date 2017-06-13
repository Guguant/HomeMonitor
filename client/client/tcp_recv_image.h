#ifndef TCP_RECV_IMAGE_H_
#define TCP_RECV_IMAGE_H_
#pragma warning (disable:4996 )

#include <stdio.h>  
#include <Winsock2.h> 

#include "common_image.h"

#pragma comment(lib,"WS2_32.lib")  
// 数据缓冲区
typedef struct RecvDataBuffer
{
	char buf[BUFFER_SIZE];
	int  flag; // flag = 2 标识一帧结束
} RecvDataBuffer;

class SockRecvImage
{
public:
	SockRecvImage(void);
	~SockRecvImage(void);

private:
	SOCKET socket_client_;
	RecvDataBuffer recv_data_; // 接收图像数据

public:
	SOCKET	socket_entry() const { return socket_client_; };
	void set_socket_entries(SOCKET socket_entry) { socket_client_ = socket_entry; }

	// 打开socket连接  
	// params : IP      服务器的ip地址  
	//          PORT    传输端口  
	// return : -1      连接失败  
	//          1       连接成功  
	int SocketConnect(const char* IP, int PORT);

	// 断开socket连接  
	void SocketDisconnect(void);

	// 传输图像  
	// params : image   待接收图像  
	// return : -1      接收失败  
	//          1       接收成功  
	int RecvImage(cv::Mat& image);

};

#endif