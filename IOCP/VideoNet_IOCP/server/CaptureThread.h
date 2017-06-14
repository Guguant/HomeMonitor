#pragma once
#include "common.h"

struct Element {
	short posi_x;
	short posi_y;
	uchar r;
	uchar g;
	uchar b;
};

DWORD _stdcall captureThread(LPVOID lpParam);
void get_diff(cv::Mat &last, cv::Mat &current, char* pktWithDiffImg);