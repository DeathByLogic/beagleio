/*
 * gpio.h
 *
 *  Created on: Feb 11,	2013
 *      Author: D. Wassenberg
 */

#ifndef GPIO_H_
#define GPIO_H_

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
	DIGITAL		= 0x01,
	PWM			= 0x02,
	DIG_PWM		= 0x03,
	SERIAL		= 0x04,
	DIG_SER		= 0x05,
	PWM_SER		= 0x06,
	DIG_PWM_SER	= 0x07,
	ANALOG		= 0x08
};

enum PIN_EDGE {
	RISING_EDGE		= 0x01,
	FALLING_EDGE	= 0x02,
	BOTH_EDGES		= 0x03
};

#define TRUE	1
#define FALSE	0

// GPIO Directories
#define FS_SERIAL_DIR	"/dev/%s"
#define FS_MUX_DIR		"/sys/kernel/debug/omap_mux/%s"
#define	FS_VALUE_DIR	"/sys/class/gpio/gpio%d/value"
#define FS_DIR_DIR		"/sys/class/gpio/gpio%d/direction"
#define FS_EDGE_DIR		"/sys/class/gpio/gpio%d/edge"
#define FS_EXPORT_DIR	"/sys/class/gpio/export"
#define FS_UNEXPORT_DIR	"/sys/class/gpio/unexport"

// Misc Defines
#define MAX_BUFF	64

// Structures
typedef struct io_pin {
	const char		*ID;
	unsigned int	 pin;
	unsigned int	 type;
	const char		*mux;
	const char		*alt;
	bool	 		 exported;
} io_pin;

// Class Definition
class beagleIO {
public:
	beagleIO(io_pin*, int);
	~beagleIO();

	void digitalSetDirection(unsigned int, PIN_DIRECTION);
	void digitalSetEdge(unsigned int, PIN_EDGE);
	void digitalGetValue(unsigned int, bool*);
	bool digitalGetValue(unsigned int);
	void digitalSetValue(unsigned int, bool);

	void serialRead();
	void serialWrite(int, const char*, int size);
	int serialOpen(unsigned int);
	void serialClose(int);
	void serialConfig(unsigned int);

	int analogRead();

	void pwmRun(unsigned int);
	void pwmStop(unsigned int);
	void pwmConfig(unsigned int, unsigned int, unsigned int);
	void pwmSetFreq(unsigned int, unsigned int);
	void pwmSetDuty(unsigned int, unsigned int);

	void pinSetMode(unsigned int, PIN_MUX, PIN_DIRECTION);
	void pinSetMode(unsigned int, PIN_MUX, PIN_PULLUP_EN, PIN_PULLUP, PIN_DIRECTION, PIN_SLEW);

private:
	// Private functions
	int gpioExport(unsigned int, bool*);
	int gpioUnexport(unsigned int, bool*);

	int gpioSetDirection(io_pin*, PIN_DIRECTION);
	int gpioSetEdge(io_pin*, PIN_EDGE);

	int gpioSetValue(io_pin*, bool);
	int gpioGetValue(io_pin*, bool*);

	int gpioWrite(io_pin *, const char*, int size);

	int gpioSetMode(io_pin*, unsigned int);
	//int gpioGetMode(io_pin*, unsigned int*);

	int gpioFDOpen(const char*, int);
	int gpioFDClose(int);

	io_pin *findGPIO(unsigned int, unsigned int);

	// Private variables
	io_pin *gpio_pins;
	int 	gpio_count;
};

#endif /* GPIO_H_ */
