#include "system.h"
#include "stm32f4xx.h"

uint32_t runtime = 0;

// 系统滴答时钟使能
void Systick_Init(void)
{
    if (SysTick_Config(SystemCoreClock / 1000))
    { 
        /* Capture error */ 
        while (1);
    }
}

// ms延时函数
void delay_ms(uint16_t msec)
{
    uint32_t target_time = runtime + msec;
    while(runtime <= target_time);
}

// NVIC向量表配置
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef nvic;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    // 读取裁判系统
    nvic.NVIC_IRQChannel = USART3_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
}

void System_Init(void)
{
    NVIC_Configuration();
    Systick_Init();
}

// systick函数 1ms自加一次
extern "C" void SysTick_Handler(void)
{
    runtime++;
}

uint32_t System_GetTime(void)
{
    return runtime;
}
