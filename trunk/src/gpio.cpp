/*
 * gpio.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: daniel@deathbylogic.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "gpio.h"

using namespace std;

/*
 * Constructor & Deconstructor
 */

beagleIO::beagleIO(io_pin *pins, int count) {
	gpio_pins = pins;
	gpio_count = count;

	for (int i = 0; i < gpio_count; i++) {
		gpio_pins[i].exported = false;
		gpio_pins[i].fd = 0;
	}
}

beagleIO::~beagleIO() {
	// Unexport all pins
	for (int i = 0; i < gpio_count; i++) {
		if (gpio_pins[i].exported) {
			gpioUnexport(gpio_pins[i].pin);
		}
	}
}

/*
 * Digital Functions
 */

void beagleIO::digitalGetValue(unsigned int pin, bool *value) {
	int fd;
	char dirBuff[MAX_BUFF];
	long int tmpValue;

	// Check if pin is in table of pins
	if (checkGPIO(pin, DIGITAL) == false) {
		fprintf(stderr, "Pin %d is a invalid pin or it is not a valid digital I/O.", pin);
		return;
	} else {
		// Export pin if needed
		if (gpio_pins[pin - 1].exported == false) {
			fprintf(stderr, "Pin %d has not been exported", pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_VALUE_DIR, pin);

			// Open the file location
			fd = gpioOpen(dirBuff, O_RDONLY);

			// Read the value of pin
			gpioRead(fd, &tmpValue, 16);

			// Close the file location
			gpioClose(fd);

			*value = (bool)tmpValue;
		}
	}
}

bool beagleIO::digitalGetValue(unsigned int pin) {
	bool tmpValue;

	// Read Digital Value
	digitalGetValue(pin, &tmpValue);

	return tmpValue;
}

void beagleIO::digitalSetValue(unsigned int pin, bool value) {
	int fd;
	char dirBuff[MAX_BUFF];

	// Check if pin is in table of pins
	if (checkGPIO(pin, DIGITAL) == false) {
		fprintf(stderr, "Pin %d is a invalid pin or it is not a valid digital I/O.", pin);
		return;
	} else {
		// Export pin if needed
		if (gpio_pins[pin - 1].exported == false) {
			fprintf(stderr, "Pin %d has not been exported", pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_VALUE_DIR, pin);

			// Open the file location
			fd = gpioOpen(dirBuff, O_WRONLY);

			// Read the value of pin
			gpioWrite(fd, value);

			// Close the file location
			gpioClose(fd);
		}
	}
}

void beagleIO::digitalSetDirection(unsigned int pin, PIN_DIRECTION direction) {
	int fd;
	char dirBuff[MAX_BUFF];

	// Check if pin is in table of pins
	if (checkGPIO(pin, DIGITAL) == false) {
		fprintf(stderr, "Pin %d is a invalid pin or it is not a valid digital I/O.", pin);
		return;
	} else {
		// Export pin if needed
		if (gpio_pins[pin - 1].exported == false) {
			fprintf(stderr, "Pin %d has not been exported", pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_DIR_DIR, pin);

			// Open the file location
			fd = gpioOpen(dirBuff, O_WRONLY);

			// Write direction to file
			switch (direction) {
			case INPUT_PIN:
				gpioWrite(fd, "input", 5);

				break;
			case OUTPUT_PIN:
				gpioWrite(fd, "in", 2);

				break;
			}

			// Close the file location
			gpioClose(fd);
		}
	}
}

void beagleIO::digitalSetEdge(unsigned int pin, PIN_EDGE edge) {
	int fd;
	char dirBuff[MAX_BUFF];

	// Check if pin is in table of pins
	if (checkGPIO(pin, DIGITAL) == false) {
		fprintf(stderr, "Pin %d is a invalid pin or it is not a valid digital I/O.", pin);
		return;
	} else {
		// Export pin if needed
		if (gpio_pins[pin - 1].exported == false) {
			fprintf(stderr, "Pin %d has not been exported", pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_DIR_DIR, pin);

			// Open the file location
			fd = gpioOpen(dirBuff, O_WRONLY);

			// Write direction to file
			switch (edge) {
			case NONE:
				gpioWrite(fd, "none", 4);

				break;
			case RISING_EDGE:
				gpioWrite(fd, "rising", 6);

				break;
			case FALLING_EDGE:
				gpioWrite(fd, "falling", 7);

				break;
			case BOTH_EDGES:
				gpioWrite(fd, "both", 4);

				break;
			}

			// Close the file location
			gpioClose(fd);
		}
	}
}

