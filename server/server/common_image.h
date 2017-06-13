#ifndef COMMON_IMAGE_H_
#define COMMON_IMAGE_H_

#pragma warning(disable:4996)
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#define IMG_WIDTH	640								// �贫��ͼ��Ŀ�
#define IMG_HEIGHT	480								// �贫��ͼ��ĸ�  
#define BUFFER_SIZE IMG_WIDTH * IMG_HEIGHT * 3 / 32	// Ĭ�ϸ�ʽΪCV_8UC3  

#endif