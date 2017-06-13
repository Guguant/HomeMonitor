#ifndef USER_COMMAND_H_
#define USER_COMMAND_H_
#pragma warning (disable:4996 )

#include "common_image.h"

#include <stdio.h>  
#include <Winsock2.h>  

#include <iostream>
#include <vector>

using namespace std;

inline void help();										// 帮助文档

bool UserCommand(char & command, cv::Mat & image);		// 控制台命令，用以操作图像
void WaterMask(cv::Mat & image);						// 时间戳水印

// 识别模型
const char xmlPath[50] = "haarcascade_frontalface_alt.xml";

/**************************
* 一些简单的操作
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