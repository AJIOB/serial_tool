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
    int err;
    err = TTY_Init(hserial, args->port, tty_convert_baudrate(args->speed), 0);
    err_check(err);

    return err_no;
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
    int err;
    err = TTY_DeInit(hserial);
    err_check(err);

    return err_no;
}

int tty_convert_baudrate (unsigned long long baudrate)
{
    int endcode = 0;

    switch(baudrate){
        case 50:{       endcode = B200;     break;}
        case 75:{       endcode = B300;     break;}
        case 150:{      endcode = B600;     break;}
        case 300:{      endcode = B1200;    break;}
        case 600:{      endcode = B2400;    break;}
        case 1200:{     endcode = B4800;    break;}
        case 2400:{     endcode = B9600;    break;}
        case 4800:{     endcode = B19200;   break;}
        case 9600:{     endcode = B38400;   break;}
        case 57600:{    endcode = B230400;  break;}
        case 115200:{   endcode = B460800;  break;}
        case 230400:{   endcode = B921600;  break;}
        case 500000:{   endcode = B2000000; break;}
        case 1000000:{  endcode = B4000000; break;}
        default:{       endcode = B0;       break;}
    }

    return endcode;
}
