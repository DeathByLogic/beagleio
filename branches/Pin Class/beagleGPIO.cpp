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
//	_pin = pin;
//
//	_exported = false;
//}

//beagleGPIO::~beagleGPIO() {
////	// Unexport all pins
////	for (int i = 0; i < gpio_count; i++) {
////		if (gpio_pins[i].exported) {
////			pinUnexport(i + 1);
////		}
////	}
//}



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

int beagleGPIO::gpioOpen(const char *dir, int flags) {
	int	fileDes;

	// Open the file for write only
	if ((fileDes = open(dir, flags)) < 0) {
		perror("BeagleIO: Unable to open file ");
	}

	return fileDes;
}

int beagleGPIO::gpioClose(int file_des) {
	int rc;

	// Close the file
	if ((rc = close(file_des)) < 0) {
		perror("BeagleIO: Unable to close file ");
	}

	return rc;
}

// Low level GPIO functions

int beagleGPIO::gpioRead(char *readBuff, int count) {
	int rc;

	// Read value of file
	if ((rc = read(_fd, readBuff, count)) < 0) {
		perror("BeagleIO: Unable to read from file ");
	}

	return rc;
}

int beagleGPIO::gpioRead(long int *value, int base) {
	int rc;
	char tempBuff[MAX_BUFF];

	// Read value of file
	if ((rc = gpioRead(tempBuff, MAX_BUFF)) < 0) {
		return rc;
	} else {
		*value = strtol(tempBuff, NULL, base);
	}

	return 0;
}
int beagleGPIO::gpioWrite(const char *writeBuff, unsigned int size) {
	int rc;

	// Write buffer to file
	if ((rc = write(_fd, writeBuff, size + 1)) < 0) {
		perror("BeagleIO: Unable to write to file ");
	}

	return rc;
}

int beagleGPIO::gpioWrite(int value, int base) {
	int rc;
	int valueLen;
	char valueBuff[MAX_BUFF];

	switch (base) {
	case 0:
	case 10:
		valueLen = snprintf(valueBuff, sizeof(valueBuff), "%d", value);

		break;
	case 8:
		valueLen = snprintf(valueBuff, sizeof(valueBuff), "%01o", value);

		break;
	case 16:
		valueLen = snprintf(valueBuff, sizeof(valueBuff), "%01x", value);

		break;
	}

	rc = gpioWrite(valueBuff, valueLen);

	return rc;
}

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

