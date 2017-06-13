#ifndef SEND_IMAGE_THREAD_H_
#define SEND_IMAGE_THREAD_H_

#include <process.h>
#include <stdio.h>

#include "common_image.h"
#include "select_fd_list.h"

// 数据缓冲区
typedef struct SendDataBuffer
{
	char buf[BUFFER_SIZE];
	int  flag; // buff
} SendDataBuffer;

// 发送图像  
// params : sock_client		client's socket
//			image			image to be sent
//
// return : -1				failed to send image
//          1				success to send image 
int SendImage(const SOCKET & sock_client, cv::Mat& image);

DWORD WINAPI workThread(LPVOID lpParam);
#endif
