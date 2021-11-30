/**
 * @file ESC.h
 * @author CubLWolf
 * @brief 对ESC外设以及相对应的片内设置进行初始化
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __ESC_H
#define __ESC_H

/*include files*/
#include "stm32f4xx.h"

extern uint32_t PWM_Value1, PWM_Value2, PWM_Value3, PWM_Value4; //PWM的值

GPIO_InitTypeDef GPIO_Initure;
TIM_HandleTypeDef TIM2_Handler;                                 //有关GPIO与定时器初始化的结构体
TIM_OC_InitTypeDef TIM2_CH1_PWMHandler;
TIM_OC_InitTypeDef TIM2_CH2_PWMHandler;
TIM_OC_InitTypeDef TIM2_CH3_PWMHandler;
TIM_OC_InitTypeDef TIM2_CH4_PWMHandler;                         //PWM输出通道设备句柄

/*初始化ESC外设以及芯片内置资源*/
void ESC_Init();

/*PWM定时器回调函数，进行GPIO的设置与初始化*/
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);

/*重新设置PWM寄存器的值*/
void ESC_PWM_Value_Set(uint32_t PWM_Value);

#endif