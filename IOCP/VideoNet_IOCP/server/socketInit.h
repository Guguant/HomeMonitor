#pragma once
/*******************************************
 *
 * class: SocketInit
 *		建立socket连接，释放socket连接
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
	// 访问sock
	SOCKET getsock();

	// 打开socket连接  
	// params : PORT    传输端口 
	//
	// return : -1      连接失败  
	//          1       连接成功  
	int socketConnect(int PORT);

	// 断开socket连接  
	void socketDisconnect(void);
};
