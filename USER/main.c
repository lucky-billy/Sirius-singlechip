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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	// ����ϵͳ�ж����ȼ�����2
	delay_init(168);			// ��ʱ��ʼ�� 
	uart_init(9600);			// ���ڳ�ʼ��
	
	LED_Init();		  			// ��ʼ��LED
	BEEP_Init(); 				// ��ʼ��������
	Remote_Init();				// ��ʼ��������
	BCOMPONENT_Init();			// ��ʼ���Զ�������
	
	while ( HC05_Init() ) 		// ��ʼ��HC05����ģ��
	{
		delay_ms(100);
	}
	
	u8 infrared = 0;

	while(1)
	{
		// ����
		if( USART3_RX_STA & 0X8000 )
		{
			u8 len = USART3_RX_STA & 0X7FFF;
			
			// ��������ť
			if ( USART3_RX_BUF[0] == '1' ) {
				FOCUS_O = 1;		// ������������ΪĬ�Ϸ���
				FOCUS_T = 0;		// ���������ʼת��
				delay_ms(1000);		// ת��ʱ��
				FOCUS_T = 1;		// �������ֹͣת��
					
				u3_printf("Focus - reduce !\r\n");
			}
				
			// ��������ť
			if ( USART3_RX_BUF[0] == '2' ) {
				FOCUS_O = 0;		// ������������Ϊ�෴����
				FOCUS_T = 0;		// ���������ʼת��
				delay_ms(1000);		// ת��ʱ��
				FOCUS_T = 1;		// �������ֹͣת��
				FOCUS_O = 1;		// ������������ΪĬ�Ϸ���
					
				u3_printf("Focus - increase !\r\n");
			}
			
			// �䱶����ť
			if ( USART3_RX_BUF[0] == '3' ) {
				ZOOM_O = 1;			// �䱶��������ΪĬ�Ϸ���
				ZOOM_T = 0;			// �䱶�����ʼת��
				delay_ms(1000);		// ת��ʱ��
				ZOOM_T = 1;			// �䱶���ֹͣת��
					
				u3_printf("Zoom - reduce !\r\n");
			}
				
			//  �䱶����ť
			if ( USART3_RX_BUF[0] == '4' ) {
				ZOOM_O = 0;			// �䱶��������Ϊ�෴����
				ZOOM_T = 0;			// �䱶�����ʼת��
				delay_ms(1000);		// ת��ʱ��
				ZOOM_T = 1;			// �䱶���ֹͣת��
				ZOOM_O = 1;			// �䱶��������ΪĬ�Ϸ���
					
				u3_printf("Zoom - increase !\r\n");
			}

			// �Աȶ�
			if ( USART3_RX_BUF[0] == '7' ) {
				// �ȸ�����λȷ��λ�ã���ת����һ��λ��
				u3_printf("Contrast !\r\n");
			}
			
			// ��׼
			if ( USART3_RX_BUF[0] == '8' ) {
				// �����źŸ���λ�����򿪶�׼���
				u3_printf("Align !\r\n");
				printf("8\r\n");
			}
			
			// ����
			if ( USART3_RX_BUF[0] == '9' ) {
				// �����źŸ���λ������������
				u3_printf("Measure !\r\n");
				printf("9\r\n");
			}
			
			USART3_RX_BUF[len] = 0;							// �ӽ�����
			printf("Bluetooth: %s\r\n", USART3_RX_BUF);		// �������ݵ���λ��
			USART3_RX_STA = 0;
		}
		
		// ����
		if ( USART_RX_STA & 0x8000 )
		{
			u8 len = USART_RX_STA & 0x3fff;	// �õ��˴ν��յ������ݳ���
			
			if ( USART_RX_BUF[0] == '1' )
			{
				FOCUS_O = 1;		// ������������ΪĬ�Ϸ���
				FOCUS_T = 0;		// ���������ʼת��
				delay_ms(1000);		// ת��ʱ��
				FOCUS_T = 1;		// �������ֹͣת��
				
				printf("Focus - reduce !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '2' )
			{
				FOCUS_O = 0;		// ������������Ϊ�෴����
				FOCUS_T = 0;		// ���������ʼת��
				delay_ms(1000);		// ת��ʱ��
				FOCUS_T = 1;		// �������ֹͣת��
				FOCUS_O = 1;		// ������������ΪĬ�Ϸ���
				
				printf("Focus - increase !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '3' )
			{
				ZOOM_O = 1;			// �䱶��������ΪĬ�Ϸ���
				ZOOM_T = 0;			// �䱶�����ʼת��
				delay_ms(1000);		// ת��ʱ��
				ZOOM_T = 1;			// �䱶���ֹͣת��
				
				printf("Zoom - reduce !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '4' )
			{
				ZOOM_O = 0;			// �䱶��������Ϊ�෴����
				ZOOM_T = 0;			// �䱶�����ʼת��
				delay_ms(1000);		// ת��ʱ��
				ZOOM_T = 1;			// �䱶���ֹͣת��
				ZOOM_O = 1;			// �䱶��������ΪĬ�Ϸ���
				
				printf("Zoom - increase !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '5' )
			{
				BRIGHT_O = 1;		// �����ȵ�������ΪĬ�Ϸ���
				BRIGHT_T = 0;		// �����ȵ����ʼת��
				delay_ms(1000);		// ת��ʱ��
				BRIGHT_T = 1;		// �����ȵ��ֹͣת��
				
				printf("Bright - reduce !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '6' )
			{
				BRIGHT_O = 0;		// �����ȵ�������Ϊ�෴����
				BRIGHT_T = 0;		// �����ȵ����ʼת��
				delay_ms(1000);		// ת��ʱ��
				BRIGHT_T = 1;		// �����ȵ��ֹͣת��
				BRIGHT_O = 1;		// �����ȵ�������ΪĬ�Ϸ���
				
				printf("Bright - increase !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '7' )
			{
				CONTRAST_O = 1;		// �Աȶȵ�������ΪĬ�Ϸ���
				CONTRAST_T = 0;		// �Աȶȵ����ʼת��
				delay_ms(1000);		// ת��ʱ��
				CONTRAST_T = 1;		// �Աȶȵ��ֹͣת��
				
				printf("Contrast - reduce !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '8' )
			{
				CONTRAST_O = 0;		// �Աȶȵ�������Ϊ�෴����
				CONTRAST_T = 0;		// �Աȶȵ����ʼת��
				delay_ms(1000);		// ת��ʱ��
				CONTRAST_T = 1;		// �Աȶȵ��ֹͣת��
				CONTRAST_O = 1;		// �Աȶȵ�������ΪĬ�Ϸ���
				
				printf("Contrast - increase !\r\n");
			}
			
			/*
			printf("Com:  ");
			for ( u8 t = 0; t < len; ++t )
			{
				USART_SendData(USART1, USART_RX_BUF[t]);         			// �������ݵ���λ��
				while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);	// �ȴ����ͽ���
			}
			printf("\r\n");	// ���뻻��
			*/
			USART_RX_STA = 0;
		}
		
		// ����
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
					FOCUS_O = 1;		// ������������ΪĬ�Ϸ���
					FOCUS_T = 0;		// ���������ʼת��
					delay_ms(1000);		// ת��ʱ��
					FOCUS_T = 1;		// �������ֹͣת��
				
					printf("Focus - reduce !\r\n");
				} break;	// 0
				
				case 152: {
					FOCUS_O = 0;		// ������������Ϊ�෴����
					FOCUS_T = 0;		// ���������ʼת��
					delay_ms(1000);		// ת��ʱ��
					FOCUS_T = 1;		// �������ֹͣת��
					FOCUS_O = 1;		// ������������ΪĬ�Ϸ���
				
					printf("Focus - increase !\r\n");
				} break;	// 100+
				
				case 176: {
					ZOOM_O = 1;			// �䱶��������ΪĬ�Ϸ���
					ZOOM_T = 0;			// �䱶�����ʼת��
					delay_ms(1000);		// ת��ʱ��
					ZOOM_T = 1;			// �䱶���ֹͣת��
				
					printf("Zoom - reduce !\r\n");
				} break;	// 200+
				
				case 48: {
					ZOOM_O = 0;			// �䱶��������Ϊ�෴����
					ZOOM_T = 0;			// �䱶�����ʼת��
					delay_ms(1000);		// ת��ʱ��
					ZOOM_T = 1;			// �䱶���ֹͣת��
					ZOOM_O = 1;			// �䱶��������ΪĬ�Ϸ���
				
					printf("Zoom - increase !\r\n");
				} break;	// 1
				
				case 24: {
					BRIGHT_O = 1;		// �����ȵ�������ΪĬ�Ϸ���
					BRIGHT_T = 0;		// �����ȵ����ʼת��
					delay_ms(1000);		// ת��ʱ��
					BRIGHT_T = 1;		// �����ȵ��ֹͣת��
				
					printf("Bright - reduce !\r\n");
				} break;	// 2
				
				case 122: {
					BRIGHT_O = 0;		// �����ȵ�������Ϊ�෴����
					BRIGHT_T = 0;		// �����ȵ����ʼת��
					delay_ms(1000);		// ת��ʱ��
					BRIGHT_T = 1;		// �����ȵ��ֹͣת��
					BRIGHT_O = 1;		// �����ȵ�������ΪĬ�Ϸ���
				
					printf("Bright - increase !\r\n");
				} break;	// 3
				
				case 16: {
					CONTRAST_O = 1;		// �Աȶȵ�������ΪĬ�Ϸ���
					CONTRAST_T = 0;		// �Աȶȵ����ʼת��
					delay_ms(1000);		// ת��ʱ��
					CONTRAST_T = 1;		// �Աȶȵ��ֹͣת��
				
					printf("Contrast - reduce !\r\n");
				} break;	// 4
				
				case 56: {
					CONTRAST_O = 0;		// �Աȶȵ�������Ϊ�෴����
					CONTRAST_T = 0;		// �Աȶȵ����ʼת��
					delay_ms(1000);		// ת��ʱ��
					CONTRAST_T = 1;		// �Աȶȵ��ֹͣת��
					CONTRAST_O = 1;		// �Աȶȵ�������ΪĬ�Ϸ���
				
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
