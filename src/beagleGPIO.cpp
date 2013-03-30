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
 * Constructor & Deconstructor
 */

beagleGPIO::beagleGPIO(io_pin *pins, int count) {
	gpio_pins = pins;
	gpio_count = count;

	for (int i = 0; i < gpio_count; i++) {
		gpio_pins[i].exported = false;
	}
}

beagleGPIO::~beagleGPIO() {
	// Unexport all pins
	for (int i = 0; i < gpio_count; i++) {
		if (gpio_pins[i].exported) {
			pinUnexport(i + 1);
		}
	}
}

/*
 * Digital Functions
 */

void beagleGPIO::digitalGetValue(unsigned int pin, bool *value) {
	int fd;
	char dirBuff[MAX_BUFF];
	long int tmpValue;

	// Check if pin is in table of pins
	if (checkGPIO(pin, DIGITAL) == false) {
		fprintf(stderr, "BeagleIO: Pin %d is a invalid pin or it is not a valid digital I/O.\n", pin);
		return;
	} else {
		// Export pin if needed
		if (gpio_pins[pin - 1].exported == false) {
			fprintf(stderr, "BeagleIO: Pin %d has not been exported\n", pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_VALUE_DIR, gpio_pins[pin - 1].pin);

			// Open the file location
			fd = gpioOpen(dirBuff, O_RDONLY);

			// Read the value of pin
			gpioRead(fd, &tmpValue);

			// Close the file location
			gpioClose(fd);

			*value = (bool)tmpValue;
		}
	}
}

bool beagleGPIO::digitalGetValue(unsigned int pin) {
	bool tmpValue;

	// Read Digital Value
	digitalGetValue(pin, &tmpValue);

	return tmpValue;
}

void beagleGPIO::digitalSetValue(unsigned int pin, bool value) {
	int fd;
	char dirBuff[MAX_BUFF];

	// Check if pin is in table of pins
	if (checkGPIO(pin, DIGITAL) == false) {
		fprintf(stderr, "BeagleIO: Pin %d is a invalid pin or it is not a valid digital I/O.\n", pin);
		return;
	} else {
		// Export pin if needed
		if (gpio_pins[pin - 1].exported == false) {
			fprintf(stderr, "BeagleIO: Pin %d has not been exported\n", pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_VALUE_DIR, gpio_pins[pin - 1].pin);

			// Open the file location
			fd = gpioOpen(dirBuff, O_WRONLY);

			// Write the value of pin
			gpioWrite(fd, value);

			// Close the file location
			gpioClose(fd);
		}
	}
}

void beagleGPIO::digitalSetDirection(unsigned int pin, PIN_DIRECTION direction) {
	int fd;
	char dirBuff[MAX_BUFF];

	// Check if pin is in table of pins
	if (checkGPIO(pin, DIGITAL) == false) {
		fprintf(stderr, "BeagleIO: Pin %d is a invalid pin or it is not a valid digital I/O.\n", pin);
		return;
	} else {
		// Export pin if needed
		if (gpio_pins[pin - 1].exported == false) {
			fprintf(stderr, "BeagleIO: Pin %d has not been exported\n", pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_DIR_DIR, gpio_pins[pin - 1].pin);

			// Open the file location
			fd = gpioOpen(dirBuff, O_WRONLY);

			// Write direction to file
			switch (direction) {
			case INPUT_PIN:
				gpioWrite(fd, "in", 3);

				break;
			case OUTPUT_PIN:
				gpioWrite(fd, "out", 4);

				break;
			}

			// Close the file location
			gpioClose(fd);
		}
	}
}

