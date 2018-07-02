#pragma once

#include "third_party/TTY.h"

enum mode_t
{
    text,
    file,
    at,
    none
};

struct args_t
{
    char* port;
    unsigned long long speed;
    float recv_time;
    enum mode_t program_mode;
    char** mode_args;
    int mode_args_num;
};

typedef TTY_Handle_t* tty_handler_t;
