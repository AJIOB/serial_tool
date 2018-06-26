/************************************************************************************************************
* File Name  :  dbg_config.h
* Author     :  Pavel Goncharuk
* Date       :  05-12-2017
* Brief      :  Debug config header
* Bug        :
* TODO       :
*************************************************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef _DBG_CONFIG_H_
#define _DBG_CONFIG_H_
/* Includes ------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
/* Defines -------------------------------------------------------------------------------------------------*/
/**
  * @defgroup   Debug_Configuration_Private_Definition Debug Configuration Private Definition
  * @brief      Debug Configuration Private Definition
  * @{
  */
// Full Assert Option
#define USE_FULL_ASSERT
// Color console option
// #define USE_ANSI_COLORS

/**
  * @defgroup   Debug_Level_Private_Definitions Debug Level Private Definitions
  * @brief      Debug Level Private Definitions
  * @{
  */
// Debug level definition
#define DBG_LVL_NONE                        (-1)
#define DBG_LVL_EXEC                        (0)
#define DBG_LVL_ERR                         (1)
#define DBG_LVL_SYS                         (2)
#define DBG_LVL_DBG                         (3)
#define DBG_LVL_USR                         (4)

// Debug Level option
#ifndef DEBUG_LEVEL
    #define DEBUG_LEVEL                     (DBG_LVL_EXEC)
#endif /* DEBUG_LEVEL */
/**
  * @}
  */

#ifdef USE_FULL_ASSERT
    #define assert_param(_expr_)            ((_expr_) ? (void)0 : assert_failed(__FILE__, __LINE__, __func__))
#else /* USE_FULL_ASSERT */
    #define assert_param(_expr_)
#endif /* USE_FULL_ASSERT */

// Debug Output source
#define __DBG_PRINT(...)                    printf(__VA_ARGS__);

// New line symbol
#define NEW_LINE                            ("\r\n")

// File name, line and function name
#define __PRINT_PATH()                      __DBG_PRINT("[%s:%d in '%s'] - ", __FILE__, __LINE__, __func__)
/**
  * @}
  */

/**
  * @defgroup   Debug_Log_Messages_Private_Definition Debug Log Messages Private Definition
  * @brief      Debug Log Messages Private Definition
  * @{
  */
// Exec log - This log using in release version of program
#if (DEBUG_LEVEL == 0)
    #define __EXEC_LOG(...)                 __DBG_PRINT(__VA_ARGS__); \
                                            __DBG_PRINT(NEW_LINE);
    #define __EXEC_BODY(...)                __VA_ARGS__

    #define __ASSERT_LOG(...)               __DBG_PRINT(ASSERT_LOG_COLOR); \
                                            __DBG_PRINT("[ASS]: "); \
                                            __DBG_PRINT(__VA_ARGS__); \
                                            __DBG_PRINT(NEW_LINE); \
                                            __DBG_PRINT(ANSI_COLOR_RESET);

#else /* DEBUG_LEVEL*/
    #define __EXEC_LOG(...)
    #define __EXEC_BODY(...)
    #define __ASSERT_LOG(...)
#endif /* DEBUG_LEVEL*/

// Error and Assertion Log
#if (DEBUG_LEVEL > 0)

    #define __ERR_LOG(...)                  __DBG_PRINT(ERROR_LOG_COLOR); \
                                            __DBG_PRINT("[ERR]: "); \
                                            __PRINT_PATH(); \
                                            __DBG_PRINT(__VA_ARGS__); \
                                            __DBG_PRINT(NEW_LINE); \
                                            __DBG_PRINT(ANSI_COLOR_RESET);

    #define __DBG_BODY(...)                 __VA_ARGS__

#else /* DEBUG_LEVEL > 0 */
    #define __ERR_LOG(...)
    #define __DBG_BODY(...)
#endif /* DEBUG_LEVEL > 0 */

// System Log
#if (DEBUG_LEVEL > 1)
    #define __SYS_LOG(...)                  __DBG_PRINT(SYSTEM_LOG_COLOR); \
                                            __DBG_PRINT("[SYS]: ");  \
                                            __PRINT_PATH(); \
                                            __DBG_PRINT(__VA_ARGS__);   \
                                            __DBG_PRINT(NEW_LINE); \
                                            __DBG_PRINT(ANSI_COLOR_RESET);
#else /* DEBUG_LEVEL > 1 */
    #define __SYS_LOG(...)
#endif /* DEBUG_LEVEL > 1 */

