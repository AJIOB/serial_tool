#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t err_t;
#define err_no                  0
#define err_yes                 1
#define err_not_implemented     2
#define err_few_args            3
#define err_unknown_mode        4

#define err_check(_err_)                                    \
    if (_err_ != err_no)                                    \
    {                                                       \
        printf("Error in line %d, file %s, func %s\r\n",    \
            __LINE__, __FILE__, __func__);                  \
        return _err_;                                       \
    }                                                       

#define err_is_null(ptr)                                    \
    (ptr == NULL ? err_yes : err_no)

#define err_not_equal(n1, n2)                               \
    (n1 != n2 ? err_yes : err_no)

