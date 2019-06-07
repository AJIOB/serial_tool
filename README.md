# Serial Tool
Simple serial tool for basic operations with serial port (send text, file or AT command, read answer with timeout).

Program uses 8 data bits mode, 1 stop bit, no parity, no flow control.

# Usage
`./serial_tool port speed wait_answer_in_sec mode mode_parameters`

## Parameters
* port - must be serial port file path, such as `/dev/ttyS1`, for example
* speed - serial port baud rate, for example `115200`
* wait_answer_in_sec - time to wait answer until program closing, for example `10` for 10 seconds wait
* mode - mode flag (see [Supported modes](#supported-modes) for additional info), for example `-text`
* mode_parameters - mode parameters (see required mode section for additional info), for example `Hello`

## Usage example
`./serial_tool "/dev/ttyS1" 115200 10 -text Hello`

## Supported modes
* `-at` - [AT commands mode](#at-commands-mode)
* `-file` - [send file mode](#send-file-mode)
* `-text` - [send text from command line](#send-text-mode)

### AT commands mode
Sends all next parameters to serial port with adding to all of it `\n\r` pair of symbols (carrier return & newline symbols), parameter by parameter

### Send file mode
Understands all next parameters as file paths and sends all file content to serial port, file by file.
**!!!ATTENTION!!!** Please, don't send big files (more that 50 MBytes) over serial port with the help of this program. It sends all file at one moment (by one `send` function call), not in byte by byte mode.

### Send text mode
Sends all next parameters to serial port without changing, parameter by parameter

# Error list
Some errors generate by system functions. Program returns `errno` in that cases. Other errors description (you can see `inc/err.h` for new errors):

|Error code|Variable name|Error description|
|---|---|---|
|0|err_no|No errors (all is good)|
|1|err_yes|Some error was generated (unknown error)|
|2|err_not_implemented|This feature is not implemented yet|
|3|err_few_args|Program needs more command-line arguments to start working|
|4|err_unknown_mode|Unknown [supported mode](#supported-modes) (or mode is not supported yet)|
