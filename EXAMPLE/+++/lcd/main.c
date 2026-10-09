
#include "iostm8l152c6.h"
#include "LCD.h"

unsigned long i;
int main( void )
{
 CLK_CKDIVR_bit.CKM=0;
 LCD_Init();
 LCD_Contrast(5);
 

 LCD_Write_String("TEST ");
 for(i=0; i<200000; i++){asm("nop");};

 while(1)
 {
  LCD_Write_String("17:32:59");
  for(i=0; i<100000; i++){asm("nop");};
  LCD_Write_String("173259");
  for(i=0; i<100000; i++){asm("nop");};
 }; 
}
