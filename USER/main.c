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
#include "bcomponent.h"

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	// 设置系统中断优先级分组2
	delay_init(168);			// 延时初始化 
	uart_init(9600);			// 串口初始化
	
	LED_Init();		  			// 初始化LED
	BEEP_Init(); 				// 初始化蜂鸣器
	Remote_Init();				// 初始化红外线
	BCOMPONENT_Init();			// 初始化自定义引脚
	
	while ( HC05_Init() ) 		// 初始化HC05蓝牙模块
	{
		delay_ms(100);
	}
	
	u8 infrared = 0;

	while(1)
	{
		// 蓝牙
		if( USART3_RX_STA & 0X8000 )
		{
			u8 len = USART3_RX_STA & 0X7FFF;
			
			// 调焦左旋钮
			if ( USART3_RX_BUF[0] == '1' ) {
				FOCUS_O = 1;		// 调焦电机方向变为默认方向
				FOCUS_T = 0;		// 调焦电机开始转动
				delay_ms(1000);		// 转动时长
				FOCUS_T = 1;		// 调焦电机停止转动
					
				u3_printf("Focus - reduce !\r\n");
			}
				
			// 调焦右旋钮
			if ( USART3_RX_BUF[0] == '2' ) {
				FOCUS_O = 0;		// 调焦电机方向变为相反方向
				FOCUS_T = 0;		// 调焦电机开始转动
				delay_ms(1000);		// 转动时长
				FOCUS_T = 1;		// 调焦电机停止转动
				FOCUS_O = 1;		// 调焦电机方向变为默认方向
					
				u3_printf("Focus - increase !\r\n");
			}
			
			// 变倍左旋钮
			if ( USART3_RX_BUF[0] == '3' ) {
				ZOOM_O = 1;			// 变倍电机方向变为默认方向
				ZOOM_T = 0;			// 变倍电机开始转动
				delay_ms(1000);		// 转动时长
				ZOOM_T = 1;			// 变倍电机停止转动
					
				u3_printf("Zoom - reduce !\r\n");
			}
				
			//  变倍右旋钮
			if ( USART3_RX_BUF[0] == '4' ) {
				ZOOM_O = 0;			// 变倍电机方向变为相反方向
				ZOOM_T = 0;			// 变倍电机开始转动
				delay_ms(1000);		// 转动时长
				ZOOM_T = 1;			// 变倍电机停止转动
				ZOOM_O = 1;			// 变倍电机方向变为默认方向
					
				u3_printf("Zoom - increase !\r\n");
			}

			// 对比度
			if ( USART3_RX_BUF[0] == '7' ) {
				// 先根据限位确定位置，再转到另一个位置
				u3_printf("Contrast !\r\n");
			}
			
			// 对准
			if ( USART3_RX_BUF[0] == '8' ) {
				// 发送信号给上位机，打开对准相机
				u3_printf("Align !\r\n");
				printf("8\r\n");
			}
			
			// 测量
			if ( USART3_RX_BUF[0] == '9' ) {
				// 发送信号给上位机，启动测量
				u3_printf("Measure !\r\n");
				printf("9\r\n");
			}
			
			USART3_RX_BUF[len] = 0;							// 加结束符
			printf("Bluetooth: %s\r\n", USART3_RX_BUF);		// 发送数据到上位机
			USART3_RX_STA = 0;
		}
		
		// 串口
		if ( USART_RX_STA & 0x8000 )
		{
			u8 len = USART_RX_STA & 0x3fff;	// 得到此次接收到的数据长度
			
			if ( USART_RX_BUF[0] == '1' )
			{
				FOCUS_O = 1;		// 调焦电机方向变为默认方向
				FOCUS_T = 0;		// 调焦电机开始转动
				delay_ms(1000);		// 转动时长
				FOCUS_T = 1;		// 调焦电机停止转动
				
				printf("Focus - reduce !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '2' )
			{
				FOCUS_O = 0;		// 调焦电机方向变为相反方向
				FOCUS_T = 0;		// 调焦电机开始转动
				delay_ms(1000);		// 转动时长
				FOCUS_T = 1;		// 调焦电机停止转动
				FOCUS_O = 1;		// 调焦电机方向变为默认方向
				
				printf("Focus - increase !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '3' )
			{
				ZOOM_O = 1;			// 变倍电机方向变为默认方向
				ZOOM_T = 0;			// 变倍电机开始转动
				delay_ms(1000);		// 转动时长
				ZOOM_T = 1;			// 变倍电机停止转动
				
				printf("Zoom - reduce !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '4' )
			{
				ZOOM_O = 0;			// 变倍电机方向变为相反方向
				ZOOM_T = 0;			// 变倍电机开始转动
				delay_ms(1000);		// 转动时长
				ZOOM_T = 1;			// 变倍电机停止转动
				ZOOM_O = 1;			// 变倍电机方向变为默认方向
				
				printf("Zoom - increase !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '5' )
			{
				BRIGHT_O = 1;		// 明亮度电机方向变为默认方向
				BRIGHT_T = 0;		// 明亮度电机开始转动
				delay_ms(1000);		// 转动时长
				BRIGHT_T = 1;		// 明亮度电机停止转动
				
				printf("Bright - reduce !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '6' )
			{
				BRIGHT_O = 0;		// 明亮度电机方向变为相反方向
				BRIGHT_T = 0;		// 明亮度电机开始转动
				delay_ms(1000);		// 转动时长
				BRIGHT_T = 1;		// 明亮度电机停止转动
				BRIGHT_O = 1;		// 明亮度电机方向变为默认方向
				
				printf("Bright - increase !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '7' )
			{
				CONTRAST_O = 1;		// 对比度电机方向变为默认方向
				CONTRAST_T = 0;		// 对比度电机开始转动
				delay_ms(1000);		// 转动时长
				CONTRAST_T = 1;		// 对比度电机停止转动
				
				printf("Contrast - reduce !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '8' )
			{
				CONTRAST_O = 0;		// 对比度电机方向变为相反方向
				CONTRAST_T = 0;		// 对比度电机开始转动
				delay_ms(1000);		// 转动时长
				CONTRAST_T = 1;		// 对比度电机停止转动
				CONTRAST_O = 1;		// 对比度电机方向变为默认方向
				
				printf("Contrast - increase !\r\n");
			}
			
			/*
			printf("Com:  ");
			for ( u8 t = 0; t < len; ++t )
			{
				USART_SendData(USART1, USART_RX_BUF[t]);         			// 发送数据到上位机
				while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);	// 等待发送结束
			}
			printf("\r\n");	// 插入换行
			*/
			USART_RX_STA = 0;
		}
		
		// 红外
		if ( infrared != 0 )
		{
			u8 key = 0;
			
			key = Remote_Scan();

			if ( key != 0 ) 
			{	
				switch(key)
				{
				case 162: 	LED0 = 0;	break;	// CH-
				case 98: 	LED0 = 1;	break;	// CH
				case 226: 	break;	// CH+
				
				case 34: 	LED1 = 0;	break;	// PREV
				case 2:		LED1 = 1;	break;	// NEXT
				case 194:	break;	// PLAY
				
				case 224:	BEEP = 1;	break;	// VOL-
				case 168:	BEEP = 0;	break;	// VOL+
				case 144:	break;	// EQ
				
				case 104: {
					FOCUS_O = 1;		// 调焦电机方向变为默认方向
					FOCUS_T = 0;		// 调焦电机开始转动
					delay_ms(1000);		// 转动时长
					FOCUS_T = 1;		// 调焦电机停止转动
				
					printf("Focus - reduce !\r\n");
				} break;	// 0
				
				case 152: {
					FOCUS_O = 0;		// 调焦电机方向变为相反方向
					FOCUS_T = 0;		// 调焦电机开始转动
					delay_ms(1000);		// 转动时长
					FOCUS_T = 1;		// 调焦电机停止转动
					FOCUS_O = 1;		// 调焦电机方向变为默认方向
				
					printf("Focus - increase !\r\n");
				} break;	// 100+
				
				case 176: {
					ZOOM_O = 1;			// 变倍电机方向变为默认方向
					ZOOM_T = 0;			// 变倍电机开始转动
					delay_ms(1000);		// 转动时长
					ZOOM_T = 1;			// 变倍电机停止转动
				
					printf("Zoom - reduce !\r\n");
				} break;	// 200+
				
				case 48: {
					ZOOM_O = 0;			// 变倍电机方向变为相反方向
					ZOOM_T = 0;			// 变倍电机开始转动
					delay_ms(1000);		// 转动时长
					ZOOM_T = 1;			// 变倍电机停止转动
					ZOOM_O = 1;			// 变倍电机方向变为默认方向
				
					printf("Zoom - increase !\r\n");
				} break;	// 1
				
				case 24: {
					BRIGHT_O = 1;		// 明亮度电机方向变为默认方向
					BRIGHT_T = 0;		// 明亮度电机开始转动
					delay_ms(1000);		// 转动时长
					BRIGHT_T = 1;		// 明亮度电机停止转动
				
					printf("Bright - reduce !\r\n");
				} break;	// 2
				
				case 122: {
					BRIGHT_O = 0;		// 明亮度电机方向变为相反方向
					BRIGHT_T = 0;		// 明亮度电机开始转动
					delay_ms(1000);		// 转动时长
					BRIGHT_T = 1;		// 明亮度电机停止转动
					BRIGHT_O = 1;		// 明亮度电机方向变为默认方向
				
					printf("Bright - increase !\r\n");
				} break;	// 3
				
				case 16: {
					CONTRAST_O = 1;		// 对比度电机方向变为默认方向
					CONTRAST_T = 0;		// 对比度电机开始转动
					delay_ms(1000);		// 转动时长
					CONTRAST_T = 1;		// 对比度电机停止转动
				
					printf("Contrast - reduce !\r\n");
				} break;	// 4
				
				case 56: {
					CONTRAST_O = 0;		// 对比度电机方向变为相反方向
					CONTRAST_T = 0;		// 对比度电机开始转动
					delay_ms(1000);		// 转动时长
					CONTRAST_T = 1;		// 对比度电机停止转动
					CONTRAST_O = 1;		// 对比度电机方向变为默认方向
				
					printf("Contrast - increase !\r\n");
				} break;	// 5
				
				case 90: {
					printf("Contrast !\r\n");
				} break;	// 6
				
				case 66: {
					printf("8\r\n");
				} break;	// 7
				
				case 74: {
					printf("9\r\n");
				} break;	// 8
				
				case 82: break;	// 9
				}
			}
		}

		delay_ms(10);
	}
}
