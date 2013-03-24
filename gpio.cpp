/*
 * gpio.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: D. Wassenberg
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "gpio.h"

using namespace std;

//
// Constructor & Deconstructor
//

beagleIO::beagleIO(io_pin *pins, int count):gpio_pins( pins ), gpio_count( count ) {
	// Empty Constructor
}

beagleIO::~beagleIO() {
	// Unexport all pins
	for (int i = 0; i < gpio_count; i++) {
		if (gpio_pins[i].exported) {
			gpioUnexport(gpio_pins[i].pin, &gpio_pins[i].exported);
		}
	}
}

//
// GPIO User Functions
//

void beagleIO::digitalSetDirection(unsigned int pin, PIN_DIRECTION direction) {
	io_pin *gpio;

	gpio = findGPIO(pin, DIGITAL);

	// Check if pin is in table of pins
	if (gpio == NULL) {
		fprintf(stderr, "Unable to find gpio pin in table");
		return;
	} else {
		// Export pin if needed
		if (!gpio->exported) {
			// Check if export succeeded
			if (gpioExport(gpio->pin, &gpio->exported)) {
				return;
			}
		}

		// Set direction of pin
		gpioSetDirection(gpio, direction);
	}
}

void beagleIO::digitalSetEdge(unsigned int pin, PIN_EDGE edge) {
	io_pin *gpio;

	gpio = findGPIO(pin, DIGITAL);

	// Check if pin is in table of pins
	if (gpio == NULL) {
		fprintf(stderr, "Unable to find gpio pin in table");
		return;
	} else {
		// Export pin if needed
		if (!gpio->exported) {
			// Check if export succeeded
			if (gpioExport(gpio->pin, &gpio->exported)) {
				return;
			}
		}

		// Set direction of pin
		gpioSetEdge(gpio, edge);
	}
}

void beagleIO::digitalGetValue(unsigned int pin, bool *value) {
	io_pin *gpio;
	bool tmp_value;

	gpio = findGPIO(pin, DIGITAL);

	// Check if pin is in table of pins
	if (gpio == NULL) {
		fprintf(stderr, "Unable to find gpio pin in table");
		return;
	} else {
		// Export pin if needed
		if (!gpio->exported) {
			// Check if export succeeded
			if (gpioExport(gpio->pin, &gpio->exported)) {
				return;
			}
		}

		// Get value of pin
		gpioGetValue(gpio, &tmp_value);

		*value = (bool)tmp_value;
	}
}

bool beagleIO::digitalGetValue(unsigned int pin) {
	io_pin *gpio;
	bool tmp_value;

	gpio = findGPIO(pin, DIGITAL);

	// Check if pin is in table of pins
	if (gpio == NULL) {
		fprintf(stderr, "Unable to find gpio pin in table");
		return 0;
	} else {
		// Export pin if needed
		if (!gpio->exported) {
			// Check if export succeeded
			if (gpioExport(gpio->pin, &gpio->exported)) {
				return 0;
			}
		}

		// Get value of pin
		gpioGetValue(gpio, &tmp_value);
	}

	return (bool)tmp_value;
}

void beagleIO::digitalSetValue(unsigned int pin, bool value) {
	io_pin *gpio;

	gpio = findGPIO(pin, DIGITAL);

	// Check if pin is in table of pins
	if (gpio == NULL) {
		fprintf(stderr, "Unable to find gpio pin in table");
	} else {
		// Export pin if needed
		if (!gpio->exported) {
			gpioExport(gpio->pin, &gpio->exported);
		}

		// Get value of pin
		gpioSetValue(gpio, (int)value);
	}
}

//
// Serial functions
//

void beagleIO::serialRead() {

}

void beagleIO::serialWrite(unsigned int pin, const char *buff, int size) {
	io_pin *gpio;

	gpio = findGPIO(pin, SERIAL);

	// Check if pin is in table of pins
	if (gpio == NULL) {
		fprintf(stderr, "Unable to find gpio pin in table");
		return;
	} else {
		// Write string to pin
		gpioWrite(gpio, buff, size);
	}
}

int beagleIO::serialOpen(unsigned int pin) {

}

void beagleIO::serialClose(unsigned int pin) {

}

void beagleIO::serialConfig(unsigned int pin) {

}

//
// Analog functions
//

int beagleIO::analogRead() {

	return 0;
}

void beagleIO::pwmRun(unsigned int) {

}

void beagleIO::pwmStop(unsigned int) {

}

void beagleIO::pwmConfig(unsigned int, unsigned int, unsigned int) {

}

void beagleIO::pwmSetFreq(unsigned int, unsigned int) {

}

void beagleIO::pwmSetDuty(unsigned int, unsigned int) {

}

void beagleIO::pinSetMode(unsigned int pin, PIN_MUX mode, PIN_DIRECTION direction) {
	unsigned int omap_mux;
	io_pin *gpio;

	// Find gpio pin
	gpio = findGPIO(pin, DIGITAL);

	if (gpio == NULL) {
		fprintf(stderr, "GPIO Set Mode: Unable to find gpio");
	} else {
		// Get the current mode
		//gpioGetMode(gpio, &omap_mux);

		// Clear Mux bits
		//omap_mux = omap_mux bitand 0xF8;

		// Set new Mux bits
		omap_mux = mode bitor direction;

		// Set the new mode
		gpioSetMode(gpio, omap_mux);
	}
}

void beagleIO::pinSetMode(unsigned int pin, PIN_MUX mode, PIN_PULLUP_EN pullup_en, PIN_PULLUP pullup, PIN_DIRECTION dir, PIN_SLEW slew) {
	unsigned int omap_mux;
	io_pin *gpio;

	// Find gpio pin
	gpio = findGPIO(pin, DIGITAL);

	if (gpio == NULL) {
		fprintf(stderr, "GPIO Set Mode: Unable to find gpio");
	} else {
		// Set new Mux bits
		omap_mux = mode bitor pullup_en bitor pullup bitor dir bitor slew;

		// Set the new mode
		gpioSetMode(gpio, omap_mux);
	}
}

//
// GPIO File Access Functions
//

io_pin *beagleIO::findGPIO(unsigned int pin, unsigned int type) {
	 for (int i = 0; i < gpio_count; i++) {
		 if ((gpio_pins[i].pin == pin) and (gpio_pins[i].type bitand type)) {
			 return &gpio_pins[i];
		 }
	 }

	return NULL;
}

// Export the GPIO pin
int beagleIO::gpioExport(unsigned int pin, bool *exported) {
	int rc;
	int	fileDes;
	int buffLen;
	char dirBuff[MAX_BUFF];

	// Attempt to open file for write only
	if ((fileDes = open(FS_EXPORT_DIR, O_WRONLY)) < 0) {
		perror("GPIO Export");
		return fileDes;
	} else {
		buffLen = snprintf(dirBuff, sizeof(dirBuff), "%d", pin);

		// Write pin number to export file
		if ((rc = write(fileDes, dirBuff, buffLen)) < 0) {
			perror("GPIO Export");
			return rc;
		}

		// Close export file
		if ((rc = close(fileDes)) < 0) {
			perror("GPIO Export");
			return rc;
		}

		// Mark pin as exported
		*exported = TRUE;

		return 0;
	}
}

// Unexport the GPIO pin
int beagleIO::gpioUnexport(unsigned int pin, bool *exported) {
	int rc;
	int	fileDes;
	int buffLen;
	char dirBuff[MAX_BUFF];

	// Open file for write only
	if ((fileDes = open(FS_UNEXPORT_DIR, O_WRONLY)) < 0) {
		perror("GPIO Unexport");
		return fileDes;
	} else {
		buffLen = snprintf(dirBuff, sizeof(dirBuff), "%d", pin);

		// Write pin to unexport file
		if ((rc = write(fileDes, dirBuff, buffLen)) < 0) {
			perror("GPIO Unexport");
			return rc;
		}

		// Close File
		if ((rc = close(fileDes)) < 0) {
			perror("GPIO Unexport");
			return rc;
		}

		// Mark pin as unexported
		*exported = FALSE;

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

int beagleIO::gpioWrite(io_pin *gpio, const char *buff, int size) {
	int rc;
	int fileDes;
	char dirBuff[MAX_BUFF];

	snprintf(dirBuff, sizeof(dirBuff), FS_SERIAL_DIR, gpio->alt);

	// Open file for write only
	if ((fileDes = open(dirBuff, O_WRONLY)) < 0) {
		perror("GPIO Write");
		return fileDes;
	} else {
		// Write buffer to file
		if ((rc = write(fileDes, buff, size)) < 0) {
			perror("GPIO Write");
			return fileDes;
		}

		// Close edge file
		if ((rc = close(fileDes)) < 0) {
			perror("GPIO Write");
			return rc;
		}
	}
	return 0;
}

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

int beagleIO::gpioSetMode(io_pin *gpio, unsigned int mode) {
	int rc;
	int	fileDes;
	char modeBuff[MAX_BUFF];
	char dirBuff[MAX_BUFF];

	snprintf(dirBuff, sizeof(dirBuff), FS_MUX_DIR, gpio->mux);

	// Open file for write only
	if ((fileDes = open(dirBuff, O_WRONLY)) < 0) {
		perror("GPIO Set Edge");
		return fileDes;
	} else {
		// Print mode into string
		snprintf(modeBuff, sizeof(modeBuff), "%.2X", mode);

		// Write the value to set config
		if ((rc = write(fileDes, modeBuff, strlen(modeBuff) + 1)) < 0) {
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

/*
int beagleIO::gpioGetMode(io_pin *gpio, unsigned int *mode) {
	int rc;
	int	fileDes;
	char modeBuff[MAX_BUFF];
	char dirBuff[MAX_BUFF];

	snprintf(dirBuff, sizeof(dirBuff), FS_MUX_DIR, gpio->mux);
	printf("%s\n",dirBuff);

	// Open file for read only
	if ((fileDes = open(dirBuff, O_RDONLY)) < 0) {
		perror("GPIO Get Config");
		return fileDes;
	} else {
		// Read value of file
		if ((rc = read(fileDes, modeBuff, strlen(modeBuff))) < 0) {
			perror("GPIO Get Config");
			return rc;
		}

		printf("OMAP (chr): %s\n", modeBuff);

		// Parse string for HEX value
		*mode = strtol(modeBuff, NULL, 16);

		// Close file
		if ((rc = close(fileDes)) < 0) {
			perror("GPIO Get Config");
			return rc;
		}

		return 0;
	}
}
*/

int beagleIO::gpioFDOpen(const char *dir, int flags) {
	int	fileDes;
	char dirBuff[MAX_BUFF];

	// Open the file for write only
	if ((fileDes = open(dir, flags)) < 0) {
		perror("GPIO FD Open");
	}

	return fileDes;
}

int beagleIO::gpioFDClose(int file_des) {
	int rc;

	// Close the file
	if ((rc = close(file_des)) < 0) {
		perror("GPIO FD Close");
	}

	return rc;
}
