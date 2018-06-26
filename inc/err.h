#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef uint8_t err_t;
#define err_no  0
#define err_yes 1

#define err_check(_err_)                                    \
    if (_err_ != err_no)                                    \
    {                                                       \
        printf("Error in line %d, file %s\r\n",             \
            __LINE__, __FILE__);                            \
        exit(_err_);                                        \
    }                                                       
