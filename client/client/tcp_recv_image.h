#ifndef TCP_RECV_IMAGE_H_
#define TCP_RECV_IMAGE_H_
#pragma warning (disable:4996 )

#include <stdio.h>  
#include <Winsock2.h> 

#include "common_image.h"

#pragma comment(lib,"WS2_32.lib")  
// ���ݻ�����
typedef struct RecvDataBuffer
{
	char buf[BUFFER_SIZE];
	int  flag; // flag = 2 ��ʶһ֡����
} RecvDataBuffer;

class SockRecvImage
{
public:
	SockRecvImage(void);
	~SockRecvImage(void);

private:
	SOCKET socket_client_;
	RecvDataBuffer recv_data_; // ����ͼ������

public:
	SOCKET	socket_entry() const { return socket_client_; };
	void set_socket_entries(SOCKET socket_entry) { socket_client_ = socket_entry; }

	// ��socket����  
	// params : IP      ��������ip��ַ  
	//          PORT    ����˿�  
	// return : -1      ����ʧ��  
	//          1       ���ӳɹ�  
	int SocketConnect(const char* IP, int PORT);

	// �Ͽ�socket����  
	void SocketDisconnect(void);

	// ����ͼ��  
	// params : image   ������ͼ��  
	// return : -1      ����ʧ��  
	//          1       ���ճɹ�  
	int RecvImage(cv::Mat& image);

};

#endif