/************************************************************************************************************
* File Name  :  dbg.h
* Author     :  Pavel Goncharuk
* Date       :  05-12-2017
* Brief      :  Header file for dbg.c module
* Bug        :
* TODO       :
*************************************************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef _DBG_H_
#define _DBG_H_
/* Includes ------------------------------------------------------------------------------------------------*/
#include "third_party/dbg_config.h"
/* Defines -------------------------------------------------------------------------------------------------*/
/**
  * @defgroup   Debug_Log_Module_Private_Defintion Debug Log Module Private Defintion
  * @brief      Debug Log Module Private Defintion
  * @{
  */
// Headers
#define USE_TEST_LOG
// #define USE_TTY_LOG
#define USE_TERMINAL_LOG

// Definitions -----------------------------------------------------------------------------------------------
// ----------------------------------------- TEST ------------------------------------------------------------
#ifdef USE_TEST_LOG
    #define __TEST_ERR_LOG(...)             __ERR_LOG(__VA_ARGS__)
    #define __TEST_SYS_LOG(...)             __SYS_LOG(__VA_ARGS__)
    #define __TEST_DBG_LOG(...)             __DBG_LOG(__VA_ARGS__)
    #define __TEST_DBG_BODY(...)            __DBG_BODY(__VA_ARGS__)
    #define __TEST_USR_LOG(...)             __USR_LOG(__VA_ARGS__)
#else /* USE_TEST_LOG */
    #define __TEST_ERR_LOG(...)
    #define __TEST_SYS_LOG(...)
    #define __TEST_DBG_LOG(...)
    #define __TEST_DBG_BODY(...)
    #define __TEST_USR_LOG(...)
#endif /* USE_TEST_LOG */
// ----------------------------------------- TTY -------------------------------------------------------------
#ifdef USE_TTY_LOG
    #define __TTY_ERR_LOG(...)             __ERR_LOG(__VA_ARGS__)
    #define __TTY_SYS_LOG(...)             __SYS_LOG(__VA_ARGS__)
    #define __TTY_DBG_LOG(...)             __DBG_LOG(__VA_ARGS__)
    #define __TTY_DBG_BODY(...)            __DBG_BODY(__VA_ARGS__)
    #define __TTY_USR_LOG(...)             __USR_LOG(__VA_ARGS__)
#else /* USE_TTY_LOG */
    #define __TTY_ERR_LOG(...)
    #define __TTY_SYS_LOG(...)
    #define __TTY_DBG_LOG(...)
    #define __TTY_DBG_BODY(...)
    #define __TTY_USR_LOG(...)
#endif /* USE_TTY_LOG */
// ----------------------------------------- TERMINAL --------------------------------------------------------
#ifdef USE_TERMINAL_LOG
    #define __TERMINAL_ERR_LOG(...)         __ERR_LOG(__VA_ARGS__)
    #define __TERMINAL_SYS_LOG(...)         __SYS_LOG(__VA_ARGS__)
    #define __TERMINAL_DBG_LOG(...)         __DBG_LOG(__VA_ARGS__)
    #define __TERMINAL_DBG_BODY(...)        __DBG_BODY(__VA_ARGS__)
    #define __TERMINAL_USR_LOG(...)         __USR_LOG(__VA_ARGS__)
#else /* USE_TERMINAL_LOG */
    #define __TERMINAL_ERR_LOG(...)
    #define __TERMINAL_SYS_LOG(...)
    #define __TERMINAL_DBG_LOG(...)
    #define __TERMINAL_DBG_BODY(...)
    #define __TERMINAL_USR_LOG(...)
#endif /* USE_TERMINAL_LOG */
/**
  * @}
  */
/* Private Typedef -----------------------------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------------------------------------*/
/* Prototypes ----------------------------------------------------------------------------------------------*/
void assert_failed (const char * fileNamePtr, int lineNum, const char * funNamePtr);
#endif /* _DBG_H_ */
