/************************************************************************************************************
* File Name  :  TTY.h
* Author     :  Pavel Goncharuk
* Date       :  08-01-2018
* Brief      :  Header file for TTY.c module
* Bug        :
* TODO       :
*************************************************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef _TTY_H_
#define _TTY_H_
/* Includes ------------------------------------------------------------------------------------------------*/
#include <termios.h>

#include "third_party/typenames.h"
/* Defines -------------------------------------------------------------------------------------------------*/
/**
  * @defgroup   TTY_Parameter_Assertion_Private_Definition TTY Parameter Assertion Private Definition
  * @brief      TTY Parameter Assertion Private Definition
  * @{
  */
#define IS_TTY_BAUDRATE(__VAR__)            (((__VAR__) == (B50)) ||\
                                            ((__VAR__) == (B75)) ||\
                                            ((__VAR__) == (B110)) ||\
                                            ((__VAR__) == (B134)) ||\
                                            ((__VAR__) == (B150)) ||\
                                            ((__VAR__) == (B200)) ||\
                                            ((__VAR__) == (B300)) ||\
                                            ((__VAR__) == (B600)) ||\
                                            ((__VAR__) == (B1200)) ||\
                                            ((__VAR__) == (B1800)) ||\
                                            ((__VAR__) == (B2400)) ||\
                                            ((__VAR__) == (B4800)) ||\
                                            ((__VAR__) == (B9600)) ||\
                                            ((__VAR__) == (B19200)) ||\
                                            ((__VAR__) == (B38400)) ||\
                                            ((__VAR__) == (B57600)) ||\
                                            ((__VAR__) == (B115200)) ||\
                                            ((__VAR__) == (B230400)) ||\
                                            ((__VAR__) == (B460800)) ||\
                                            ((__VAR__) == (B500000)) ||\
                                            ((__VAR__) == (B576000)) ||\
                                            ((__VAR__) == (B921600)) ||\
                                            ((__VAR__) == (B1000000)) ||\
                                            ((__VAR__) == (B1152000)) ||\
                                            ((__VAR__) == (B1500000)) ||\
                                            ((__VAR__) == (B2000000)) ||\
                                            ((__VAR__) == (B2500000)) ||\
                                            ((__VAR__) == (B3000000)) ||\
                                            ((__VAR__) == (B3500000)) ||\
                                            ((__VAR__) == (B4000000)))
/**
  * @}
  */
/* Private Typedef -----------------------------------------------------------------------------------------*/
/**
  * @brief  TTY Handle Structure Defintion
  */
typedef struct{
    char portStr[0x100];                    // TTY port string definition
    int fileDes;                            // File decription of TTY port
} TTY_Handle_t;
/* Exported constants --------------------------------------------------------------------------------------*/
/* Prototypes ----------------------------------------------------------------------------------------------*/
int TTY_Init (TTY_Handle_t ** handlePtr, const char * portPtr, int baudrate, int parity);
int TTY_DeInit (TTY_Handle_t ** handlePtr);
int TTY_Write (TTY_Handle_t * handlePtr, uint8_t * buffPtr, uint32_t size);
int TTY_Read (TTY_Handle_t * handlePtr, uint8_t * buffPtr, uint32_t size);
#endif /* _TTY_H_ */
