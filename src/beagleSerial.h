/*
	Copyright (C) 2013 deathbylogic.com
	Author: daniel@deathbylogic.com

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BEAGLESERIAL_H_
#define BEAGLESERIAL_H_

#include <termios.h>
#include <string>

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
	std::string	 _tty;

protected:

public:
	// Constructor & Deconstructor
				 beagleSerial(const std::string &id, const int index, const std::string &tty) : beagleDigital(id, index), _tty_fd(0), _tty(tty) {}
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
