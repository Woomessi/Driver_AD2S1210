#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/AD2S1210/AD2S1210.h"

int main(void)
{
  HAL_Init();                                 /* ��ʼ��HAL�� */
  sys_stm32_clock_init(85, 2, 2, 4, 8);       /* ����ʱ��,170Mhz */
  delay_init(170);                            /* ��ʱ��ʼ�� */
  usart_init(115200);                         /* ���ڳ�ʼ��Ϊ115200 */
	
	AD2S1210GPIOInitiate();
  
	AD2S1210Initiate();//�ϵ�ʱ����ƺ͸�λ
		
	CLR_SOE();
	SET_RD();//����ͨ���轫RD����
	
	AD2S1210SelectMode(CONFIG); //��������ģʽ���ԼĴ������б�̣�������AD2S1210�ļ���Ƶ�ʡ��ֱ��ʺ͹��ϼ����ֵ
  
  unsigned	char	buf[4] = {0,0,0,0};
	unsigned	char	error[4] = {0,0,0,0};
	//uint8_t a = 1;
	//uint8_t* buf = &a;
	
	/* ����д�����Ƿ����� */
	//WriteToAD2S1210(CONTROL, 0x7A); //Ĭ��0x7E
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
	SET_RES1();//���ƼĴ����еķֱ���λӦ��RES0, RES1�������ŵĵ�ƽ����һ�£�Ĭ��Ϊ12λ

  //ReadFromAD2S1210(CONFIG, EXFREQUENCY, buf); //Ĭ��Ƶ�ʿ�����FCWΪ28H����Ӧ�ļ���Ƶ��Ϊ10kHz

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




