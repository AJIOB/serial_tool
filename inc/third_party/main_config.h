/************************************************************************************************************
* File Name  :  main_config.h
* Author     :  Pavel Goncharuk
* Date       :  05-12-2017
* Brief      :  Main configure header
* Bug        :
* TODO       :
*************************************************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef _MAIN_CONFIG_H_
#define _MAIN_CONFIG_H_
/* Includes ------------------------------------------------------------------------------------------------*/
/* Defines -------------------------------------------------------------------------------------------------*/
// Unuse input parameter
#define __UNUSE(__PARAM__)                  (void)(__PARAM__)
/**
  * @defgroup   MAIN_Config_Parameter_Assertion_Definitions MAIN Config Parameter Assertion Definitions
  * @brief      MAIN Config Parameter Assertion Definitions
  * @{
  */
#define IS_NO_NULL(__VAR__)                 ((__VAR__) != (NULL))
#define IS_NULL(__VAR__)                    ((__VAR__) == (NULL))
#define IS_POSITIVE(__VAR__)                ((__VAR__) >= (0))
/**
  * @}
  */
/* Private Typedef -----------------------------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------------------------------------*/
/* Prototypes ----------------------------------------------------------------------------------------------*/
#endif /* _MAIN_CONFIG_H_ */
