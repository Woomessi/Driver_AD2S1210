#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/AD2S1210/AD2S1210.h"

int main(void)
{
  HAL_Init();                                 /* 初始化HAL库 */
  sys_stm32_clock_init(85, 2, 2, 4, 8);       /* 设置时钟,170Mhz */
  delay_init(170);                            /* 延时初始化 */
  usart_init(115200);                         /* 串口初始化为115200 */
	
	AD2S1210GPIOInitiate();
	
  AD2S1210Initiate();
	AD2S1210SelectMode(CONFIG);
	
	CLR_SOE();
	SET_RD();
	
	uint8_t a = 1;
	uint8_t* buf = &a;
	//WriteToAD2S1210(CONTROL, 0x7C);  	//write control register address 
	ReadFromAD2S1210(CONFIG, CONTROL, buf);
	
  while (1)
  {
		printf("%d\n",buf[0]);
		delay_ms(300);
  }
}




