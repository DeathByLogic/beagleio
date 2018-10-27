/*
	Copyright (C) 2015 deathbylogic.com
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

#ifndef BEAGLEI2C_H_
#define BEAGLEI2C_H_

#include <string>

#include "beagleGPIO.h"
#include "beagleDigital.h"

// Terminal Directories
#define FS_I2C_DIR	"/dev/%s"

// Serial configuration constants


// Class definition
class beagleI2C: public beagleDigital  {
private:
	int			 _i2c_fd;
	std::string	 _i2c;

protected:

public:
	// Constructor & Deconstructor
				 beagleI2C(const std::string &id, const int index, const std::string &i2c) : beagleDigital(id, index), _i2c_fd(0), _i2c(i2c) {}
				~beagleI2C();

	// Serial Functions
	void	     writeTo(const void *str, char address, size_t size);
	void         requestFrom(void *str, char address, size_t size, bool consecutively);

	void		 readPort(void *str, size_t size);
	void		 writePort(const void *str, size_t size);

	int			 openPort(int address);
	void		 closePort();

	bool		 isPortOpen();
	int			 getPortFD();

};

#endif /* BEAGLEI2C_H_ */
