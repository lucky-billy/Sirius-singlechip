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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	// ����ϵͳ�ж����ȼ�����2
	delay_init(168);			// ��ʱ��ʼ�� 
	uart_init(9600);			// ���ڳ�ʼ��
	
	LED_Init();		  			// ��ʼ��LED
	BEEP_Init(); 				// ��ʼ��������
	Remote_Init();				// ��ʼ��������
	
	while ( HC05_Init() ) 		// ��ʼ��HC05����ģ��
	{
		delay_ms(100);
	}

	while(1)
	{
		// ����
		if( USART3_RX_STA & 0X8000 )
		{
			u8 len = USART3_RX_STA & 0X7FFF;
			
			// ��������ť
			if ( USART3_RX_BUF[0] == '1' ) {
				LED0 = 1;		// ֹͣת��
				delay_ms(10);
				LED1 = 1;		// ���÷���Ϊ����
				delay_ms(10);
				LED0 = 0;		// ��ʼת��
				
				delay_ms(100);	// ת��ʱ��
				
				LED0 = 1;		// ֹͣת��
					
				u3_printf("Focus - reduce !\r\n");
			}
				
			// ��������ť
			if ( USART3_RX_BUF[0] == '2' ) {
				LED0 = 1;		// ֹͣת��
				delay_ms(10);
				LED1 = 0;		// ���÷���Ϊ����
				delay_ms(10);
				LED0 = 0;		// ��ʼת��
				
				delay_ms(100);	// ת��ʱ��
				
				LED0 = 1;		// ֹͣת��
					
				u3_printf("Focus - increase !\r\n");
			}
			
			// �䱶����ť
			if ( USART3_RX_BUF[0] == '3' ) {
				LED0 = 1;		// ֹͣת��
				delay_ms(10);
				LED1 = 1;		// ���÷���Ϊ����
				delay_ms(10);
				LED0 = 0;		// ��ʼת��
				
				delay_ms(100);	// ת��ʱ��
				
				LED0 = 1;		// ֹͣת��
					
				u3_printf("Zoom - reduce !\r\n");
			}
				
			//  �䱶����ť
			if ( USART3_RX_BUF[0] == '4' ) {
				LED0 = 1;		// ֹͣת��
				delay_ms(10);
				LED1 = 0;		// ���÷���Ϊ����
				delay_ms(10);
				LED0 = 0;		// ��ʼת��
				
				delay_ms(100);	// ת��ʱ��
				
				LED0 = 1;		// ֹͣת��
					
				u3_printf("Zoom - increase !\r\n");
			}
			
			// �ⰵ��������ť
			if ( USART3_RX_BUF[0] == '5' ) {
				LED0 = 1;		// ֹͣת��
				delay_ms(10);
				LED1 = 1;		// ���÷���Ϊ����
				delay_ms(10);
				LED0 = 0;		// ��ʼת��
				
				delay_ms(100);	// ת��ʱ��
				
				LED0 = 1;		// ֹͣת��
					
				u3_printf("Brightness - reduce !\r\n");
			}
				
			// �ⰵ��������ť
			if ( USART3_RX_BUF[0] == '6' ) {
				LED0 = 1;		// ֹͣת��
				delay_ms(10);
				LED1 = 0;		// ���÷���Ϊ����
				delay_ms(10);
				LED0 = 0;		// ��ʼת��
				
				delay_ms(100);	// ת��ʱ��
				
				LED0 = 1;		// ֹͣת��
					
				u3_printf("Brightness - increase !\r\n");
			}

			// �Աȶ�
			if ( USART3_RX_BUF[0] == '7' ) {
				u3_printf("Contrast !\r\n");
			}
			
			// ��׼
			if ( USART3_RX_BUF[0] == '8' ) {
				u3_printf("Align !\r\n");
			}
			
			// ����
			if ( USART3_RX_BUF[0] == '9' ) {
				u3_printf("Measure !\r\n");
			}
			
			USART3_RX_BUF[len] = 0;							// �ӽ�����
			printf("Bluetooth: %s\r\n", USART3_RX_BUF);		// ���ͻ�Ӧ���ݵ�����1
			
			USART3_RX_STA = 0;
		}
		
		// ����
		if ( USART_RX_STA & 0x8000 )
		{
			u8 len = USART_RX_STA & 0x3fff;	// �õ��˴ν��յ������ݳ���
			
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
				USART_SendData(USART1, USART_RX_BUF[t]);         			// �򴮿�1��������
				while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);	// �ȴ����ͽ���
			}
			printf("\r\n");	// ���뻻��
			USART_RX_STA = 0;
		}
		
		// ����
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
