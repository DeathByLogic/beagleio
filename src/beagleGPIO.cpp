/*
 * beagleGPIO.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: daniel@deathbylogic.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "beagleGPIO.h"

using namespace std;

/*
 * Constructor & Destructor
 */

//beagleGPIO::beagleGPIO() {
//	// Do nothing
//}

//beagleGPIO::beagleGPIO(const char *ID) {
////	gpio_pins = pins;
////	gpio_count = count;
////
////	for (int i = 0; i < gpio_count; i++) {
////		gpio_pins[i].exported = false;
////	}
////	_pin = pin;
//
////	_exported = false;
//}

beagleGPIO::~beagleGPIO() {
	// Close the fd pointer if it is open
	if (_fd > 0) {
		gpioClose(_fd);
	}

//	// Unexport all pins
//	for (int i = 0; i < gpio_count; i++) {
//		if (gpio_pins[i].exported) {
//			pinUnexport(i + 1);
//		}
//	}
}

/*
 * Private Functions
 */

int beagleGPIO::gpioOpen(const char *dir, int flags) {
	int	fd;

	// Open the file for write only
	if ((fd = open(dir, flags)) < 0) {
		perror("BeagleIO: Unable to open file ");
	}

	return fd;
}

int beagleGPIO::gpioClose(int fd) {
	int rc;

	// Close the file
	if ((rc = close(fd)) < 0) {
		perror("BeagleIO: Unable to close file ");
	}

	return rc;
}

int beagleGPIO::getPinFD() {
	return _fd;
}

bool beagleGPIO::isOpen() {
	if (_fd > 0) {
		return true;
	} else {
		return false;
	}
}

/*
 * Analog Functions
 */

//void beagleGPIO::analogRead(unsigned int pin, int *value) {
//	int fd;
//	char dirBuff[MAX_BUFF];
//	long int tmpValue;
//
//	// Check if pin is in table of pins
//	if (checkGPIO(pin, ANALOG) == false) {
//		fprintf(stderr, "BeagleIO: Pin %d is a invalid pin or it is not a valid analog input.\n", pin);
//		return;
//	} else {
//		snprintf(dirBuff, sizeof(dirBuff), FS_ANALOG_DIR, gpio_pins[pin - 1].alt);
//
//		// Open the file location
//		fd = gpioOpen(dirBuff, O_RDONLY);
//
//		// Read the value of pin
//		gpioRead(fd, &tmpValue);
//
//		// Close the file location
//		gpioClose(fd);
//
//		*value = tmpValue;
//	}
//}
//
//int beagleGPIO::analogRead(unsigned int pin) {
//	int tmpValue;
//
//	analogRead(pin, &tmpValue);
//
//	return tmpValue;
//}

/*
 * PWM Functions
 */

/*
void pwmRun(unsigned int) {

}

void pwmStop(unsigned int) {

}

void pwmConfig(unsigned int, unsigned int, unsigned int) {

}

void pwmSetFreq(unsigned int, unsigned int) {

}

void pwmSetDuty(unsigned int, unsigned int) {

}
*/

/*
 * GPIO File Access Functions
 */

//bool beagleGPIO::checkGPIO(unsigned int pin, unsigned int type) {
//	 if ((gpio_pins[pin - 1].type bitand type) > 0) {
//		 return true;
//	 }
//
//	return false;
//}


