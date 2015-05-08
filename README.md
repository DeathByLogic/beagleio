# BeagleIO
BeagleIO is a simple C library to access the GPIO pins of the BeagleBone White/Black. Each pin is broken out as an object with a base class of BeagleGPIO, if the pin has additional functionality a derived class based on BeagleGPIO is used.

```c++
// Read analog pin
cout << P9_39.readPin() << endl;

// Write to digital pin
P8_45.exportPin();
P8_45.setDirection(OUTPUT_PIN);
P8_45.writePin(true);
P8_45.unexportPin();

// Read from digital pin
P8_41.exportPin();
P8_41.setDirection(INPUT_PIN);
P8_41.openPin(O_RDONLY | O_NONBLOCK);
cout << P8_41.readPin() << endl;
P8_41.closePin();
P8_41.unexportPin();

// Write to serial port
P8_37.exportPin();
P8_37.setDirection(OUTPUT_PIN);
P8_37.openPort(BR_57600);
P8_37.writePort("U",1);
P8_37.closePort();
```

## Class Structure
- BeagleGPIO
  - BeagleAnalog
  - BeagleDigital
    - BeagleSerial
    - BeagleI2C
    
## Class descriptions
### BeagleGPIO
Low level pin IO functions

### BeagleDigital
- Read and write to digital I/O pins
- Set pin direction
- Set pin edge
- Export pin

### BeagleAnalog
- Read analog value of analog pins

### BeagleSerial
- Open pin as serial port
- Read from port
- Write to port
- Change buad rate, parity, byte size, stop bit

### BealgeI2C
- Write to address
- Request from address
