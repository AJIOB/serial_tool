# Serial Tool
Simple serial tool for basic operations with serial port (send text, file or AT command, read answer with timeout)

# Usage
`./serial_tool port speed wait_answer_in_sec mode mode_parameters`

## Parameters
* port - must be serial port file path, such as `/dev/ttyS1`, for example
* speed - serial port baud rate, for example `115200`
* wait_answer_in_sec - time to wait answer until program closing
* mode - mode flag (see [Supported modes](Supported-modes) for additional info)
* mode_parameters - mode parameters (see [Supported modes](Supported-modes) for additional info)

## Supported modes
**TODO**
