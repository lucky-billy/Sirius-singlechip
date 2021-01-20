#ifndef __BCOMPONENT_H
#define __BCOMPONENT_H
#include "sys.h"

#define FOCUS_T PFout(1)			// 调焦转动
#define FOCUS_O PFout(2)			// 调焦方向

#define ZOOM_T PFout(3)				// 变倍转动
#define ZOOM_O PFout(4)				// 变倍方向
#define ZOOM_ML PGout(0)			// 变倍左限位
#define ZOOM_MR PGout(1)			// 变倍右限位

#define BRIGHT_T PBout(11)			// 明亮度转动
#define BRIGHT_O PBout(10)			// 明亮度方向
#define BRIGHT_ML PGout(2)			// 明亮度左限位
#define BRIGHT_MR PGout(3)			// 明亮度右限位

#define CONTRAST_T PDout(5)			// 对比度转动
#define CONTRAST_O PFout(11)		// 对比度方向
#define CONTRAST_ML PGout(4)		// 对比度左限位
#define CONTRAST_MR PGout(5)		// 对比度右限位

#define ALIGN PDout(11)				// 对准
#define MEASURE PEout(11)			// 测量

void BCOMPONENT_Init(void);			// 初始化

#endif
