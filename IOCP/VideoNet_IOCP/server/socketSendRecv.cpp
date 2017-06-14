#include "socketSendRecv.h"
#include "protocol.h"

char buffer[10 + 640 * 480 * 3 * 8] = { '0' };

/****************************************
* ����ͼ�� ��������ͼ������
***************************************/
int SocketSendRecv::send_whole_imagedata(SOCKET & sockClient, char * whole_image_data, int length)
{
	// Error code
	int err = 0;

	// Pkt Header
	DifferenceImage head = { WHOLE_IMAGE ,length };
	memcpy(buffer, &head, sizeof(head));
	memcpy(buffer + sizeof(head), whole_image_data, length);

	// ��������
	err = send(sockClient, (char *)buffer, sizeof(head) + length, 0);
	if (err < 0)
	{
		printf("send whole image data error: %s(errno: %d)\n", strerror(errno), errno);
		return -1;
	}
	return 0;
}


/****************************************
* ����ͼ�� ����ͼ���ֵ
***************************************/
int SocketSendRecv::send_difference_imagedata(SOCKET & sockClient, char * image_difference_data, int length)
{
	// Pkt Header
	DifferenceImage head = { DIFFERENCE_IMAGE ,length };
	memcpy(buffer, &head, sizeof(head));
	memcpy(buffer + sizeof(head), image_difference_data,  length);

	// Error code
	int err = 0;
	// ��������
	err = send(sockClient, (char *)buffer, sizeof(head) + length, 0);
	if (err < 0)
	{
		printf("send difference image data error: %s(errno: %d)\n", strerror(errno), errno);
		return -1;
	}
	return 0;
}