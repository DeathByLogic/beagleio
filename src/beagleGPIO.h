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

#ifndef BEAGLEGPIO_H_
#define BEAGLEGPIO_H_

// Includes
#include <string>

// Structures
typedef struct io_pin {
	const char		*ID;
	unsigned int	 pin;
	unsigned int	 type;
	const char		*mux;
	const char		*alt;
	bool			 exported;
} io_pin;

// Misc Defines
#define MAX_BUFF	64

// Class Definition
class beagleGPIO {
private:

protected:
	std::string	 _id;
	int 		 _fd;

	// Constructor
				 beagleGPIO(const std::string &id) : _id(id), _fd(0) { }

	// Open and close pin functions
	int			 gpioOpen(const char* dir, int flags);
	int			 gpioClose(int fd);

	// Read from pin file
	int			 gpioRead(int fd, void *str, unsigned int count);
	int			 gpioRead(int fd, int *value, unsigned int base);
	int			 gpioRead(int fd, int *value);

	// Write to pin file
	int			 gpioWrite(int fd, const void *str, unsigned int count);
	int			 gpioWrite(int fd, int value, unsigned int base);
	int			 gpioWrite(int fd, int value);

	// Search in a directory
	int			 dirSearch(const char *dir, const char *search, char *rtn);

public:
	// Deconstructor
	virtual		~beagleGPIO();

	// Virtual open and close pin functions
	virtual int	 openPin(int flags) = 0;
	virtual void closePin() = 0;

	// Misc Pin functions
	int			 getPinFD();
	bool		 isPinOpen();

	// digital object virtual functions
	//virtual void setDirection(PIN_DIRECTION) = 0;
	//virtual void setEdge(PIN_EDGE);
	//virtual void getValue(bool *value);
	//virtual bool getValue();
	//virtual void setValue(bool value);

	//virtual void pinSetMux(PIN_MUX, PIN_PULLUP_EN = PULLUP_ENABLED, PIN_PULLUP = PULLDOWN, PIN_DIRECTION = OUTPUT_PIN, PIN_SLEW = FAST_SLEW);
	//virtual int	pinExport();
	//virtual int	pinUnexport();


	// serial object virtual functions

	// pwm object virtual functions

	// analog object virtual functions
};


//class beagleGPIO {
//public:
//			beagleGPIO(io_pin*, int);
//			~beagleGPIO();
//
//	// Digital Functions
//	void	digitalSetDirection(unsigned int pin, PIN_DIRECTION);
//	void	digitalSetEdge(unsigned int pin, PIN_EDGE);
//
//	void	digitalGetValue(unsigned int pin , bool *value);
//	bool	digitalGetValue(unsigned int pin);
//
//	void	fdigitalGetValue(int fd, bool *value);
//	bool	fdigitalGetValue(int fd);
//
//	void	digitalSetValue(unsigned int pin, bool value);
//
//	// Analog Functions
//	void	analogRead(unsigned int pin, int *value);
//	int		analogRead(unsigned int pin);
//
//	// PWM Functions
//	void	pwmRun(unsigned int);
//	void	pwmStop(unsigned int);
//	void	pwmSetConfig(unsigned int, unsigned int, unsigned int);
//	void	pwmSetFreq(unsigned int, unsigned int);
//	void	pwmSetDuty(unsigned int, unsigned int);
//
//	// Configuration Functions
//	void	pinSetMux(unsigned int, PIN_MUX, PIN_PULLUP_EN = PULLUP_ENABLED, PIN_PULLUP = PULLDOWN, PIN_DIRECTION = OUTPUT_PIN, PIN_SLEW = FAST_SLEW);
//
//	int		pinExport(unsigned int pin);
//	int		pinUnexport(unsigned int pin);
//
//	int		pinOpen(unsigned int pin);
//	void	pinClose(int fd);
//
//private:
//	// Private functions
//	int		gpioRead(int, char*, int);
//	int		gpioRead(int, long int*, int = 0);
//
//	int		gpioWrite(int, const char*, unsigned int);
//	int		gpioWrite(int, int, int = 0);
//
//	int		gpioOpen(const char*, int);
//	int		gpioClose(int);
//
//	bool	checkGPIO(unsigned int, unsigned int);
//
//	// Private variables
//	io_pin	*gpio_pins;
//	int 	gpio_count;
//};

#endif /* BEAGLEGPIO_H_ */
