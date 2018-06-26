/************************************************************************************************************
* File Name  :  dbg.c
* Author     :  Pavel Goncharuk
* Date       :  05-12-2017
* Brief      :  Debug module
* Bug        :
* TODO       :
*************************************************************************************************************/
/* Includes ------------------------------------------------------------------------------------------------*/
#include "third_party/dbg.h"
/* Private variables ---------------------------------------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------------------------------------*/
/* Prototypes ----------------------------------------------------------------------------------------------*/
/* Functions -----------------------------------------------------------------------------------------------*/
/**
  * @brief  Assertion failed handler
  * @param  fileNamePtr: Pointer to string with file name
  * @param  lineNum: Line number of assertion
  * @param  funNamePtr: Pointer to string with function name
  * @retval none
  */
void assert_failed (const char * fileNamePtr, int lineNum, const char * funNamePtr){
    __ASSERT_LOG("%s:%d in '%s'", fileNamePtr, lineNum, funNamePtr);

    // Exit from program
    exit (EXIT_FAILURE);
}
