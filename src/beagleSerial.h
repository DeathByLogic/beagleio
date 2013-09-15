/*
 * beagleSerial.h
 *
 *  Created on: Mar 29, 2013
 *      Author: daniel@deathbylogic.com
 */

#ifndef BEAGLESERIAL_H_
#define BEAGLESERIAL_H_

#include <termios.h>

#include "beagleGPIO.h"
#include "beagleDigital.h"

using namespace std;

// Terminal Directories
#define FS_SERIAL_DIR	"/dev/%s"

// Serial configuration constants
enum BAUD {
	BR_75		= B75,
	BR_110		= B110,
	BR_300		= B300,
	BR_1200		= B1200,
	BR_2400		= B2400,
	BR_4800		= B4800,
	BR_9600		= B9600,
	BR_19200	= B19200,
	BR_38400	= B38400,
	BR_57600	= B57600,
	BR_115200	= B115200
};

enum BYTE_SIZE {
	BS_5_BIT	= CS5,
	BS_6_BIT	= CS6,
	BS_7_BIT	= CS7,
	BS_8_BIT	= CS8
};

enum PARITY_BIT {
	PB_NONE		= 0x0000,
	PB_EVEN		= PARENB,
	PB_ODD		= PARENB | PARODD
};

enum STOP_BIT {
	SB_ONE		= 0x0000,
	SB_TWO		= CSTOPB
};

// Class definition
class beagleSerial: public beagleDigital  {
private:
	int			 _tty_fd;
	const char	*_tty;

protected:

public:
	// Constructor & Deconstructor
				 beagleSerial(const char *id, const int index, const char *tty) : beagleDigital(id, index), _tty(tty) {}
				~beagleSerial();

	// Serial Functions
	void		 readPort(void *str, unsigned int count);
	void		 writePort(const void *str, unsigned int count);

	int			 openPort(BAUD, PARITY_BIT = PB_NONE, BYTE_SIZE = BS_8_BIT, STOP_BIT = SB_ONE);
	void		 closePort();
	void		 configPort(BAUD, PARITY_BIT = PB_NONE, BYTE_SIZE = BS_8_BIT, STOP_BIT = SB_ONE);

	bool		 isPortOpen();
	int			 getPortFD();

};

#endif /* BEAGLESERIAL_H_ */
