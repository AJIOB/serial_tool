#pragma once

#include "err.h"
#include "args.h"

//temp
typedef int tty_handler_t;

err_t parse_args(int argc, char** argv);
err_t open_serial(struct args_t* args, tty_handler_t* hserial);
err_t send_info(struct args_t* args, tty_handler_t* hserial);
err_t receive_info(struct args_t* args, tty_handler_t* hserial);
err_t close_serial(struct args_t* args, tty_handler_t* hserial);

