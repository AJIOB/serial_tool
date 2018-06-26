#include <stdio.h>

#include "lib.h"

int main(int argc, char** argv)
{
    err_t err = err_no;
    struct args_t args;

    err = parse_args(argc - 1, argv + 1, &args);
    err_check(err);

    tty_handler_t hserial;

    err = open_serial(&args, &hserial);
    err_check(err);

    err = send_info(&args, &hserial);
    err_check(err);

    err = receive_info(&args, &hserial);
    err_check(err);

    err = close_serial(&args, &hserial);
    err_check(err);

    return 0;
}
