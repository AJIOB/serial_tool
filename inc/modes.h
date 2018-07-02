#pragma once

#include "err.h"
#include "args.h"

err_t send_info(struct args_t* args, tty_handler_t* hserial);

err_t send_info_file(int argc, char** argv, tty_handler_t* hserial);
err_t send_info_text(int argc, char** argv, tty_handler_t* hserial);
err_t send_info_at(int argc, char** argv, tty_handler_t* hserial);
