#include "tcp_recv_image.h"  

SockRecvImage::SockRecvImage(void)
{
}

SockRecvImage::~SockRecvImage(void)
{
}

/*******************************************************
 * 建立socket连接
 ******************************************************/
int SockRecvImage::SocketConnect(const char* IP, int PORT)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return -1;
	}

	err = (int)(socket_client_ = socket(AF_INET, SOCK_STREAM, 0));
	if (err < 0) {
		printf("create socket error: %s(errno: %d)\n\n", strerror(errno), errno);
		return -1;
	}
	else
	{
		printf("create socket successful!\nnow connect ...\n\n");
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(IP);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT);

	err = connect(socket_client_, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (err < 0)
	{
		printf("connect error: %s(errno: %d)\n\n", strerror(errno), errno);
		return -1;
	}
	else
	{
		printf("connect successful!\n\n");
		return 1;
	}
}

/****************************************
 * 断开socket 连接
 ***************************************/
void SockRecvImage::SocketDisconnect(void)
{
	closesocket(socket_client_);
	WSACleanup();
}

/****************************************
* 接收图像
***************************************/
int SockRecvImage::RecvImage(cv::Mat& image)
{
	cv::Mat img(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, cv::Scalar(0));

	int needRecv = sizeof(RecvDataBuffer);
	int count = 0;

	while (1)
	{
		for (int i = 0; i < 32; i++)
		{
			int pos = 0;  // 缓冲区位置
			int len0 = 0; // 一次接收数据的长度

			while (pos < needRecv)
			{
				len0 = recv(socket_client_, (char*)(&recv_data_) + pos, needRecv - pos, 0);
				if (len0 < 0)
				{
					// printf("Server Recieve Data Failed!\n");
					return -1;
				}
				pos += len0;
			}

			count = count + recv_data_.flag;

			// 组包
			int num1 = IMG_HEIGHT / 32 * i;
			for (int j = 0; j < IMG_HEIGHT / 32; j++)
			{
				int num2 = j * IMG_WIDTH * 3;
				uchar* ucdata = img.ptr<uchar>(j + num1);
				for (int k = 0; k < IMG_WIDTH * 3; k++)
				{
					ucdata[k] = recv_data_.buf[num2 + k];
				}
			}

			if (recv_data_.flag == 2)
			{
				if (count == 33) // 数据包已接收完整 31 + 2
				{
					image = img;
					return 1;
				}
				else // 数据包存在丢失，接收下一帧
				{
					printf("miss pkt!\n");
					count = 0;
					i = 0;
				}
			}
		}
	}
}