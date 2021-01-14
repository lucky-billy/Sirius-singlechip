#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "led.h"
#include "beep.h"
#include "remote.h"
#include "hc05.h" 	 
#include "usart3.h" 

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	// 设置系统中断优先级分组2
	delay_init(168);			// 延时初始化 
	uart_init(9600);			// 串口初始化
	
	LED_Init();		  			// 初始化LED
	BEEP_Init(); 				// 初始化蜂鸣器
	Remote_Init();				// 初始化红外线
	
	while ( HC05_Init() ) 		// 初始化HC05蓝牙模块
	{
		delay_ms(100);
	}

	while(1)
	{
		// 蓝牙
		if( USART3_RX_STA & 0X8000 )
		{
			u8 len = USART3_RX_STA & 0X7FFF;
			
			// 调焦左旋钮
			if ( USART3_RX_BUF[0] == '1' ) {
				LED0 = 1;		// 停止转动
				delay_ms(10);
				LED1 = 1;		// 设置方向为左旋
				delay_ms(10);
				LED0 = 0;		// 开始转动
				
				delay_ms(100);	// 转动时长
				
				LED0 = 1;		// 停止转动
					
				u3_printf("Focus - reduce !\r\n");
			}
				
			// 调焦右旋钮
			if ( USART3_RX_BUF[0] == '2' ) {
				LED0 = 1;		// 停止转动
				delay_ms(10);
				LED1 = 0;		// 设置方向为右旋
				delay_ms(10);
				LED0 = 0;		// 开始转动
				
				delay_ms(100);	// 转动时长
				
				LED0 = 1;		// 停止转动
					
				u3_printf("Focus - increase !\r\n");
			}
			
			// 变倍左旋钮
			if ( USART3_RX_BUF[0] == '3' ) {
				LED0 = 1;		// 停止转动
				delay_ms(10);
				LED1 = 1;		// 设置方向为左旋
				delay_ms(10);
				LED0 = 0;		// 开始转动
				
				delay_ms(100);	// 转动时长
				
				LED0 = 1;		// 停止转动
					
				u3_printf("Zoom - reduce !\r\n");
			}
				
			//  变倍右旋钮
			if ( USART3_RX_BUF[0] == '4' ) {
				LED0 = 1;		// 停止转动
				delay_ms(10);
				LED1 = 0;		// 设置方向为右旋
				delay_ms(10);
				LED0 = 0;		// 开始转动
				
				delay_ms(100);	// 转动时长
				
				LED0 = 1;		// 停止转动
					
				u3_printf("Zoom - increase !\r\n");
			}
			
			// 光暗调节左旋钮
			if ( USART3_RX_BUF[0] == '5' ) {
				LED0 = 1;		// 停止转动
				delay_ms(10);
				LED1 = 1;		// 设置方向为左旋
				delay_ms(10);
				LED0 = 0;		// 开始转动
				
				delay_ms(100);	// 转动时长
				
				LED0 = 1;		// 停止转动
					
				u3_printf("Brightness - reduce !\r\n");
			}
				
			// 光暗调节右旋钮
			if ( USART3_RX_BUF[0] == '6' ) {
				LED0 = 1;		// 停止转动
				delay_ms(10);
				LED1 = 0;		// 设置方向为右旋
				delay_ms(10);
				LED0 = 0;		// 开始转动
				
				delay_ms(100);	// 转动时长
				
				LED0 = 1;		// 停止转动
					
				u3_printf("Brightness - increase !\r\n");
			}

			// 对比度
			if ( USART3_RX_BUF[0] == '7' ) {
				u3_printf("Contrast !\r\n");
			}
			
			// 对准
			if ( USART3_RX_BUF[0] == '8' ) {
				u3_printf("Align !\r\n");
			}
			
			// 测量
			if ( USART3_RX_BUF[0] == '9' ) {
				u3_printf("Measure !\r\n");
			}
			
			USART3_RX_BUF[len] = 0;							// 加结束符
			printf("Bluetooth: %s\r\n", USART3_RX_BUF);		// 发送回应数据到串口1
			
			USART3_RX_STA = 0;
		}
		
		// 串口
		if ( USART_RX_STA & 0x8000 )
		{
			u8 len = USART_RX_STA & 0x3fff;	// 得到此次接收到的数据长度
			
			if ( USART_RX_BUF[0] == '1' )
			{
				LED0 = 0;
			}
			if ( USART_RX_BUF[0] == '2' )
			{
				LED0 = 1;
			}
			if ( USART_RX_BUF[0] == '4' )
			{
				LED1 = 0;
			}
			if ( USART_RX_BUF[0] == '5' )
			{
				LED1 = 1;
			}
			
			printf("Com:  ");
			for ( u8 t = 0; t < len; ++t )
			{
				USART_SendData(USART1, USART_RX_BUF[t]);         			// 向串口1发送数据
				while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);	// 等待发送结束
			}
			printf("\r\n");	// 插入换行
			USART_RX_STA = 0;
		}
		
		// 红外
		else
		{
			u8 key = 0;
			u8 *str = 0;
			
			key = Remote_Scan();

			if ( key != 0 ) 
			{
				switch(key)
				{
				case 162: 	break;	// CH-
				case 98: 	break;	// CH
				case 226: 	break;	// CH+
				
				case 34: 	break;	// PREV
				case 2:		break;	// NEXT
				case 194:	break;	// PLAY
				
				case 224:	break;	// VOL-
				case 168:	break;	// VOL+
				case 144:	break;	// EQ
				
				case 104:	break;	// 0
				case 152:	break;	// 100+
				case 176:	break;	// 200+
				
				case 48:	LED0 = 0;	break;	// 1
				case 24:	LED0 = 1;	break;	// 2
				case 122:	break;	// 3
				
				case 16:	LED1 = 0;	break;	// 4
				case 56:	LED1 = 1;	break;	// 5
				case 90:	break;	// 6
				
				case 66:	BEEP = 1;	break;	// 7
				case 74:	BEEP = 0;	break;	// 8
				case 82:	break;	// 9
				}
			
				//printf("%s\r\n", str);
			}
		}

		delay_ms(10);
	}
}