void beagleGPIO::digitalSetEdge(unsigned int pin, PIN_EDGE edge) {
	int fd;
	char dirBuff[MAX_BUFF];

	// Check if pin is in table of pins
	if (checkGPIO(pin, DIGITAL) == false) {
		fprintf(stderr, "S: Pin %d is a invalid pin or it is not a valid digital I/O.\n", pin);
		return;
	} else {
		// Export pin if needed
		if (gpio_pins[pin - 1].exported == false) {
			fprintf(stderr, "BeagleIO: Pin %d has not been exported\n", pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_DIR_DIR, gpio_pins[pin - 1].pin);

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
 * Set Pin Mux Mode
 */

void beagleGPIO::pinSetMux(unsigned int pin, PIN_MUX mode) {
	int fd;
	char dirBuff[MAX_BUFF];

	// Check if pin is in table of pins
	if (checkGPIO(pin, DIGITAL bitor SERIAL bitor PWM) == false) {
		fprintf(stderr, "Pin %d is a invalid pin or it is not a valid digital I/O.\n", pin);
		return;
	} else {
		snprintf(dirBuff, sizeof(dirBuff), FS_MUX_DIR, gpio_pins[pin - 1].mux);

		// Open the file location
		fd = gpioOpen(dirBuff, O_WRONLY);

		gpioWrite(fd, mode, 16);

		// Close the file location
		gpioClose(fd);
	}
}

void beagleGPIO::pinSetMux(unsigned int pin, PIN_MUX mode, PIN_PULLUP_EN pullup_en, PIN_PULLUP pullup, PIN_DIRECTION direction, PIN_SLEW slew) {
	int fd;
	char dirBuff[MAX_BUFF];
	unsigned int omap_mux;

	// Check if pin is in table of pins
	if (checkGPIO(pin, DIGITAL bitor SERIAL bitor PWM) == false) {
		fprintf(stderr, "BeagleIO: Pin %d is a invalid pin or it is not a valid digital I/O.\n", pin);
		return;
	} else {
		snprintf(dirBuff, sizeof(dirBuff), FS_MUX_DIR, gpio_pins[pin - 1].mux);

		omap_mux = mode bitor pullup_en bitor pullup bitor direction bitor slew;

		// Open the file location
		fd = gpioOpen(dirBuff, O_WRONLY);

		gpioWrite(fd, omap_mux, 16);

		// Close the file location
		gpioClose(fd);
	}
}

// Export the GPIO pin
int beagleGPIO::pinExport(unsigned int pin) {
	int rc;
	int	fileDes;
	int buffLen;
	char dirBuff[MAX_BUFF];

	// Attempt to open file for write only
	if ((fileDes = gpioOpen(FS_EXPORT_DIR, O_WRONLY)) < 0) {
		return fileDes;
	} else {
		buffLen = snprintf(dirBuff, sizeof(dirBuff), "%d", gpio_pins[pin - 1].pin);

		// Write pin number to export file
		if (gpioWrite(fileDes, dirBuff, buffLen) > 0) {
			gpio_pins[pin - 1].exported =  true;

			printf("BeagleIO: Exported gpio%d\t(Pin %d)\n", gpio_pins[pin - 1].pin, pin);
		}

		// Close export file
		if ((rc = gpioClose(fileDes)) < 0) {
			return rc;
		}

		return 0;
	}
}

// Unexport the GPIO pin
int beagleGPIO::pinUnexport(unsigned int pin) {
	int rc;
	int	fileDes;
	int buffLen;
	char dirBuff[MAX_BUFF];

	// Open file for write only
	if ((fileDes = gpioOpen(FS_UNEXPORT_DIR, O_WRONLY)) < 0) {
		return fileDes;
	} else {
		buffLen = snprintf(dirBuff, sizeof(dirBuff), "%d", gpio_pins[pin - 1].pin);

		// Write pin to unexport file
		if (gpioWrite(fileDes, dirBuff, buffLen) > 0) {
			gpio_pins[pin - 1].exported =  false;

			printf("BeagleIO: Unexported gpio%d\t(Pin %d)\n", gpio_pins[pin - 1].pin, pin);
		}

		// Close File
		if ((rc = close(fileDes)) < 0) {
			return rc;
		}

		return 0;
	}
}

/*
 * Analog Functions
 */

void beagleGPIO::analogRead(unsigned int pin, int *value) {
	int fd;
	char dirBuff[MAX_BUFF];
	long int tmpValue;

	// Check if pin is in table of pins
	if (checkGPIO(pin, ANALOG) == false) {
		fprintf(stderr, "BeagleIO: Pin %d is a invalid pin or it is not a valid analog input.\n", pin);
		return;
	} else {
		snprintf(dirBuff, sizeof(dirBuff), FS_ANALOG_DIR, gpio_pins[pin - 1].alt);

		// Open the file location
		fd = gpioOpen(dirBuff, O_RDONLY);

		// Read the value of pin
		gpioRead(fd, &tmpValue);

		// Close the file location
		gpioClose(fd);

		*value = tmpValue;
	}
}

int beagleGPIO::analogRead(unsigned int pin) {
	int tmpValue;

	analogRead(pin, &tmpValue);

	return tmpValue;
}

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

bool beagleGPIO::checkGPIO(unsigned int pin, unsigned int type) {
	 if ((gpio_pins[pin - 1].type bitand type) > 0) {
		 return true;
	 }

	return false;
}

int beagleGPIO::gpioRead(int fileDes, char *readBuff, int count) {
	int rc;

	// Read value of file
	if ((rc = read(fileDes, readBuff, count)) < 0) {
		perror("BeagleIO: Unable to read from file ");
	}

	return rc;
}

int beagleGPIO::gpioRead(int fileDes, long int *value, int base) {
	int rc;
	char tempBuff[MAX_BUFF];

	// Read value of file
	if ((rc = gpioRead(fileDes, tempBuff, MAX_BUFF)) < 0) {
		return rc;
	} else {
		*value = strtol(tempBuff, NULL, base);
	}

	return 0;
}
int beagleGPIO::gpioWrite(int fileDes, const char *writeBuff, unsigned int size) {
	int rc;

	// Write buffer to file
	if ((rc = write(fileDes, writeBuff, size + 1)) < 0) {
		perror("BeagleIO: Unable to write to file ");
	}

	return rc;
}

int beagleGPIO::gpioWrite(int fileDes, int value, int base) {
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

	rc = gpioWrite(fileDes, valueBuff, valueLen);

	return rc;
}

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

