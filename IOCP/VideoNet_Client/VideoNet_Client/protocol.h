#pragma once
#define IMG_HEIGHT 480
#define IMG_WIDTH 640
#define IMG_SIZE 640 * 480 * 3 // ͼ��ߴ�
#define WHOLE_IMAGE			1
#define DIFFERENCE_IMAGE	2

// ����ͼ��� Header
typedef struct WholeImage
{
	int type;
	int length;
}WholeImage;

// ��ֵͼ��� Header
typedef struct DifferenceImage
{
	int type;
	int length;
}DifferenceImage;