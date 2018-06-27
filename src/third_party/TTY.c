/************************************************************************************************************
* File Name  :  TTY.c
* Author     :  Pavel Goncharuk
* Date       :  08-01-2018
* Brief      :  TTY interface support
* Bug        :
* TODO       :
*************************************************************************************************************/
/* Includes ------------------------------------------------------------------------------------------------*/
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "third_party/dbg.h"
#include "third_party/main_config.h"

#include "third_party/TTY.h"
/* Private variables ---------------------------------------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------------------------------------*/
/* Prototypes ----------------------------------------------------------------------------------------------*/
static int TTY_BaudrateWorkAround (int baudrate);
/* Functions -----------------------------------------------------------------------------------------------*/
/**
  * @brief  TTY interface configuration and initiaziation
  * @param  handlePtr: Pointer to TTY handle structure definition @TTY_Handle_t
  * @param  portPtr: Pointer to string with port definition
  * @param  baudrate: Baudrate value
  * @param  parity: Parity option
  * @retval endcode: @errno
  */
int TTY_Init (TTY_Handle_t ** handlePtr, const char * portPtr, int baudrate, int parity){
    // Parameter assertion check
    assert_param(IS_NO_NULL(portPtr));
    assert_param(IS_TTY_BAUDRATE(baudrate));
    assert_param(IS_POSITIVE(parity));

    struct termios tempTTY;

    memset(&tempTTY, 0, sizeof(tempTTY));

    // Initilize TTY handler
    __TTY_USR_LOG("Initilize TTY handler");
    (*handlePtr) = (TTY_Handle_t *) malloc(sizeof(TTY_Handle_t));
    assert_param(IS_NO_NULL(*handlePtr));
    memset(*handlePtr, 0, sizeof(TTY_Handle_t));

    // Open TTY port
    __TTY_USR_LOG("Open TTY port");
    strcpy((*handlePtr)->portStr, portPtr);
    (*handlePtr)->fileDes = open(portPtr, (O_RDWR|O_NOCTTY|O_SYNC));
    assert_param(IS_POSITIVE((*handlePtr)->fileDes));

    // Configre TTY port
    __TTY_USR_LOG("Configre TTY port");
    if (tcgetattr((*handlePtr)->fileDes, &tempTTY)){
        __TTY_ERR_LOG("Failed to configure port: %d", errno);
        return errno;
    }

    // Configure baudrate value
    __TTY_USR_LOG("Configure baudrate value: %Xh", baudrate);
    if (cfsetospeed(&tempTTY, TTY_BaudrateWorkAround(baudrate))){
        __TTY_ERR_LOG("Failed to configure output stream speed: %d", errno);
        return errno;
    }
    if (cfsetispeed(&tempTTY, TTY_BaudrateWorkAround(baudrate))){
        __TTY_ERR_LOG("Failed to configure input stream speed: %d", errno);
        return errno;
    }

    // Configure TTY flags
    __TTY_USR_LOG("Configure TTY flags");
    tempTTY.c_cflag = (tempTTY.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tempTTY.c_iflag &= ~IGNBRK;         // disable break processing
    tempTTY.c_lflag = 0;                // no signaling chars, no echo,
                                    // no canonical processing
    tempTTY.c_oflag = 0;                // no remapping, no delays
    tempTTY.c_cc[VMIN]  = 0;            // read doesn't block
    tempTTY.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    tempTTY.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tempTTY.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                    // enable reading
    tempTTY.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tempTTY.c_cflag |= parity;
    tempTTY.c_cflag &= ~CSTOPB;
    tempTTY.c_cflag &= ~CRTSCTS;

    // Initialize config into port
    __TTY_DBG_LOG("Initialize config into port");
    if (tcsetattr((*handlePtr)->fileDes, TCSANOW, &tempTTY)){
        __TTY_ERR_LOG("Failed to initilize port configuration: %d", errno);
        return errno;
    }
    __TTY_SYS_LOG("Port %s successfully configured", portPtr);

    return 0;
}

/**
  * @brief  TTY port deinitialization
  * @param  handlePtr: Pointer to TTY handle structure definition @TTY_Handle_t
  * @retval endcode: @errno
  */
int TTY_DeInit (TTY_Handle_t ** handlePtr){
    // Parameter assertion check
    assert_param(IS_NO_NULL(*handlePtr));

    __TTY_DBG_BODY(char tempString[0x100] = {0});
    __TTY_DBG_BODY(strcpy(tempString, (*handlePtr)->portStr));

    // Deinitilize TTY handler and free memory
    __TTY_USR_LOG("Deinitilize TTY handler and free memory");
    if (close((*handlePtr)->fileDes)){
        __TTY_ERR_LOG("Failed to close TTY port: %d", errno);
        return errno;
    }
    free(*handlePtr);
    __TTY_SYS_LOG("TTY port %s was successfully closed", tempString);

    return 0;
}

/**
  * @brief  Send data using TTY port
  * @param  handlePtr: Pointer to TTY handle structure defintion @TTY_Handle_t
  * @param  buffPtr: Pointer to output data buffer
  * @param  size: Size of data to send
  * @retval endcode: Number of bytes what was send
  */
int TTY_Write (TTY_Handle_t * handlePtr, uint8_t * buffPtr, uint32_t size){
    // Parameter assertion check
    assert_param(IS_NO_NULL(handlePtr));
    assert_param(IS_NO_NULL(buffPtr));
    assert_param(IS_POSITIVE(size));

    int endcode = 0;

    // Send data using TTY interface
    __TTY_USR_LOG("Send %d bytes of data using TTY interface", size);
    endcode = write(handlePtr->fileDes, buffPtr, size);

    // CRUTCH @TODO
    endcode = ((endcode > 0) ? (endcode) : (0));

    return endcode;
}

/**
  * @brief  Read data using TTY port
  * @param  handlePtr: Pointer to TTY handle structure definition @TTY_Handle_t
  * @param  buffPtr: Pointer to input data buffer
  * @param  size: Siz of data to read
  * @retval endcode: Number of bytes what was read
  */
int TTY_Read (TTY_Handle_t * handlePtr, uint8_t * buffPtr, uint32_t size){
    // Parameter assertion check
    assert_param(IS_NO_NULL(handlePtr));
    assert_param(IS_NO_NULL(buffPtr));
    assert_param(IS_POSITIVE(size));

    int endcode = 0;

    // Read data using TTY interface
    __TTY_USR_LOG("Read %d bytes of data using TTY interface", size);
    endcode = read(handlePtr->fileDes, buffPtr, size);

    // CRUTCH @TODO
    endcode = ((endcode > 0) ? (endcode) : (0));

    return endcode;
}

/**
  * @brief  Increase input baudrate
  * @note   This function is a crutch. Need proper termios.h header file
  * @param  baudrate: Input baudrate value
  * @retval endcode: Increased baudrate value
  */
static int TTY_BaudrateWorkAround (int baudrate){
    // Parameter assertion check
    assert_param(IS_TTY_BAUDRATE(baudrate));

    return baudrate;
#if 0
    int endcode = 0;

    switch(baudrate){
        case B50:{      endcode = B200;     break;}
        case B75:{      endcode = B300;     break;}
        case B150:{     endcode = B600;     break;}
        case B300:{     endcode = B1200;    break;}
        case B600:{     endcode = B2400;    break;}
        case B1200:{    endcode = B4800;    break;}
        case B2400:{    endcode = B9600;    break;}
        case B4800:{    endcode = B19200;   break;}
        case B9600:{    endcode = B38400;   break;}
        case B57600:{   endcode = B230400;  break;}
        case B115200:{  endcode = B460800;  break;}
        case B230400:{  endcode = B921600;  break;}
        case B500000:{  endcode = B2000000; break;}
        case B1000000:{ endcode = B4000000; break;}
        default:{       endcode = B0;       break;}
    }

    return endcode;
#endif
}
