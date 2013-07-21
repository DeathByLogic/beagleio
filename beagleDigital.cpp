/*
 * beagleDigital.cpp
 *
 *  Created on: Jul 20, 2013
 *      Author: daniel
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "beagleGPIO.h"
#include "beagleDigital.h"

//beagleDigital::beagleDigital(const char *ID) {
//	beagleGPIO(ID);
//
//	//_mux = mux;
//}

beagleDigital::~beagleDigital() {
	// unexport pin
	if (_exported == true) {
		pinUnexport();
	}
}

void beagleDigital::getValue(bool *value) {
	int fd;
	char dirBuff[MAX_BUFF];
	long int tmpValue;

//	// Check if pin is in table of pins
//	if (checkGPIO(pin, DIGITAL) == false) {
//		fprintf(stderr, "BeagleIO: Pin %d is a invalid pin or it is not a valid digital I/O.\n", pin);
//		return;
//	} else {
		// Export pin if needed
		if (_exported == false) {
			fprintf(stderr, "BeagleIO: Pin %d has not been exported\n", _pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_VALUE_DIR, _pin);

			// Open the file location
			fd = gpioOpen(dirBuff, O_RDONLY);

			// Read the value of pin
			gpioRead(&tmpValue);

			// Close the file location
			gpioClose(fd);

			*value = (bool)tmpValue;
		}
//	}
}

bool beagleDigital::getValue() {
	bool tmpValue;

	// Read Digital Value
	getValue(&tmpValue);

	return tmpValue;
}

//void beagleGPIO::fdigitalGetValue(int fd, bool *value) {
//	long int tmpValue;
//
//	if (fd > 0) {
//		// Seek to the beginning of the file
//		lseek(fd, 0, SEEK_SET);
//
//		// Read the value of pin
//		gpioRead(fd, &tmpValue);
//
//		*value = (bool)tmpValue;
//	}
//}
//
//bool beagleGPIO::fdigitalGetValue(int fd) {
//	bool tmpValue;
//
//	// Read Digital Value
//	digitalGetValue(fd, &tmpValue);
//
//	return tmpValue;
//
//}

void beagleDigital::setValue(bool value) {
	int fd;
	char dirBuff[MAX_BUFF];

	// Check if pin is in table of pins
//	if (checkGPIO(pin, DIGITAL) == false) {
//		fprintf(stderr, "BeagleIO: Pin %d is a invalid pin or it is not a valid digital I/O.\n", pin);
//		return;
//	} else {
		// Export pin if needed
		if (_exported == false) {
			fprintf(stderr, "BeagleIO: Pin %d has not been exported\n", _pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_VALUE_DIR, _pin);

			// Open the file location
			fd = gpioOpen(dirBuff, O_WRONLY);

			// Write the value of pin
			gpioWrite(fd, value);

			// Close the file location
			gpioClose(fd);
		}
//	}
}

void beagleDigital::setDirection(PIN_DIRECTION direction) {
	int fd;
	char dirBuff[MAX_BUFF];

	// Check if pin is in table of pins
//	if (checkGPIO(pin, DIGITAL) == false) {
//		fprintf(stderr, "BeagleIO: Pin %d is a invalid pin or it is not a valid digital I/O.\n", pin);
//		return;
//	} else {
		// Export pin if needed
		if (_exported == false) {
			fprintf(stderr, "BeagleIO: Pin %d has not been exported\n", _pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_DIR_DIR, _pin);

			// Open the file location
			fd = gpioOpen(dirBuff, O_WRONLY);

			// Write direction to file
			switch (direction) {
			case INPUT_PIN:
				gpioWrite("in", 3);

				break;
			case OUTPUT_PIN:
				gpioWrite("out", 4);

				break;
			}

			// Close the file location
			gpioClose(fd);
		}
//	}
}

void beagleDigital::setEdge(PIN_EDGE edge) {
	int fd;
	char dirBuff[MAX_BUFF];

	// Check if pin is in table of pins
//	if (checkGPIO(pin, DIGITAL) == false) {
//		fprintf(stderr, "S: Pin %d is a invalid pin or it is not a valid digital I/O.\n", pin);
//		return;
//	} else {
		// Export pin if needed
		if (_exported == false) {
			fprintf(stderr, "BeagleIO: Pin %d has not been exported\n", _pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_EDGE_DIR, _pin);

			// Open the file location
			fd = gpioOpen(dirBuff, O_WRONLY);

			// Write direction to file
			switch (edge) {
			case NONE:
				gpioWrite("none", 5);

				break;
			case RISING_EDGE:
				gpioWrite("rising", 7);

				break;
			case FALLING_EDGE:
				gpioWrite("falling", 8);

				break;
			case BOTH_EDGES:
				gpioWrite("both", 5);

				break;
			}

			// Close the file location
			gpioClose(fd);
		}
//	}
}

/*
 * Set Pin Mux Mode
 */

