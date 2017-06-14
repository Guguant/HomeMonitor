#pragma once
#define IMG_HEIGHT 480
#define IMG_WIDTH 640
#define IMG_SIZE 640 * 480 * 3 // 图像尺寸
#define WHOLE_IMAGE			1
#define DIFFERENCE_IMAGE	2

// 完整图像包 Header
typedef struct WholeImage
{
	int type;
	int length;
}WholeImage;

// 差值图像包 Header
typedef struct DifferenceImage
{
	int type;
	int length;
}DifferenceImage;