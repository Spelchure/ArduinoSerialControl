![img](https://img.shields.io/github/license/Spelchure/ArduinoSerialControl)
![img](https://img.shields.io/github/issues/Spelchure/ArduinoSerialControl)
![img](https://img.shields.io/github/languages/top/Spelchure/ArduinoSerialControl)

# Arduino Serial Control
Controlling arduino using serial communication. Currently only **UNIX** like systems supported.
Tested under:

- Archlinux 5.13.9
- CMake version 3.21.3
- GCC version 10.2.0
- Arduino Ide version 1.8.9
- Arduino-CMake-Toolchain
- avrdude version 6.3 

## Features
- [x] Communication arduino over serial cable.
- [x] Reading/Displaying messages coming from arduino.
- [x] Sending commands to arduino that coming from named pipe. (default */tmp/arduinocommand* ) 
- [ ] ZMQ sockets support.
- [ ] JSON processing.
- [ ] Logging.


## Requirements
- C++17 compliant compiler
- CMake version >= 3.6.3
- **Arduino-CMake-Toolchain** for compiling arduino code. (see [ArduinoCMakeToolchain](https://github.com/a9183756-gh/Arduino-CMake-Toolchain))
- **avrdude** for flashing compiled code to arduino.

### Building ArduinoSerialControl
	mkdir -p build && cd build && cmake ../
	make

### Usage
	./ArduinoSerialControl <ARDUINO_USB_PORT>
	
### Example
	./ArduinoSerialControl /dev/ttyUSB0
	echo -n "Hello Arduino" > /tmp/arduinocommand
	# For closing communication
	echo -n "close" > /tmp/arduinocommand

### Building Arduino code
You must install **arduino ide** and **arduino-cmake-toolchain** for building arduino code and flashing it to arduino using **avrdude.**

## Steps

### 1. Build arduino code
	TODO

### 2. Flash to arduino
	TODO

## Documentation

### Viewing documents
Doxygen generated documents can be viewed in docs folder. [Doxygen generated html documentation](./docs/html/index.html) 

### Generating documents
For generating documentation you need [doxygen](https://github.com/doxygen/doxygen).

	doxygen Doxyfile

## Testing
	TODO 
