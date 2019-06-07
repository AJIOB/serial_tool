#include <string.h>

#include "modes.h"

err_t send_info(struct args_t* args, tty_handler_t* hserial)
{
    int argc = args->mode_args_num;
    char** argv = args->mode_args;

    switch (args->program_mode)
    {
    case none:
        return err_no;
    case file:
        return send_info_file(argc, argv, hserial);
    case text:
        return send_info_text(argc, argv, hserial);
    case at:
        return send_info_at(argc, argv, hserial);
    default:
        return err_not_implemented;
    }
}

err_t send_info_file(int argc, char** argv, tty_handler_t* hserial)
{
    for (int i = 0; i < argc; i++)
    {
        int file_size;
        FILE* fp;
        int err_num;

        fp = fopen(argv[i], "rb");
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

        err_num = TTY_Write(*hserial, buff, file_size);
        err_check(err_not_equal(err_num, file_size));

        free(buff);
    }

    return err_no;
}

err_t send_info_text(int argc, char** argv, tty_handler_t* hserial)
{
    for (int i = 0; i < argc; i++)
    {
        int err_num;
        int file_size = strlen(argv[i]);

        err_num = TTY_Write(*hserial, (uint8_t *)(argv[i]), file_size);
        err_check(err_not_equal(err_num, file_size));
    }

    return err_no;
}

err_t send_info_at(int argc, char** argv, tty_handler_t* hserial)
{
    static const char endl[] = "\n\r";
    static const int endl_len = sizeof(endl)/sizeof(endl[0]) - 1;

    for (int i = 0; i < argc; i++)
    {
        int at_cmd_len = strlen(argv[i]);

        char* ptr = (char *) malloc ((at_cmd_len + endl_len + 1) * sizeof(char));
        err_check(err_is_null(ptr));

        strcpy(ptr, argv[i]);
        strcpy(ptr + at_cmd_len, endl);

        int err_num;
        int file_size = strlen(ptr);
        err_num = TTY_Write(*hserial, (uint8_t *)(ptr), file_size);
        err_check(err_not_equal(err_num, file_size));

        free(ptr);
    }

    return err_no;
}
