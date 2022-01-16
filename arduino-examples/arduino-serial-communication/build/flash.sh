#!/bin/bash

if [ $# -lt 1 ]; then
	echo -e "Usage: ./flash.sh <tty>\n\tExample: ./flash.sh /dev/ttyUSB0\n"
	exit
fi
avrdude -v -p atmega328p -c arduino -P "$1" -b 115200 -D -U flash:w:./arduino_serial_communication.hex:i
