#include "main.h"

int main( void )
{
  uint32_t Address_EEPROM=EEPROM_START+4;
  uint32_t n0=0;
  uint32_t n1=0;
  uint32_t k0=0;
  uint32_t k1=0;
  uint8_t ERR=2;
  uint8_t rr=0;

  CLK_Init();
  UART_Init();
  GP_IO_Init();
  TIMR2_Init();
  FLASH_EEPROM_Unlock();
  A_D_C_Init();

 enableInterrupts(); //Разрешаем прерывания.

 while(1)
 {
   /*
   if(GPIO_ReadInputPin(GPIOC, GPIO_PIN_2)==0)
   {
      GPIO_WriteLow(GPIOB, GPIO_PIN_6);
      delay_ms(50);
      GPIO_WriteHigh(GPIOB, GPIO_PIN_6);
      while(GPIO_ReadInputPin(GPIOC, GPIO_PIN_2)==0){delay_ms(10);};
   };
   
   if(GPIO_ReadInputPin(GPIOE, GPIO_PIN_5)==0)
   {
      GPIO_WriteLow(GPIOB, GPIO_PIN_7);
      delay_ms(50);
      GPIO_WriteHigh(GPIOB, GPIO_PIN_7);
      while(GPIO_ReadInputPin(GPIOE, GPIO_PIN_5)==0){delay_ms(10);};
   };
   */
   if(GPIO_ReadInputPin(GPIOC, GPIO_PIN_1)==0)
   {
      ERR=0;
      GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
      GPIO_WriteHigh(GPIOB, GPIO_PIN_6);
      while(GPIO_ReadInputPin(GPIOC, GPIO_PIN_1)==0){delay_ms(10);};
   };
   
  if(ERR==0)
  {
    GPIO_WriteLow(GPIOB, GPIO_PIN_7);
    //delay_ms(6);              
    FLASH_ProgramWord(Address_EEPROM, n0);
    //FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
    GPIO_WriteHigh(GPIOB, GPIO_PIN_7);
    delay_ms(4);
    n1 = FLASH_ReadWord(Address_EEPROM);
    if(n1!=n0)
    {
      ERR=1;
    }else
    {
      n0++;
      GPIO_WriteReverse(GPIOF, GPIO_PIN_4);
    };
    
  }else if(ERR==1)
  {
    GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
    delay_ms(100);
  }else if(ERR==2)
  {
    GPIO_WriteReverse(GPIOB, GPIO_PIN_6);
    delay_ms(100);
  };
   /*
  GPIO_WriteLow(GPIOB, GPIO_PIN_6);
  delay_ms(50);
  GPIO_WriteHigh(GPIOB, GPIO_PIN_6);
  
  GPIO_WriteLow(GPIOB, GPIO_PIN_7);
  delay_ms(50);
  GPIO_WriteHigh(GPIOB, GPIO_PIN_7);
   
  GPIO_WriteLow(GPIOB, GPIO_PIN_5);
  delay_ms(50);
  GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
  delay_ms(1000); 
*/

 }
 
 //return 0;
}
