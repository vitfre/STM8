//#ifdef DEBUG_STM8S003X3
    #include <stdio.h>
//#endif


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  //#ifdef DEBUG_STM8S003X3
  //printf("file %s on line %d\r\n", file, line);         
  //#endif
  /* Infinite loop */
  while (1)
  {
  }
}
#endif