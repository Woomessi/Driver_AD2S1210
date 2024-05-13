#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/AD2S1210/AD2S1210.h"
#include "./BSP/DRV8301_HAL/DRV8301.h"

int main(void)
{
    HAL_Init();                           /* 初始化HAL库 */
    sys_stm32_clock_init(85, 2, 2, 4, 8); /* 设置时钟,170Mhz */
    delay_init(170);                      /* 延时初始化 */
    usart_init(115200);                   /* 串口初始化为115200 */

//    AD2S1210GPIOInitiate();

//    AD2S1210Initiate(); // 上电时序控制和复位

//    CLR_SOE();
//    SET_RD(); // 串口通信需将RD拉高

//    AD2S1210SelectMode(CONFIG); // 进入配置模式，对寄存器进行编程，以设置AD2S1210的激励频率、分辨率和故障检测阈值

//    unsigned char buf[4] = {0, 0, 0, 0};
//    unsigned char error[4] = {0, 0, 0, 0};
//    float angle = 0;
//    unsigned short velocity0 = 0;
//    float velocity = 0;

//    /* 检查读写功能是否正常 */
//    // WriteToAD2S1210(CONTROL, 0x7A); //默认0x7E
//    // ReadFromAD2S1210(CONFIG, CONTROL, buf);

//    SET_SPL();
//    delay_ms(1);
//    CLR_SPL();
//    delay_ms(5);
//    ReadFromAD2S1210(CONFIG, FAULT, buf); // read/clear fault register
//    SET_SPL();
//    delay_ms(1);
//    CLR_SPL();

//    CLR_RES0();
//    SET_RES1(); // 控制寄存器中的分辨率位应与RES0, RES1输入引脚的电平保持一致，默认为12位

//    // ReadFromAD2S1210(CONFIG, EXFREQUENCY, buf); //默认频率控制字FCW为28H，对应的激励频率为10kHz
		
		//DRV8301 Initialization
		DRV8301GPIOInitiate();
		delay_ms(500);
		DRV8301Cfg cfg = {
			.GATE_CURRENT = CURRENT0_7A,//","
			.GATE_RESET = GATE_RST_NORMAL,
			.PWM_MODE = PHASE6PWM,
			.OCP_MODE = OCLATCHSTDOWN,
			.OC_ADJ_SET = 18,
			.OCTW_MODE = OCOTBOTH,
			.GAINVALUE = GAIN10,
			.DC_CAL_CH1 = CONNECTLOADPH1,
			.DC_CAL_CH2 = CONNECTLOADPH2,
			.OC_TOFF = CYCLEBYCYCLE//没有","
		};
		spi3init();
		DRV8301Init(cfg);
		delay_ms(500);
		uint16_t id = DRV8301IDread();
		printf("ID = %d\r\n", id);
		
		uint16_t rconfig = 0;
    while (1)
    {
//			id = DRV8301IDread();
//		  printf("ID = %d\r\n", id);
//			delay_ms(100);
//			
//			uint16_t wconfig = DRV8301WRITE | REGCTRL1 << 11 | cfg.GATE_CURRENT | cfg.GATE_RESET | cfg.PWM_MODE | cfg.OCP_MODE | cfg.OC_ADJ_SET;
//      spi3writeword(wconfig);
//      printf("wconfig1 = %d\r\n", wconfig);
//      delay_ms(100);

//      rconfig = DRV8301READ | REGCTRL1 << 11;
//      spi3writeword(rconfig);
//      uint16_t regvalue = spi3readword();
//      printf("regvalue1 = %d\r\n", regvalue);
//			delay_ms(100);
//			
//			rconfig = DRV8301READ | REGCTRL2 << 11;
//      spi3writeword(rconfig);
//      regvalue = spi3readword();
//      printf("regvalue2 = %d\r\n", regvalue);
//			delay_ms(100);
//			
//      wconfig = 0;
//      wconfig = DRV8301WRITE | REGCTRL2 << 11 | cfg.OCTW_MODE | cfg.GAINVALUE | cfg.DC_CAL_CH1 | cfg.DC_CAL_CH2 | cfg.OC_TOFF << 6;
//      spi3writeword(wconfig);
//      printf("wconfig2 = %d\r\n", wconfig);
//			delay_ms(100);
//			
//      rconfig = DRV8301READ | REGCTRL2 << 11;
//      spi3writeword(rconfig);
//      regvalue = spi3readword();
//      printf("regvalue2 = %d\r\n", regvalue);
//			delay_ms(100);

        //		AD2S1210SelectMode(CONFIG);
        //		SET_SPL();
        //	  delay_ms(1);
        //	  CLR_SPL();
        //    delay_ms(5);
        //	  ReadFromAD2S1210(CONFIG, FAULT, error); 		//read/clear fault register
        //	  SET_SPL();
        //	  delay_ms(1);
        //	  CLR_SPL();
        //		printf("%X\n",error[0]);

//        AD2S1210SelectMode(POSITION);
//        ReadFromAD2S1210(POSITION, POS_VEL, buf); // read data register
//        angle = ((buf[2] << 8) | buf[1]) >> 4;
//        angle = angle * 360 / 4095;
//        printf("degree: %f\n", angle);
//        printf("error: %X\n", buf[0]);

//        AD2S1210SelectMode(VELOCITY);              // Normal Mode velocity output
//        ReadFromAD2S1210(VELOCITY, POS_VEL, buf);  // read data register
//        velocity0 = ((buf[2] << 8) | buf[1]) >> 4; // 12位补码
//        if ((velocity0 & 0x800) >> 11){
//            if (velocity0 == 0xFFF)
//            {
//                printf("rps: 0.000000\n");
//                printf("error: %X\n", buf[0]);
//            }
//            else
//            {
//                // velocity = (~(velocity0 & 0x7FF))& 0x7FF;
//                // velocity = velocity*1000/2048;

//                velocity = 4096 - velocity0; // 原码
//                velocity = velocity * 1000 / 2048;

//                printf("rps:minus %f\n", velocity);
//                printf("error: %X\n", buf[0]);
//            }
//				}
//        else
//        {
//            velocity = velocity0;
//            velocity = velocity * 1000 / 2048;
//            printf("rps: %f\n", velocity);
//            printf("error: %X\n", buf[0]);
//        }

//        delay_ms(100);
    }
}
