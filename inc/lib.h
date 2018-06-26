#pragma once

#include "err.h"
#include "args.h"
#include "third_party/TTY.h"

typedef TTY_Handle_t* tty_handler_t;

err_t parse_args(int argc, char** argv, struct args_t* hargs);
err_t open_serial(struct args_t* args, tty_handler_t* hserial);
err_t send_info(struct args_t* args, tty_handler_t* hserial);
err_t send_info_file(struct args_t* args, tty_handler_t* hserial);
err_t receive_info(struct args_t* args, tty_handler_t* hserial);
err_t close_serial(struct args_t* args, tty_handler_t* hserial);

/**
 * @brief Convert baudrate from human-readable to special-defined
 * 
 * @param baudrate Human-readable baudrate
 * @return int Special-defined baudrate
 */
int tty_convert_baudrate(unsigned long long baudrate);

/**
 * @brief Calculate stop time value
 * 
 * @param delta Time in seconds from now to stop time
 * @param res Ponter to time structure
 * @return err_t Error status
 */
err_t time_get_stop_time(float delta, struct timeval* res);
