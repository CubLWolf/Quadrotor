#include "ESC.h"

/**
 * @brief 对四旋翼来说，需要输出四路PWM来控制电调（ESC）设备，因此我选用了TIM2定时器的
 *        四个PWM通道进行控制。函数功能就是对涉及这四个通道的设备进行相应的设置。
 * 
 * @param arr 
 * @param psc 
 */
void ESC_Init(uint16_t arr, uint16_t psc){

    TIM2_Handler.Instance = TIM2;                                                      //定时器句柄指向定时器2
    TIM2_Handler.Init.Prescaler = psc;                                                 //定时器分频数值设置
    TIM2_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;                                //设置为向上计数模式
    TIM2_Handler.Init.Period = arr;                                                    //自动重装PWM比较寄存器初值
    TIM2_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                          //设置晶振分频模式
    HAL_TIM_PWM_Init(&TIM2_Handler);                                                   //初始化TIM2定时器的PWM设置

    /*通道一设置*/
    TIM2_CH1_PWMHandler.OCMode = TIM_OCMODE_PWM1;                                      //选择PWM1模式
    TIM2_CH1_PWMHandler.Pulse = arr/2;                                                 //设置占空比，初始化默认为50%
    TIM2_CH1_PWMHandler.OCPolarity = TIM_OCPOLARITY_LOW;                               //设置为低比较极性
    HAL_TIM_PWM_ConfigChannel(&TIM2_Handler, &TIM2_CH1_PWMHandler, TIM_CHANNEL_1);     //配置TIM2通道
    HAL_TIM_PWM_Start(&TIM2_Handler, TIM_CHANNEL_1);                                   //启动PWM通道1

    /*通道二设置*/
    TIM2_CH2_PWMHandler.OCMode = TIM_OCMODE_PWM1;
    TIM2_CH2_PWMHandler.Pulse = arr/2;
    TIM2_CH2_PWMHandler.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&TIM2_Handler, &TIM2_CH2_PWMHandler, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&TIM2_Handler, TIM_CHANNEL_2);

    /*通道三设置*/
    TIM2_CH3_PWMHandler.OCMode = TIM_OCMODE_PWM1;
    TIM2_CH3_PWMHandler.Pulse = arr/2;
    TIM2_CH3_PWMHandler.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&TIM2_Handler, &TIM2_CH3_PWMHandler, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&TIM2_Handler, TIM_CHANNEL_3);

    /*通道四设置*/
    TIM2_CH4_PWMHandler.OCMode = TIM_OCMODE_PWM1;
    TIM2_CH4_PWMHandler.Pulse = arr/2;
    TIM2_CH4_PWMHandler.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&TIM2_Handler, &TIM2_CH4_PWMHandler, TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(&TIM2_Handler, TIM_CHANNEL_4);

}

/**
 * @brief 函数为HAL_TIM_PWM_Init的回调函数，在这里我们进行输出PWM的I/O管脚的设置。
 * 
 * @param htim 
 */
void HAL_TIM_PWM_MSPInit(TIM_HandleTypeDef *htim){

    __HAL_RCC_TIM2_CLK_ENABLE();                                                       //使能TIM2时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();                                                      //使能GPIOA管脚时钟

    GPIO_Initure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;              //设置相应输出通道
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;                                               //设置为复用推挽输出模式
    GPIO_Initure.Pull = GPIO_PULLUP;                                                   //设置为上拉模式
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;                                              //启用高速时钟
    GPIO_Initure.Alternate = GPIO_AF1_TIM2;                                            //相应引脚分别复用为TIM2_CH1/2/3/4
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

}

/**
 * @brief PID调参后要实时设置PWM的输入值，函数功能为重新设置PWM输入值，内容细节不再赘述。
 * 
 */
void ESC_PWM_Value_Set(uint32_t PWM_Value1, \
                       uint32_t PWM_Value2, \
                       uint32_t PWM_Value3, \
                       uint32_t PWM_Value4){

    TIM2 -> CCR1 = PWM_Value1;
    TIM2 -> CCR2 = PWM_Value2;
    TIM2 -> CCR3 = PWM_Value3;
    TIM2 -> CCR4 = PWM_Value4;

}