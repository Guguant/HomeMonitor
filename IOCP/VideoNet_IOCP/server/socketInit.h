#pragma once
/*******************************************
 *
 * class: SocketInit
 *		����socket���ӣ��ͷ�socket����
 *
 *
 *******************************************/


#include "common.h"

#pragma comment(lib,"WS2_32.lib")  

class SocketInit
{
public:
	SocketInit()
	{
		sockSrv = 0;
	}
	~SocketInit() {}

private:
	SOCKET sockSrv;

public:
	// ����sock
	SOCKET getsock();

	// ��socket����  
	// params : PORT    ����˿� 
	//
	// return : -1      ����ʧ��  
	//          1       ���ӳɹ�  
	int socketConnect(int PORT);

	// �Ͽ�socket����  
	void socketDisconnect(void);
};
