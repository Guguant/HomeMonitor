#pragma once
#pragma warning(disable:4996)

#include <stdio.h>  
#include <winsock2.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include "protocol.h"

#define IMG_HEIGHT	480								// 需传输图像的高 
#define IMG_WIDTH	640								// 需传输图像的宽
 
#define BUF_SIZE 1500 // 480 * 640  * 8 + 10

#define MODE_READ 1
#define MODE_WRITE 2

extern cv::Mat global_image;	// 全局图像
extern int time_count;			// 计时器


typedef struct { // socket info  
				 // 注意何时被分配空间、传递、使用
	SOCKET hClntSock;
	SOCKADDR_IN clntAdr;
} HANDLE_DATA;

typedef struct { // buffer info
				 // 将io用到的缓冲和Overlapped结构体封装到一起
	OVERLAPPED overlapped;
	WSABUF wsaBuf;
	char buffer[BUF_SIZE];
	int rwMode;    // MODE_READ or MODE_WRITE
	int expectedSize;
	int recvSize;
} IO_DATA;