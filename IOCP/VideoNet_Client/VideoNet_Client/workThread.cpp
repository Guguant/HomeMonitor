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

		// �����ر��׽���
		if (recvSize <= 0)
			break;

		// �����ò���length
		if (recvSize < 8)
			continue;

		// ��ȡ��������
		expectedSize = (expectedSize == 0 ? ((WholeImage *)buff)->length : expectedSize);

		// �յ���С�ڰ����ȡ�������Ҫ����һ�Σ�ճ��
		if (recvSize < expectedSize)
			continue;

		// �յ��Ĵ��ڵ��ڰ����ȡ�������Ҫ�ְ�����processPkt����
		while (recvSize >= expectedSize) {
			char* completedPkt = new char[expectedSize];
			memcpy(completedPkt, buff, expectedSize);
			processPkt(completedPkt, param);
			delete[] completedPkt;

			// ���·ְ�����������Ⱥ��յ�����
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
			/* ��ʼ��ʾ��Ƶ */
			//cvNamedWindow("video from server", 1);
			cv::imshow("video from server", *image);
			cv::startWindowThread();
			cv::waitKey(1);
			break;
		}
		case '2': {
			/* �ر���Ƶ���� */
			cvDestroyWindow("video from server");
			*command = '2';
			break;
		}
		case '3': {
			///* ���浱ǰͼƬ */
			// ����·��
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