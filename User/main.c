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
  
	AD2S1210Initiate();//上电时序控制和复位
		
	CLR_SOE();
	SET_RD();//串口通信需将RD拉高
	
	AD2S1210SelectMode(CONFIG); //进入配置模式，对寄存器进行编程，以设置AD2S1210的激励频率、分辨率和故障检测阈值
  
  unsigned	char	buf[4] = {0,0,0,0};
	unsigned	char	error[4] = {0,0,0,0};
	//uint8_t a = 1;
	//uint8_t* buf = &a;
	
	/* 检查读写功能是否正常 */
	//WriteToAD2S1210(CONTROL, 0x7A); //默认0x7E
	//ReadFromAD2S1210(CONFIG, CONTROL, buf);
  
	SET_SPL();
	delay_ms(1);
	CLR_SPL();
  delay_ms(5);
	ReadFromAD2S1210(CONFIG, FAULT, buf); 		//read/clear fault register
	SET_SPL();
	delay_ms(1);
	CLR_SPL();
	
	CLR_RES0();
	SET_RES1();//控制寄存器中的分辨率位应与RES0, RES1输入引脚的电平保持一致，默认为12位

  //ReadFromAD2S1210(CONFIG, EXFREQUENCY, buf); //默认频率控制字FCW为28H，对应的激励频率为10kHz

  while (1)
  {
		//putchar(buf[0]);
		//printf("%d\n",buf[0]);
		
		AD2S1210SelectMode(POSITION);
		ReadFromAD2S1210(POSITION, POS_VEL, buf);		//read data register
	  putchar(buf[2]);
	  putchar(buf[1]);
	  putchar(buf[0]);
		
		AD2S1210SelectMode(CONFIG);
		SET_SPL();
	  delay_ms(1);
	  CLR_SPL();
    delay_ms(5);
	  ReadFromAD2S1210(CONFIG, FAULT, error); 		//read/clear fault register
	  SET_SPL();
	  delay_ms(1);
	  CLR_SPL();
		putchar(error[0]);
		
//	  AD2S1210SelectMode(VELOCITY);		//Normal Mode velocity output						   
//	  ReadFromAD2S1210(VELOCITY, POS_VEL, buf);		//read data register
//	  putchar(buf[2]);
//	  putchar(buf[1]);
//	  putchar(buf[0]);
		
		delay_ms(300);
  }
}