/*
 * Serial Functions
 */


int beagleIO::serialRead(unsigned int pin, char *buf, int count) {
	int fd;
	int size;

	// Check if pin is in table of pins
	if (checkGPIO(pin, SERIAL) == false) {
		fprintf(stderr, "Pin %d is a invalid pin or it is not a valid digital I/O.", pin);
		return 0;
	} else {
		if ((fd = gpio_pins[pin - 1].fd) > 0) {
			// Read from buffer
			size = gpioRead(fd, buf);
		}
	}

	return size;
}

void beagleIO::serialWrite(unsigned int pin, const char *buf, int count) {
	int fd;

	// Check if pin is in table of pins
	if (checkGPIO(pin, SERIAL) == false) {
		fprintf(stderr, "Pin %d is a invalid pin or it is not a valid digital I/O.", pin);
		return;
	} else {
		if ((fd = gpio_pins[pin - 1].fd) > 0) {
			// Write string to buffer
			gpioWrite(fd, buf, count);
		}
	}
}

void beagleIO::serialOpen(unsigned int pin) {
	int fd;
	char dirBuff[MAX_BUFF];

	// Check if pin is in table of pins
	if (checkGPIO(pin, SERIAL) == false) {
		fprintf(stderr, "Pin %d is a invalid pin or it is not a valid digital I/O.", pin);
		return;
	} else {
		snprintf(dirBuff, sizeof(dirBuff), FS_SERIAL_DIR, gpio_pins[pin - 1].alt);

		// Open the file location
		if ((fd = gpioOpen(dirBuff, O_RDWR | O_NOCTTY | O_NDELAY)) > 0) {
			gpio_pins[pin - 1].fd = fd;
		}
	}
}

void beagleIO::serialClose(unsigned int pin) {
	// Check if pin is in table of pins
	if (checkGPIO(pin, SERIAL) == false) {
		fprintf(stderr, "Pin %d is a invalid pin or it is not a valid digital I/O.", pin);
		return;
	} else {
		// Close the file location
		if (gpioClose(gpio_pins[pin - 1].fd) == 0) {
			gpio_pins[pin - 1].fd = 0;
		}
	}
}

void beagleIO::serialConfig(unsigned int pin) {

}

/*
 * Set Pin Mux Mode
 */

void beagleIO::pinSetMode(unsigned int pin, PIN_MUX mode, PIN_DIRECTION direction) {
	int fd;
	char dirBuff[MAX_BUFF];
	unsigned int omap_mux;

	// Check if pin is in table of pins
	if (checkGPIO(pin, DIGITAL bitor SERIAL bitor PWM) == false) {
		fprintf(stderr, "Pin %d is a invalid pin or it is not a valid digital I/O.", pin);
		return;
	} else {
		snprintf(dirBuff, sizeof(dirBuff), FS_MUX_DIR, gpio_pins[pin - 1].mux);

		omap_mux = mode bitor direction;

		// Open the file location
		fd = gpioOpen(dirBuff, O_WRONLY);

		gpioWrite(fd, omap_mux);

		// Close the file location
		gpioClose(fd);
	}
}

void beagleIO::pinSetMode(unsigned int pin, PIN_MUX mode, PIN_PULLUP_EN pullup_en, PIN_PULLUP pullup, PIN_DIRECTION direction, PIN_SLEW slew) {
	int fd;
	char dirBuff[MAX_BUFF];
	unsigned int omap_mux;

	// Check if pin is in table of pins
	if (checkGPIO(pin, DIGITAL bitor SERIAL bitor PWM) == false) {
		fprintf(stderr, "Pin %d is a invalid pin or it is not a valid digital I/O.", pin);
		return;
	} else {
		snprintf(dirBuff, sizeof(dirBuff), FS_MUX_DIR, gpio_pins[pin - 1].mux);

		omap_mux = mode bitor pullup_en bitor pullup bitor direction bitor slew;

		// Open the file location
		fd = gpioOpen(dirBuff, O_WRONLY);

		gpioWrite(fd, omap_mux);

		// Close the file location
		gpioClose(fd);
	}
}

