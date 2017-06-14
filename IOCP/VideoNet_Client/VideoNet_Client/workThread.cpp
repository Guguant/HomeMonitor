#include "workThread.h"
#include "protocol.h"
#include "process.h"
#include "utils.h"

unsigned int __stdcall WorkerThread(LPVOID param) {
	SOCKET socket = ((threadParam*)param)->hSocket;
	char buff[1500000];
	int recvSize = 0;
	int expectedSize = 0;

	while (true) {
		recvSize += recv(socket, buff + recvSize, sizeof(buff) - recvSize, 0);

		// 错误或关闭套接字
		if (recvSize <= 0)
			break;

		// 避免拿不到length
		if (recvSize < 8)
			continue;

		// 获取期望长度
		expectedSize = (expectedSize == 0 ? ((WholeImage *)buff)->length : expectedSize);

		// 收到的小于包长度————要再收一次，粘包
		if (recvSize < expectedSize)
			continue;

		// 收到的大于等于包长度————要分包，给processPkt处理
		while (recvSize >= expectedSize) {
			char* completedPkt = new char[expectedSize];
			memcpy(completedPkt, buff, expectedSize);
			processPkt(completedPkt, param);
			delete[] completedPkt;

			// 更新分包后的期望长度和收到长度
			recvSize = recvSize - expectedSize;
			if (recvSize < 8) {
				memmove(buff, buff + expectedSize, recvSize);
				expectedSize = 0;
				break;
			}
			else {
				memmove(buff, buff + expectedSize, recvSize);
				expectedSize = ((WholeImage *)buff)->length;
			}
		}
	}

	closesocket(socket);
	return 0;
}

unsigned int __stdcall ShowThread(LPVOID param) {
	char* command = ((threadParam*)param)->command;
	cv::Mat *image = (cv::Mat *)(((threadParam*)param)->cvMat);
	// cv::Mat image = (*(cv::Mat *)((threadParam*)param)->cvMat).clone();
	while (true) {

		switch (*command) {
		case '1': {
			/* 开始显示视频 */
			//cvNamedWindow("video from server", 1);
			cv::imshow("video from server", *image);
			cv::startWindowThread();
			cv::waitKey(1);
			break;
		}
		case '2': {
			/* 关闭视频窗口 */
			cvDestroyWindow("video from server");
			*command = '2';
			break;
		}
		case '3': {
			///* 保存当前图片 */
			// 保存路径
			time_t t = time(0);
			char path[100];
			strftime(path, sizeof(path), "D:\\%Y-%m-%d-%H-%M-%S.jpg", localtime(&t));
			if (cv::imwrite(path, *image)) {
				printf("saved as %s\n", path);
			}
			else {
				printf("failed to save!\n");
			}
			*command = '1';
			break;
		}
		}
	}
	return 0;
}