// Debug Log
#if (DEBUG_LEVEL > 2)
    #define __DBG_LOG(...)                  __DBG_PRINT(DEBUG_LOG_COLOR); \
                                            __DBG_PRINT("[DBG]: ");     \
                                            __PRINT_PATH(); \
                                            __DBG_PRINT(__VA_ARGS__);   \
                                            __DBG_PRINT(NEW_LINE); \
                                            __DBG_PRINT(ANSI_COLOR_RESET);

#else /* DEBUG_LEVEL > 2 */
    #define __DBG_LOG(...)
#endif /* DEBUG_LEVEL > 2 */

// User Log
#if (DEBUG_LEVEL > 3)
    #define __USR_LOG(...)                  __DBG_PRINT(USER_LOG_COLOR); \
                                            __DBG_PRINT("[USR]: ");     \
                                            __PRINT_PATH(); \
                                            __DBG_PRINT(__VA_ARGS__);   \
                                            __DBG_PRINT(NEW_LINE); \
                                            __DBG_PRINT(ANSI_COLOR_RESET);
#else /* DEBUG_LEVEL > 3 */
    #define __USR_LOG(...)
#endif /* DEBUG_LEVEL > 3 */
/**
  * @}
  */

/**
  * @defgroup   Debug_ANSII_Colors_Private_Definition Debug ANSII Colors Private Definition
  * @brief      Debug ANSII Colors Private Definition
  * @{
  */
// Log color definitions
#define ERROR_LOG_COLOR                     ANSI_COLOR_RED
#define ASSERT_LOG_COLOR                    ANSI_COLOR_MAGENTA
#define BREAK_LOG_COLOR                     ANSI_COLOR_YELLOW
#define SYSTEM_LOG_COLOR                    ANSI_COLOR_CYAN
#define USER_LOG_COLOR                      ANSI_COLOR_BLUE
#define DEBUG_LOG_COLOR                     ANSI_COLOR_GREEN

// Color codes
#ifdef USE_ANSI_COLORS
    #define ANSI_COLOR_RED                  "\e[91m"        //It's light red
    #define ANSI_COLOR_GREEN                "\e[92m"        //It's light green
    #define ANSI_COLOR_YELLOW               "\e[93m"        //It's light yellow
    #define ANSI_COLOR_BLUE                 "\e[94m"        //It's light blue
    #define ANSI_COLOR_MAGENTA              "\e[95m"        //It's light magenta
    #define ANSI_COLOR_CYAN                 "\e[96m"        //It's light cyan
    #define ANSI_COLOR_RESET                "\e[39m"        //It's default color

    #define ANSI_COLOR_RED_BACKGROUND       "\e[41m"        //It's light red
    #define ANSI_COLOR_GREEN_BACKGROUND     "\e[42m"        //It's light green
    #define ANSI_COLOR_YELLOW_BACKGROUND    "\e[43m"        //It's light yellow
    #define ANSI_COLOR_BLUE_BACKGROUND      "\e[44m"        //It's light blue
    #define ANSI_COLOR_MAGENTA_BACKGROUND   "\e[45m"        //It's light magenta
    #define ANSI_COLOR_CYAN_BACKGROUND      "\e[46m"        //It's light cyan
    #define ANSI_COLOR_RESET_BACKGROUND     "\e[49m"        //It's default color
#else
    #define ANSI_COLOR_RED                  " "
    #define ANSI_COLOR_GREEN                " "
    #define ANSI_COLOR_YELLOW               " "
    #define ANSI_COLOR_BLUE                 " "
    #define ANSI_COLOR_MAGENTA              " "
    #define ANSI_COLOR_CYAN                 " "
    #define ANSI_COLOR_RESET                " "

    #define ANSI_COLOR_RED_BACKGROUND       " "
    #define ANSI_COLOR_GREEN_BACKGROUND     " "
    #define ANSI_COLOR_YELLOW_BACKGROUND    " "
    #define ANSI_COLOR_BLUE_BACKGROUND      " "
    #define ANSI_COLOR_MAGENTA_BACKGROUND   " "
    #define ANSI_COLOR_CYAN_BACKGROUND      " "
    #define ANSI_COLOR_RESET_BACKGROUND     " "
#endif /* USE_ANSI_COLORS */
/**
  * @
  */
/* Private Typedef -----------------------------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------------------------------------*/
/* Prototypes ----------------------------------------------------------------------------------------------*/
#endif /* _DBG_CONFIG_H_ */
