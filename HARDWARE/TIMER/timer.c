#include "timer.h"
#include "led.h"

extern vu16 USART3_RX_STA;

// ��ʱ��7�жϷ������		    
void TIM7_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)	// �Ǹ����ж�
	{	 			   
		USART3_RX_STA|=1<<15;		// ��ǽ������
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  	// ���TIM7�����жϱ�־    
		TIM_Cmd(TIM7, DISABLE);  	// �ر�TIM7 
	}	    
}
 
// ͨ�ö�ʱ���жϳ�ʼ��
// ����ʼ��ѡ��ΪAPB1��2������APB1Ϊ36M
// arr���Զ���װֵ��
// psc��ʱ��Ԥ��Ƶ��		 
void TIM7_Int_Init(u16 arr,u16 psc)
{	
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);	// TIM7ʱ��ʹ��    
	
	// ��ʱ��TIM7��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; 				// ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 				// ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // ����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); 		// ����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); 				// ʹ��ָ����TIM7�ж�,���������ж�
   
	TIM_Cmd(TIM7,ENABLE);	// ʹ�ܶ�ʱ��7
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	// ��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		// �����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			// IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);							// ����ָ���Ĳ�����ʼ��VIC�Ĵ���
}