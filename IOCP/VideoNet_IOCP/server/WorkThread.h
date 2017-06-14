#pragma once
#include "common.h"
// 图片数据
//char imagedata[10 + (640 * 480 * 3) * 8] = { '0' };

// 工作线程
DWORD _stdcall workThread(LPVOID lpParam);