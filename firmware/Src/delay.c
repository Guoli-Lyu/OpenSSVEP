#include "delay.h"
#define u8  uint8_t  
#define u16 uint16_t 
#define u32 uint32_t 
//static u8  fac_us=0;							//us��ʱ������			   
//static u16 fac_ms=0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��
			   
//��ʼ���ӳٺ���
//��ʹ��OS��ʱ��,�˺������ʼ��OS��ʱ�ӽ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
//void delay_init(void){
//	fac_us=SystemCoreClock/1000000;				//Ϊϵͳʱ��  
//	fac_ms=(u16)fac_us*1000;							//��OS��,����ÿ��ms��Ҫ��systickʱ����   
//}						
//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(uint32_t nus)   {     
	uint32_t ticks;     
	uint32_t told,tnow,tcnt=0;     
	uint32_t reload=SysTick->LOAD;	//LOAD��ֵ     
	ticks=nus*64;//��Ҫ�Ľ�����     
	tcnt=0;     
	told=SysTick->VAL;//�ս���ʱ�ļ�����ֵ     
	while(1){         
		tnow=SysTick->VAL;         
		if(tnow!=told){             
			if(tnow<told)
				tcnt+=told-tnow;        //����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.            
			else 
				tcnt+=reload-tnow+told;             
			told=tnow;             
			if(tcnt>=ticks)break;			//����/����Ҫ�ӳٵ�ʱ��,���˳�.           
			}       
	};  
} 
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	uint32_t ticks;     
	uint32_t told,tnow,tcnt=0;     
	uint32_t reload=SysTick->LOAD;	//LOAD��ֵ     
	ticks=nms*64000;//��Ҫ�Ľ�����     
	tcnt=0;     
	told=SysTick->VAL;//�ս���ʱ�ļ�����ֵ     
	while(1){         
		tnow=SysTick->VAL;         
		if(tnow!=told){             
			if(tnow<told)
				tcnt+=told-tnow;        //����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.            
			else 
				tcnt+=reload-tnow+told;             
			told=tnow;             
			if(tcnt>=ticks)break;			//����/����Ҫ�ӳٵ�ʱ��,���˳�.           
			}       
	};  	    
} 


/*
void delay_us(uint32_t nus){		
	uint32_t i;
	uint16_t time = 2;
	for(i=0;i<nus;i++){
		while(time--);
	}
}

void delay_ms(uint32_t nms){		
	uint32_t i;
	uint16_t time = 11900;
	for(i=0;i<nms;i++){
		while(time--);
	}
}*/
