/*******************************************************************************
    ������� � ������ "������ UART STM8. ���������� ������."
    �������� ������ �� ����������� TXE.
    url: www.eugenemcu.ru/publ/11-1-0-69
    mcu: STM8S105C6, board - STM8 Discovery, CLK - external 16MHz.
*******************************************************************************/

     #include "iostm8s105c6.h"
     #include "intrinsics.h" //����� ������� ������� __enable_interrupt()

     unsigned char HELLO[]="Hello, I'm STM8S105C6, but who are you?";
     unsigned char *byteNum = HELLO; // ��������� �� ������������ ����.
     void main( void )
     {
          CLK_ECKR_HSEEN=1; // ��������� ������ ���������� � ������� ������� (HSEEN)
          CLK_SWCR_SWEN=1; // ��������� ������������ �����������;
          CLK_SWR=0xB4; //�������� clock �� ���������� ���������� (HSE)
          CLK_CKDIVR=0; //�������� ������� �� 1 - ������� ���� ������������.
          while(CLK_CMSR!=0xB4); //���� ������������ �������
          UART2_CR2_REN=UART2_CR2_TEN=1; // ��������� ������ TX, RX.
          UART2_BRR2 = 0x0B; UART2_BRR1 = 0x08; // BaudRate = 115200.
          __enable_interrupt(); //��������� ����������.
          UART2_CR2_TIEN=1; // ��������� ���������� �� TXE. ������ ��������.
          
          while(1)
          { 
          }
     }
     #pragma vector=UART2_T_TXE_vector
     __interrupt void UART2_TXE(void)
     {
          if (*byteNum) 
          {
               UART2_DR=*byteNum; // ��������� ����.
               byteNum++;
          }
          else UART2_CR2_TIEN=0; // ��������� ���������� �� TXE, �� ��������.
     }