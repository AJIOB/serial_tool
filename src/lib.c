#include <string.h>

#include "lib.h"

err_t parse_args(int argc, char** argv, struct args_t* hargs)
{
    const int min_args = 3;

    if (argc < min_args)
    {
        return err_few_args;
    }

    hargs->port = argv[0];
    hargs->speed = atoll(argv[1]);
    hargs->recv_time = atof(argv[2]);
    hargs->mode_args_num = argc - min_args - 1;
    hargs->mode_args = argv + min_args + 1;

    if (argc == min_args)
    {
        hargs->program_mode = none;
    }
    else if(!strcmp(argv[min_args], "-file"))
    {
        hargs->program_mode = file;
    }
    else if(!strcmp(argv[min_args], "-text"))
    {
        hargs->program_mode = text;
    }
    else if(!strcmp(argv[min_args], "-at"))
    {
        hargs->program_mode = at;
    }
    else
    {
        return err_unknown_mode;
    }

    return err_no;
}

err_t open_serial(struct args_t* args, tty_handler_t* hserial)
{
    //TODO

    return err_not_implemented;
}

err_t send_info(struct args_t* args, tty_handler_t* hserial)
{
    //TODO

    return err_not_implemented;
}

err_t receive_info(struct args_t* args, tty_handler_t* hserial)
{
    //TODO

    return err_not_implemented;
}

err_t close_serial(struct args_t* args, tty_handler_t* hserial)
{
    //TODO

    return err_not_implemented;
}
