#ifndef USER_COMMAND_H_
#define USER_COMMAND_H_
#pragma warning (disable:4996 )

#include "common_image.h"

#include <stdio.h>  
#include <Winsock2.h>  

#include <iostream>
#include <vector>

using namespace std;

inline void help();										// �����ĵ�

bool UserCommand(char & command, cv::Mat & image);		// ����̨������Բ���ͼ��
void WaterMask(cv::Mat & image);						// ʱ���ˮӡ

// ʶ��ģ��
const char xmlPath[50] = "haarcascade_frontalface_alt.xml";

/**************************
* һЩ�򵥵Ĳ���
**************************/
inline void help()
{
	printf("-------------------------------------\n");
	printf("Commmad           Function\n");
	printf("  1               start to video\n");
	printf("  2               close video\n");
	printf("  3               save current image\n");
	printf("  4               face recognition\n");
	printf("  5               help\n");
	printf("  q               quit\n");
	printf("-------------------------------------\n");
}

#endif