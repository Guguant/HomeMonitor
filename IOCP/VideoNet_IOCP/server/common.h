#pragma once
#pragma warning(disable:4996)

#include <stdio.h>  
#include <winsock2.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include "protocol.h"

#define IMG_HEIGHT	480								// �贫��ͼ��ĸ� 
#define IMG_WIDTH	640								// �贫��ͼ��Ŀ�
 
#define BUF_SIZE 1500 // 480 * 640  * 8 + 10

#define MODE_READ 1
#define MODE_WRITE 2

extern cv::Mat global_image;	// ȫ��ͼ��
extern int time_count;			// ��ʱ��


typedef struct { // socket info  
				 // ע���ʱ������ռ䡢���ݡ�ʹ��
	SOCKET hClntSock;
	SOCKADDR_IN clntAdr;
} HANDLE_DATA;

typedef struct { // buffer info
				 // ��io�õ��Ļ����Overlapped�ṹ���װ��һ��
	OVERLAPPED overlapped;
	WSABUF wsaBuf;
	char buffer[BUF_SIZE];
	int rwMode;    // MODE_READ or MODE_WRITE
	int expectedSize;
	int recvSize;
} IO_DATA;