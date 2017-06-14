#include "process.h"
#include "protocol.h"
#include "workThread.h"
#include "utils.h"

void processPkt(char *completedPkt, LPVOID param) {
	WholeImage *head = (WholeImage*)completedPkt;

	switch (head->type) {
	case WHOLE_IMAGE:
		processWholeImg(completedPkt + sizeof(WholeImage), head->length, param);
		break;
	case DIFFERENCE_IMAGE:
		processDiffImg(completedPkt + sizeof(DifferenceImage), head->length, param);
		break;
	}
}

void processWholeImg(char *img, int size, LPVOID param) {
	cv::Mat *global_image = (cv::Mat*)(((threadParam*)param)->cvMat);
	int num1 = 0;
	uchar* ucdata = 0;
	for (int row = 0; row < IMG_HEIGHT; row++)
	{
		num1 = row * IMG_WIDTH * 3;
		ucdata = global_image->ptr<uchar>(row);
		for (int col = 0; col < IMG_WIDTH * 3; col++)
		{
			ucdata[col] = img[num1 + col];
		}
	}
}

void processDiffImg(char *diff, int size, LPVOID param) {
	cv::Mat *last_image = (cv::Mat*)(((threadParam*)param)->cvMat);
	uchar* ucdata = 0;
	int num1 = 0;
	Element *e = (Element*)diff;

	for (int i = 0; i < size; i++, e++) {
		ucdata = last_image->ptr<uchar>(e->posi_y);
		ucdata[e->posi_x * 3] += e->r;
		ucdata[e->posi_x * 3+1] += e->g;
		ucdata[e->posi_x * 3+2] += e->b;
	}
}