/*

int beagleGPIO::gpioSetEdge(io_pin *gpio, PIN_EDGE edge) {
	int rc;
	int	fileDes;
	char dirBuff[MAX_BUFF];

	snprintf(dirBuff, sizeof(dirBuff), FS_EDGE_DIR, gpio->pin);

	// Open file for write only
	if ((fileDes = open(dirBuff, O_WRONLY)) < 0) {
		perror("GPIO Set Edge");
		return fileDes;
	} else {
		// Write the correct string to set edge
		switch (edge) {
		case RISING_EDGE:
			rc = write(fileDes, "rising", 7);
			break;
		case FALLING_EDGE:
			rc = write(fileDes, "falling", 8);
			break;
		case BOTH_EDGES:
			rc = write(fileDes, "both", 5);
			break;
		default:
			fprintf(stderr, "GPIO Set Edge: Invalid Edge Argument");
			break;
		}

		// Check for errors on write
		if (rc < 0) {
			perror("GPIO Set Edge");
			return rc;
		}

		// Close edge file
		if ((rc = close(fileDes)) < 0) {
			perror("GPIO Set Edge");
			return rc;
		}

		return 0;
	}
}

// Set the GPIO pin value
int beagleGPIO::gpioSetValue(io_pin* gpio, bool value) {
	int rc;
	int	fileDes;
	char dirBuff[MAX_BUFF];

	snprintf(dirBuff, sizeof(dirBuff), FS_VALUE_DIR, gpio->pin);

	// Open file for write only
	if ((fileDes = open(dirBuff, O_WRONLY)) < 0) {
		perror("GPIO Set Value");
		return fileDes;
	} else {
		// Write correct value to file
		if (value) {
			rc = write(fileDes, "1", 2);
		} else {
			rc = write(fileDes, "0", 2);
		}

		// Check for errors
		if (rc < 0) {
			perror("GPIO Set Value");
			return rc;
		}

		// Close file
		if ((rc = close(fileDes)) < 0) {
			perror("GPIO Set Value");
			return rc;
		}

		return 0;
	}
}

int beagleGPIO::gpioGetValue(io_pin *gpio, bool *value) {
	int rc;
	int	fileDes;
	char ch;
	char dirBuff[MAX_BUFF];

	snprintf(dirBuff, sizeof(dirBuff), FS_VALUE_DIR, gpio->pin);

	// Open file for read only
	if ((fileDes = open(dirBuff, O_RDONLY)) < 0) {
		perror("GPIO Get Value");
		return fileDes;
	} else {
		// Read value of file
		if ((rc = read(fileDes, &ch, 1)) < 0){
			perror("GPIO Get Value");
			return rc;
		}

		// Interpret Value
		if (ch != '0') {
			*value = 1;
		} else {
			*value = 0;
		}

		// Close file
		if ((rc = close(fileDes)) < 0) {
			perror("GPIO Get Value");
			return rc;
		}

		return 0;
	}
}

// Set the GPIO pin direction
int beagleGPIO::gpioSetDirection(io_pin *gpio, PIN_DIRECTION direction) {
	int rc;
	int	fileDes;
	char dirBuff[MAX_BUFF];

	snprintf(dirBuff, sizeof(dirBuff), FS_DIR_DIR, gpio->pin);

	// Attempt to open the file for write only
	if ((fileDes = open(dirBuff, O_WRONLY)) < 0) {
		perror("GPIO Direction");
		return fileDes;
	} else {
		// Write to file based on direction
		switch (direction) {
		case INPUT_PIN:
			// If input write "in"
			rc = write(fileDes, "in", 3);
			break;
		case OUTPUT_PIN:
			// If output write "out"
			rc = write(fileDes, "out", 4);
			break;
		default:
			fprintf(stderr, "GPIO Direction: Invalid Direction");
			break;
		}

		// Check for errors
		if (rc < 0) {
			perror("GPIO Direction");
			return rc;
		}

		// Close the file
		if ((rc = close(fileDes)) < 0) {
			perror("GPIO Direction");
			return rc;
		}

		return 0;
	}
}

int beagleGPIO::gpioSetMode(io_pin *gpio, unsigned int mode) {
	int rc;
	int	fileDes;
	char modeBuff[MAX_BUFF];
	char dirBuff[MAX_BUFF];

	snprintf(dirBuff, sizeof(dirBuff), FS_MUX_DIR, gpio->mux);

	// Open file for write only
	if ((fileDes = open(dirBuff, O_WRONLY)) < 0) {
		perror("GPIO Set Mode");
		return fileDes;
	} else {
		// Print mode into string
		snprintf(modeBuff, sizeof(modeBuff), "%.2X", mode);

		// Write the value to set config
		if ((rc = write(fileDes, modeBuff, strlen(modeBuff) + 1)) < 0) {
			perror("GPIO Set Mode");
			return rc;
		}

		// Close edge file
		if ((rc = close(fileDes)) < 0) {
			perror("GPIO Set Mode");
			return rc;
		}

		return 0;
	}
}

 */

