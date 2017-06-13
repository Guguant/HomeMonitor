#ifndef COMMON_IMAGE_H_
#define COMMON_IMAGE_H_

#pragma warning(disable:4996)
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#define IMG_WIDTH	640								// 需传输图像的宽
#define IMG_HEIGHT	480								// 需传输图像的高  
#define BUFFER_SIZE IMG_WIDTH * IMG_HEIGHT * 3 / 32	// 默认格式为CV_8UC3  

#endif