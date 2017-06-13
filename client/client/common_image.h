#ifndef COMMON_IMAGE_H_
#define COMMON_IMAGE_H_

#include "opencv2/opencv.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/core/core.hpp"

#define IMG_WIDTH  640		// 需接收图像的宽  
#define IMG_HEIGHT 480		// 需接收图像的高  
#define BUFFER_SIZE IMG_WIDTH * IMG_HEIGHT * 3 / 32
							// 默认格式为CV_8UC3  分包个数 32


#endif