/*
 * beagleGPIO.h
 *
 *  Created on: Mar 24, 2013
 *      Author: daniel@deathbylogic.com
 */

#ifndef BEAGLEGPIO_H_
#define BEAGLEGPIO_H_

// Structures
typedef struct io_pin {
	const char		*ID;
	unsigned int	 pin;
	unsigned int	 type;
	const char		*mux;
	const char		*alt;
	bool			 exported;
} io_pin;

// GPIO Configuration Constants
enum PIN_MUX {
	MUX_0	= 0x00,
	MUX_1	= 0x01,
	MUX_2	= 0x02,
	MUX_3	= 0x03,
	MUX_4	= 0x04,
	MUX_5	= 0x05,
	MUX_6	= 0x06,
	MUX_7	= 0x07
};

enum PIN_PULLUP_EN {
	PULLUP_ENABLED	= 0x00,
	PULLUP_DISABLED	= 0x08
};

enum PIN_PULLUP {
	PULLDOWN	= 0x00,
	PULLUP		= 0x10
};

enum PIN_DIRECTION {
	INPUT_PIN	= 0x20,
	OUTPUT_PIN	= 0x00
};

enum PIN_SLEW {
	FAST_SLEW	= 0x00,
	SLOW_SLEW	= 0x40
};

// Other GPIO constants
enum PIN_VALUE {
	LOW		= 0,
	HIGH	= 1
};

enum PIN_TYPE {
	POWER		= 0x00,
	SYSTEM		= 0x00,
	DIGITAL		= 0x01,
	PWM			= 0x02,
	SERIAL		= 0x04,
	ANALOG		= 0x08
};

enum PIN_EDGE {
	NONE			= 0x00,
	RISING_EDGE		= 0x01,
	FALLING_EDGE	= 0x02,
	BOTH_EDGES		= 0x03
};

// Misc Defines
#define MAX_BUFF	64

// GPIO Directories
#define FS_SERIAL_DIR	"/dev/%s"
#define FS_MUX_DIR		"/sys/kernel/debug/omap_mux/%s"
#define	FS_VALUE_DIR	"/sys/class/gpio/gpio%d/value"
#define FS_DIR_DIR		"/sys/class/gpio/gpio%d/direction"
#define FS_EDGE_DIR		"/sys/class/gpio/gpio%d/edge"
#define FS_EXPORT_DIR	"/sys/class/gpio/export"
#define FS_UNEXPORT_DIR	"/sys/class/gpio/unexport"
#define FS_ANALOG_DIR	"/sys/devices/platform/omap/tsc/%s"

// Class Definition
class beagleGPIO {
private:
	const char	*_ID;

	//beagleGPIO();

protected:
				 beagleGPIO(const char *ID) : _ID(ID) { }

	unsigned int _pin;
	bool 		 _exported;

	int 		 _fd;

	int          gpioOpen(const char*, int);
	int			 gpioClose(int);

	int	 		 gpioRead(char*, int);
	int	 		 gpioRead(long int*, int = 0);

	int			 gpioWrite(const char*, unsigned int);
	int			 gpioWrite(int, int = 0);

public:


	virtual		~beagleGPIO() = 0;

	// global object functions
	virtual int	 pinOpen();
	virtual void pinClose();

	// digital object virtual functions
	virtual void setDirection(PIN_DIRECTION);
	virtual void setEdge(PIN_EDGE);
	virtual void getValue(bool *value);
	virtual bool getValue();
	virtual void setValue(bool value);

	virtual void pinSetMux(PIN_MUX, PIN_PULLUP_EN = PULLUP_ENABLED, PIN_PULLUP = PULLDOWN, PIN_DIRECTION = OUTPUT_PIN, PIN_SLEW = FAST_SLEW);
	virtual int	 pinExport();
	virtual int  pinUnexport();


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
