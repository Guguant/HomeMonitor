#pragma once
#include <WinSock2.h>
#include "utils.h"

typedef struct Element {
	short posi_x;
	short posi_y;
	uchar r;
	uchar g;
	uchar b;
}Element;

void processPkt(char *completedPkt, LPVOID param);
void processWholeImg(char *img, int size, LPVOID param);
void processDiffImg(char *diff, int size, LPVOID param);