#include <string.h>

// for receive_info
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

// for timers
#include <sys/time.h>

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
    switch (args->program_mode)
    {
    case none:
        return err_no;
    case file:
        return send_info_file(args, hserial);
    default:
        return err_not_implemented;
    }
}

err_t send_info_file(struct args_t* args, tty_handler_t* hserial)
{
    if (args->program_mode != file)
    {
        return err_not_implemented;
    }

    for (int i = 0; i < args->mode_args_num; i++)
    {
        int file_size;
        FILE* fp;
        err_t err;
        int err_num;

        fp = fopen(args->mode_args[i], "rb");
        err_check(err_is_null(fp));

        // get file size
        err_num = fseek(fp, 0L, SEEK_END);
        err_check(err_not_equal(err_num, 0));
        file_size = ftell(fp);

        // set cursor to begin
        err_num = fseek(fp, 0L, SEEK_SET);
        err_check(err_not_equal(err_num, 0));

        uint8_t* buff = (uint8_t* )malloc(file_size * sizeof(uint8_t));
        err_check(err_is_null(buff));
        int were_read;
        were_read = fread(buff, sizeof(uint8_t), file_size, fp);
        err_check(err_not_equal(were_read, file_size));

        err = TTY_Write(*hserial, buff, file_size);
        err_check(err_not_equal(err, file_size));

        free(buff);
    }

    return err_no;
}

err_t receive_info(struct args_t* args, tty_handler_t* hserial)
{
    fd_set set;
    int filedesc = (*hserial)->fileDes;
    int err_int;
    err_t err;

    FD_ZERO(&set); /* clear the set */
    FD_SET(filedesc, &set); /* add our file descriptor to the set */

    /* timeout block */
    struct timeval t_stop;
    err = time_get_stop_time(args->recv_time, &t_stop);
    err_check(err);

    while (1)
    {
        struct timeval t_curr;
        err_int = gettimeofday(&t_curr, NULL);
        err_check(err_not_equal(err_int, 0));

        struct timeval timeout;
        timersub(&t_stop, &t_curr, &timeout);

        int rv;
        rv = select(filedesc + 1, &set, NULL, NULL, &timeout);
        if(rv == -1)
        {
            //error
            err_check(err_yes);
        }
        else if(rv == 0)
        {
            //timeout
            break;
        }
        else
        {
            /* there was data to read */
            err_t err;
            char buff;
            err = TTY_Read(*hserial, (uint8_t *)&buff, 1);
            err_check(err);

            putchar(buff);
        }
    }
    return err_no;
}

err_t close_serial(struct args_t* args, tty_handler_t* hserial)
{
    int err;
    err = TTY_DeInit(hserial);
    err_check(err);

    return err_no;
}

int tty_convert_baudrate(unsigned long long baudrate)
{
    int endcode = 0;

    switch(baudrate){
        case 50:{       endcode = B50;      break;}
        case 75:{       endcode = B75;      break;}
        case 110:{      endcode = B110;     break;}
        case 134:{      endcode = B134;     break;}
        case 150:{      endcode = B150;     break;}
        case 200:{      endcode = B200;     break;}
        case 300:{      endcode = B300;     break;}
        case 600:{      endcode = B600;     break;}
        case 1200:{     endcode = B1200;    break;}
        case 1800:{     endcode = B1800;    break;}
        case 2400:{     endcode = B2400;    break;}
        case 4800:{     endcode = B4800;    break;}
        case 9600:{     endcode = B9600;    break;}
        case 19200:{    endcode = B19200;   break;}
        case 38400:{    endcode = B38400;   break;}
        case 57600:{    endcode = B57600;   break;}
        case 115200:{   endcode = B115200;  break;}
        case 230400:{   endcode = B230400;  break;}
        case 460800:{   endcode = B460800;  break;}
        case 500000:{   endcode = B500000;  break;}
        case 576000:{   endcode = B576000;  break;}
        case 921600:{   endcode = B921600;  break;}
        case 1000000:{  endcode = B1000000; break;}
        case 1152000:{  endcode = B1152000; break;}
        case 1500000:{  endcode = B1500000; break;}
        case 2000000:{  endcode = B2000000; break;}
        case 2500000:{  endcode = B2500000; break;}
        case 3000000:{  endcode = B3000000; break;}
        case 3500000:{  endcode = B3500000; break;}
        case 4000000:{  endcode = B4000000; break;}
        default:{       endcode = B0;       break;}
    }

    return endcode;
}

err_t time_get_stop_time(float delta, struct timeval* res)
{
    int err_int;
    struct timeval t_start, t_delta;

    // start time
    err_int = gettimeofday(&t_start, NULL);
    err_check(err_not_equal(err_int, 0));

    //calc new time
    long long seconds = (long long)(delta);
    t_delta.tv_sec = (time_t)seconds;
    t_delta.tv_usec = (time_t)((delta - seconds) * 1000000);

    timeradd(&t_start, &t_delta, res);

    return err_no;
}
