#include "send_image_thread.h"

/**************************************
* 创建线程 处理多个socket
***************************************/
DWORD WINAPI workThread(LPVOID lpParam)
{
	// SocketList
	SocketList * socket_list = (SocketList *)lpParam;
	int err = 0;

	// write set
	fd_set fdwrite;

	/* select() timeout */
	struct timeval timeout;
	timeout.tv_sec = 6; // 6s
	timeout.tv_usec = 0;

	// 打开设备前置摄像头
	cv::VideoCapture capture(0);
	if (!capture.isOpened()) {
		printf("Open VideoCapture Failed.\n");
		return -1;
	}

	SOCKET socket;

	/* 发送图片 */
	cv::Mat image(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, cv::Scalar(0));
	while (true)
	{
		// socket 可写
		socket_list->SetFdset(&fdwrite);

		err = select(0, NULL, &fdwrite, NULL, &timeout); // timeout > 6s
		if (err == 0)
		{
			printf("select() timeout\n");
			continue;
		}
		else
		{
			// 遍历socketList中的每一个socket，查看socket是可写的，处理可写socket
			for (int i = 0; i < FD_SETSIZE;i++)
			{
				// socketArray[i] = 0 表示 当前socket不可用
				if (socket_list->socket_entry(i) == 0)
				{
					continue;
				}

				socket = socket_list->socket_entry(i);
				// if socket is writeable, start to send image data.
				if (FD_ISSET(socket, &fdwrite))
				{
					capture >> image;
					if (image.empty())
					{
						printf("read image failed!\n");
						return -1;
					}

					// send image to client
					err = SendImage(socket, image);
					if (err > 0)
					{
						printf("success.\n");
					}
					if (err < 0)
					{
						printf("%d is disconnect\n", int(socket));
						closesocket(socket);
						socket_list->DeleteClosedSocket(socket);
					}
				} // end if
			} //end for
		}
	} // end while
	capture.release();
}


/****************************************
* 发送图像
***************************************/
int SendImage(const SOCKET & sock_client, cv::Mat & image)
{
	SendDataBuffer send_data; // 传输图像数据
	memset(send_data.buf, 0, sizeof(char) * BUFFER_SIZE);
	send_data.flag = 0;

	// image is empty, return -1;
	if (image.empty())
	{
		printf("empty image\n\n");
		return -1;
	}

	// check SIZE of the image 
	if (image.cols != IMG_WIDTH || image.rows != IMG_HEIGHT || image.type() != CV_8UC3)
	{
		printf("the image must satisfy :\n	cols = IMG_WIDTH （%d） \
											rows = IMG_HEIGHT（%d) \
											type = CV_8UC3\n\n", IMG_WIDTH, IMG_HEIGHT);
		return -1;
	}

	// 将 480 * 640 的图片按 高 拆分成32个包
	for (int packet_num = 0; packet_num < 32; packet_num++)
	{
		int num1 = IMG_HEIGHT / 32 * packet_num;
		for (int image_row = 0; image_row < IMG_HEIGHT / 32; image_row++)
		{
			int num2 = image_row * IMG_WIDTH * 3;
			uchar* ucdata = image.ptr<uchar>(image_row + num1);
			for (int image_col = 0; image_col < IMG_WIDTH * 3; image_col++)
			{
				send_data.buf[num2 + image_col] = ucdata[image_col];
			}
		}

		if (packet_num == 31) // 标识帧的最后一个数据包
			send_data.flag = 2;
		else
			send_data.flag = 1;

		// 发送数据
		if (send(sock_client, (char *)(&send_data), sizeof(send_data), 0) < 0)
		{
			printf("send image error: %s(errno: %d)\n", strerror(errno), errno);
			return -1;
		}
	}
	return 0;
}