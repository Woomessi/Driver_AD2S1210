#include "DRV8301.h"

void DRV8301GPIOInitiate(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    NOCTW_GPIO_CLK_ENABLE();
    NFAULT_GPIO_CLK_ENABLE();
    NSCS_DRV8301_GPIO_CLK_ENABLE();
    SCLK_DRV8301_GPIO_CLK_ENABLE();
    SDO_DRV8301_GPIO_CLK_ENABLE();
    SDI_DRV8301_GPIO_CLK_ENABLE();
    DC_CAL_GPIO_CLK_ENABLE();
    EN_GATE_GPIO_CLK_ENABLE();
    INH_A_GPIO_CLK_ENABLE();
    INL_A_GPIO_CLK_ENABLE();
    INH_B_GPIO_CLK_ENABLE();
    INL_B_GPIO_CLK_ENABLE();
    INH_C_GPIO_CLK_ENABLE();
    INL_C_GPIO_CLK_ENABLE();
    SO1_GPIO_CLK_ENABLE();
    SO2_GPIO_CLK_ENABLE();

    gpio_init_struct.Pin = NOCTW_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(NOCTW_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = NFAULT_GPIO_PIN;
    HAL_GPIO_Init(NFAULT_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = NSCS_DRV8301_GPIO_PIN;
    HAL_GPIO_Init(NSCS_DRV8301_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = SCLK_DRV8301_GPIO_PIN;
    HAL_GPIO_Init(SCLK_DRV8301_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = SDI_DRV8301_GPIO_PIN;
    HAL_GPIO_Init(SDI_DRV8301_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = DC_CAL_GPIO_PIN;
    HAL_GPIO_Init(DC_CAL_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = EN_GATE_GPIO_PIN;
    HAL_GPIO_Init(EN_GATE_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = INH_A_GPIO_PIN;
    HAL_GPIO_Init(INH_A_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = INL_A_GPIO_PIN;
    HAL_GPIO_Init(INL_A_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = INH_B_GPIO_PIN;
    HAL_GPIO_Init(INH_B_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = INL_B_GPIO_PIN;
    HAL_GPIO_Init(INL_B_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = INH_C_GPIO_PIN;
    HAL_GPIO_Init(INH_C_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = INL_C_GPIO_PIN;
    HAL_GPIO_Init(INL_C_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = SO1_GPIO_PIN;
    HAL_GPIO_Init(SO1_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = SO2_GPIO_PIN;
    HAL_GPIO_Init(SO2_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = SDO_DRV8301_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SDO_DRV8301_GPIO_PORT, &gpio_init_struct);

    // gpio_init_struct.Pin = SDO_GPIO_PIN;
    // gpio_init_struct.Mode = GPIO_MODE_INPUT;
    // // gpio_init_struct.Pull = GPIO_NOPULL;
    // HAL_GPIO_Init(SDO_GPIO_PORT, &gpio_init_struct);
}

// void chipselect(u8 status)
// {
//     if (status == 0)
//     {
//         GPIOD->BSRRH |= 0x01 << 2;
//     }
//     else if (status == 1)
//     {
//         GPIOD->BSRRL |= 0x01 << 2;
//     }
// }

// u16 spi3transfer(u16 data){
//     while(!(SPI3->SR & 0x01 << 1));
//     SPI3->DR = data;
//     while(!(SPI3->SR & 0x01));
//     return SPI3->DR;
// }

void spi3init(void){
    RCC->AHB1ENR |= 0x01 << 2 | 0x01 << 3;

    GPIOC->MODER &= ~(0x03 << 20 | 0x03 << 22 | 0x03 << 24);
    GPIOD->MODER &= ~(0x03 << 4);

    GPIOC->MODER |= 0x01 << 20 | 0x01 << 24;
    GPIOD->MODER |= 0x01 << 4;

    GPIOC->OTYPER &= ~(0x01 << 10 | 0x01 << 12);
    GPIOD->OTYPER &= ~(0x01 << 2);

    GPIOC->OSPEEDR &= ~(0x03 << 20 | 0x03 << 24);
    GPIOD->OSPEEDR &= ~(0x03 << 4);
    
    GPIOC->OSPEEDR |= 0x03 << 20 | 0x03 << 24;
    GPIOD->OSPEEDR |= 0x03 << 4;

    GPIOC->PUPDR &= ~(0x03 << 20 | 0x03 << 22 | 0x03 << 24);
    GPIOD->PUPDR &= ~(0x03 << 4);

    GPIOC->BSRRH |= 0x01 << 10 | 0x01 << 12;

    GPIOD->BSRRL |= 0x01 << 2;
}

void chipselect(u8 status)
{
    if (status)
    {
        GPIOD->BSRRL |= 0x01 << 2;
    }
    else
    {
        GPIOD->BSRRH |= 0x01 << 2;
    }
}

void spi3sck(u8 clk)
{
    if (clk)
    {
        GPIOC->BSRRL |= 0x01 << 10;
    }
    else
    {
        GPIOC->BSRRH |= 0x01 << 10;
    }
}

void spi3writeword(u16 data)
{
    u8 i;
    chipselect(0);
    for (i = 0; i < 16; i++)
    {
        spi3sck(1);
        if (data & 0x8000 >> i)
        {
            GPIOC->BSRRL |= 0x01 << 12;
        }
        else
        {
            GPIOC->BSRRH |= 0x01 << 12;
        }
        spi3sck(0);
    }
    GPIOC->BSRRH |= 0x01 << 12;
    chipselect(1);
}

u16 spi3readword(void){
    u8 i;
    u16 data = 0;
    chipselect(0);
    for(i = 0; i < 16; i++){
        spi3sck(1);
        spi3sck(0);
        if(GPIOC->IDR & 0x01 << 11){
            data |= 0x8000 >> i;
        }
    }
    chipselect(1);
    return data;
}

void enablegate(void){
    RCC->AHB1ENR |= 0x01 << 6;
    GPIOG->MODER &= ~(0x03 << 12);
    GPIOG->MODER |= 0x01 << 12;
    GPIOG->OTYPER &= ~(0x01 << 6);
    GPIOG->OSPEEDR &= ~(0x03 << 12);
    GPIOG->PUPDR &= ~(0x03 << 12);
    GPIOG->BSRRL |= 0x01 << 6;
}

u16 DRV8301IDread(void){
    u16 command = 0;
    u16 regvalue = 0;
    command = DRV8301READ | REGSTATUS2 << 11;
    urtprintf("command = %d\r\n", command);
    spi3writeword(command);
    regvalue = spi3readword();
    return regvalue & 0x0f;
}

u8 DRV8301Init(DRV8301Cfg cfg){
    enablegate();
    timer6delayms(500);
    u16 wconfig = 0;
    u16 rconfig = 0;
    u16 regvalue = 0;
    wconfig = DRV8301WRITE | REGCTRL1 << 11 | cfg.GATE_CURRENT | cfg.GATE_RESET | cfg.PWM_MODE | cfg.OCP_MODE | cfg.OC_ADJ_SET;
    urtprintf("wconfig1 = %d\r\n", wconfig);
    spi3writeword(wconfig);
    rconfig = DRV8301READ | REGCTRL1 << 11;
    spi3writeword(rconfig);
    regvalue = spi3readword();
    urtprintf("regvalue = %d\r\n", regvalue);
    if((regvalue & 0x07ff) != (wconfig &0x07ff)){
        return 1;
    }
    wconfig = 0;
    wconfig = DRV8301WRITE | REGCTRL2 << 11 | cfg.OCTW_MODE | cfg.GAINVALUE | cfg.DC_CAL_CH1 | cfg.DC_CAL_CH2 | cfg.OC_TOFF << 6;
    urtprintf("wconfig2 = %d\r\n", wconfig);
    spi3writeword(wconfig);
    rconfig = DRV8301READ | REGCTRL2 << 11;
    spi3writeword(rconfig);
    regvalue = spi3readword();
    urtprintf("regvalue2 = %d\r\n", regvalue);
    if((regvalue & 0x007f) != (wconfig & 0x007f)){
        return 2;
    }
    return 0;

}