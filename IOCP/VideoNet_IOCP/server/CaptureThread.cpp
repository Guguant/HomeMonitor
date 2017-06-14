#include "CaptureThread.h"
#include <stdio.h>

// 最新一帧图片
cv::Mat last_image(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, cv::Scalar(0));
int CompactWithHeader(char * Dst, char * Source, int dstLen, int srcLen);

/**************************************
* 创建线程 处理多个socket
***************************************/
DWORD _stdcall captureThread(LPVOID lpParam)
{
	HANDLE_DATA **handleInfoPtr = (HANDLE_DATA**)lpParam;

	// 打开设备前置摄像头
	cv::VideoCapture capture(0);
	if (!capture.isOpened()) {
		printf("Open VideoCapture Failed.\n");
		return -1;
	}

	char *pktWithWholeImg = (char*)malloc(sizeof(char) * IMG_SIZE + 10);
	char *pktWithDiffImg = (char*)malloc(15000000);
	IO_DATA* ioInfo = new IO_DATA();
	memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
	ioInfo->rwMode = MODE_WRITE;

	int times = 0;

	int diff_size = 0;
	while (true) {
		last_image = global_image.clone();
		capture >> global_image;

		/*if (times == 0) {*/
			times++;
			// 完整图像处理
			CompactWithHeader(pktWithWholeImg, (char*)global_image.data, 0, IMG_SIZE);
			HANDLE_DATA **handleInfo = handleInfoPtr;
			for (int i = 0; i < 64; i++) {
				if (*(handleInfo + i) != NULL) {
					ioInfo->wsaBuf.buf = pktWithWholeImg;
					ioInfo->wsaBuf.len = sizeof(WholeImage) + IMG_SIZE;
					WSASend((*(handleInfo + i))->hClntSock, &(ioInfo->wsaBuf), 1, NULL, 0, &(ioInfo->overlapped), NULL);
				}
			}
		//}
		//else {
		//	times = times > 19 ? 0 : (times + 1);
		//	// 差值图像处理
		//	get_diff(last_image, global_image, pktWithDiffImg);
		//	HANDLE_DATA **handleInfo = handleInfoPtr;
		//	for (int i = 0; i < 64; i++) {
		//		if (*(handleInfo + i) != NULL) {
		//			ioInfo->wsaBuf.buf = pktWithDiffImg;
		//			ioInfo->wsaBuf.len = ((DifferenceImage*)pktWithDiffImg)->length;
		//			WSASend((*(handleInfo + i))->hClntSock, &(ioInfo->wsaBuf), 1, NULL, 0, &(ioInfo->overlapped), NULL);
		//		}
		//	}
		//}
	}
	free(pktWithWholeImg);
	free(pktWithDiffImg);
}

int CompactWithHeader(char * Dst, char * Source, int dstLen, int srcLen)
{
	// Pkt Header
	WholeImage head = { WHOLE_IMAGE ,srcLen + sizeof(head) };
	memcpy(Dst, &head, sizeof(head));
	memcpy(Dst + sizeof(head), Source, srcLen);
	return 0;
}

void get_diff(cv::Mat &last, cv::Mat &current, char* pktWithDiffImg) {
	DifferenceImage *head = (DifferenceImage*)(pktWithDiffImg);
	head->type = DIFFERENCE_IMAGE;
	head->length = 8;
	Element temp;
	for (int i = 0; i < IMG_HEIGHT; i++) {
		uchar* old_ucdata = last.ptr<uchar>(i);
		uchar* new_ucdata = current.ptr<uchar>(i);
		for (int j = 0; j < IMG_WIDTH; j++) {
			temp.posi_x = i;
			temp.posi_y = j;
			temp.r = new_ucdata[j * 3] - old_ucdata[j * 3];
			temp.g = new_ucdata[j * 3 + 1] - old_ucdata[j * 3 + 1];
			temp.b = new_ucdata[j * 3 + 2] - old_ucdata[j * 3 + 2];
			if (-15 < temp.r&temp.r < 15) {
				temp.r = 0;
			}
			if (-15 < temp.g&temp.g < 15) {
				temp.g = 0;
			}
			if (-15 < temp.b&temp.b < 15) {
				temp.b = 0;
			}

			if (temp.r || temp.g || temp.b) {
				memcpy(pktWithDiffImg + head->length, &temp, sizeof(temp));
				head->length += sizeof(temp);
			}
			temp.r = 0;
			temp.g = 0;
			temp.b = 0;
		}
	}
}