/*
 * Analog Functions
 */

/*
int analogRead() {

	return 0;
}

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

bool beagleIO::checkGPIO(unsigned int pin, unsigned int type) {
	 if ((gpio_pins[pin - 1].type bitand type) > 0) {
		 return true;
	 }

	return false;
}

// Export the GPIO pin
int beagleIO::gpioExport(unsigned int pin) {
	int rc;
	int	fileDes;
	int buffLen;
	char dirBuff[MAX_BUFF];

	// Attempt to open file for write only
	if ((fileDes = gpioOpen(FS_EXPORT_DIR, O_WRONLY)) < 0) {
		return fileDes;
	} else {
		buffLen = snprintf(dirBuff, sizeof(dirBuff), "%d", pin);

		// Write pin number to export file
		gpioWrite(fileDes, dirBuff, buffLen);

		// Close export file
		if ((rc = gpioClose(fileDes)) < 0) {
			return rc;
		}

		gpio_pins[pin - 1].exported =  true;

		return 0;
	}
}

// Unexport the GPIO pin
int beagleIO::gpioUnexport(unsigned int pin) {
	int rc;
	int	fileDes;
	int buffLen;
	char dirBuff[MAX_BUFF];

	// Open file for write only
	if ((fileDes = gpioOpen(FS_UNEXPORT_DIR, O_WRONLY)) < 0) {
		return fileDes;
	} else {
		buffLen = snprintf(dirBuff, sizeof(dirBuff), "%d", pin);

		// Write pin to unexport file
		gpioWrite(fileDes, dirBuff, buffLen);

		// Close File
		if ((rc = close(fileDes)) < 0) {
			return rc;
		}

		gpio_pins[pin - 1].exported =  false;

		return 0;
	}
}

int beagleIO::gpioRead(int fileDes, char *readBuff) {
	int rc;

	// Read value of file
	if ((rc = read(fileDes, readBuff, strlen(readBuff))) < 0) {
		perror("GPIO Read");
	}

	return rc;
}

int beagleIO::gpioRead(int fileDes, long int *value, int base) {
	int rc;
	char tempBuff[MAX_BUFF];

	// Read value of file
	if ((rc = gpioRead(fileDes, tempBuff)) < 0) {
		return rc;
	} else {
		*value = strtol(tempBuff, NULL, base);
	}

	return 0;
}
int beagleIO::gpioWrite(int fileDes, const char *writeBuff, unsigned int size) {
	int rc;

	// Write buffer to file
	if ((rc = write(fileDes, writeBuff, size)) < 0) {
		perror("GPIO Write");
		return rc;
	}

	return 0;
}

int beagleIO::gpioWrite(int fileDes, int value) {
	int rc;
	int valueLen;
	char valueBuff[MAX_BUFF];

	valueLen = snprintf(valueBuff, sizeof(valueBuff), "%.2X", value);

	if ((rc = gpioWrite(fileDes, valueBuff, valueLen)) < 0) {
		return rc;
	}

	return 0;
}

int beagleIO::gpioOpen(const char *dir, int flags) {
	int	fileDes;

	// Open the file for write only
	if ((fileDes = open(dir, flags)) < 0) {
		perror("GPIO FD Open");
	}

	return fileDes;
}

int beagleIO::gpioClose(int file_des) {
	int rc;

	// Close the file
	if ((rc = close(file_des)) < 0) {
		perror("GPIO FD Close");
	}

	return rc;
}

/*

int beagleIO::gpioSetEdge(io_pin *gpio, PIN_EDGE edge) {
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
int beagleIO::gpioSetValue(io_pin* gpio, bool value) {
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

int beagleIO::gpioGetValue(io_pin *gpio, bool *value) {
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
int beagleIO::gpioSetDirection(io_pin *gpio, PIN_DIRECTION direction) {
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

int beagleIO::gpioSetMode(io_pin *gpio, unsigned int mode) {
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

