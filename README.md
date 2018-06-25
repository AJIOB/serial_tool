# Serial Tool
Simple serial tool for basic operations with serial port (send text, file or AT command, read answer with timeout).

Program uses 8 data bits mode, 1 stop bit, no parity, no flow control.

# Usage
`./serial_tool port speed wait_answer_in_sec mode mode_parameters`

## Parameters
* port - must be serial port file path, such as `/dev/ttyS1`, for example
* speed - serial port baud rate, for example `115200`
* wait_answer_in_sec - time to wait answer until program closing, for example `10` for 10 seconds wait
* mode - mode flag (see [Supported modes](#Supported-modes) for additional info), for example `-text`
* mode_parameters - mode parameters (see required mode section for additional info), for example `Hello`

## Usage example
`./serial_tool "/dev/ttyS1" 115200 10 -text Hello`

## Supported modes
* `-at` - [AT commands mode](#AT-commands-mode)
* `-file` - [send file mode](#Send-file-mode)
* `-text` - [send text from command line](#Send-text-mode)

### AT commands mode
Sends all next parameters to serial port with adding to all of it `\r\n` pair of symbols (carrier return & newline symbols), parameter by parameter

### Send file mode
Understands all next parameters as file paths and sends all file content to serial port, file by file.  
**!!!ATTENTION!!!** Please, don't send big files (more that 50 MBytes) over serial port with the help of this program. It sends all file at one moment (by one `send` function call), not in byte by byte mode.

### Send text mode
Sends all next parameters to serial port without changing, parameter by parameter