void beagleDigital::pinSetMux(PIN_MUX mode, PIN_PULLUP_EN pullup_en, PIN_PULLUP pullup, PIN_DIRECTION direction, PIN_SLEW slew) {
	int fd;
	char dirBuff[MAX_BUFF];
	unsigned int omap_mux;

	// Check if pin is in table of pins
//	if (checkGPIO(pin, DIGITAL bitor SERIAL bitor PWM) == false) {
//		fprintf(stderr, "BeagleIO: Pin %d is a invalid pin or it is not a valid digital I/O.\n", pin);
//		return;
//	} else {
		snprintf(dirBuff, sizeof(dirBuff), FS_MUX_DIR, _mux);

		omap_mux = mode bitor pullup_en bitor pullup bitor direction bitor slew;

		// Open the file location
		fd = gpioOpen(dirBuff, O_WRONLY);

		gpioWrite(omap_mux, 16);

		// Close the file location
		gpioClose(fd);
//	}
}

// Export the GPIO pin
int beagleDigital::pinExport() {
	int rc;
	int	fileDes;
	int buffLen;
	char dirBuff[MAX_BUFF];

	// Attempt to open file for write only
	if ((fileDes = gpioOpen(FS_EXPORT_DIR, O_WRONLY)) < 0) {
		return fileDes;
	} else {
		buffLen = snprintf(dirBuff, sizeof(dirBuff), "%d", _pin);

		// Write pin number to export file
		if (gpioWrite(dirBuff, buffLen) > 0) {
			_exported =  true;

			printf("BeagleIO: Exported gpio%d\t(Pin %d)\n", _pin, _pin);
		}

		// Close export file
		if ((rc = gpioClose(fileDes)) < 0) {
			return rc;
		}

		return 0;
	}
}

// Unexport the GPIO pin
int beagleDigital::pinUnexport() {
	int rc;
	int	fileDes;
	int buffLen;
	char dirBuff[MAX_BUFF];

	// Open file for write only
	if ((fileDes = gpioOpen(FS_UNEXPORT_DIR, O_WRONLY)) < 0) {
		return fileDes;
	} else {
		buffLen = snprintf(dirBuff, sizeof(dirBuff), "%d", _pin);

		// Write pin to unexport file
		if (gpioWrite(dirBuff, buffLen) > 0) {
			_exported =  false;

			printf("BeagleIO: Unexported gpio%d\t(Pin %d)\n", _pin, _pin);
		}

		// Close File
		if ((rc = close(fileDes)) < 0) {
			return rc;
		}

		return 0;
	}
}

int beagleDigital::pinOpen() {
	//int fd;
	char dirBuff[MAX_BUFF];

//	if (checkGPIO(pin, DIGITAL bitor SERIAL bitor PWM bitor ANALOG) == false) {
//		fprintf(stderr, "BeagleIO: Pin %d is a invalid pin.\n", pin);
//		return -1;
//	} else {
		// Check in pin has been exported
		if (_exported == false) {
			fprintf(stderr, "BeagleIO: Pin %d has not been exported\n", _pin);
		} else {
			snprintf(dirBuff, sizeof(dirBuff), FS_VALUE_DIR, _pin);

			// Open the file location
			_fd = gpioOpen(dirBuff, O_RDONLY | O_NONBLOCK);
		}
//	}

	return _fd;
}

void beagleDigital::pinClose() {
	gpioClose(_fd);
}
