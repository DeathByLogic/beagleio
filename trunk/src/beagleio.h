/*
 * gpio.h
 *
 *  Created on: Feb 11,	2013
 *      Author: daniel@deathbylogic.com
 */

#ifndef BEAGLEIO_H_
#define BEAGLEIO_H_

#include <unistd.h>
#include "gpio.h"

// I/O Header Pins
io_pin P8_pins[46] = {
	{"GND",			0,		POWER,				NULL,				NULL		},
	{"GND",			0,		POWER,				NULL,				NULL		},
	{"GPIO1_6",		38,		DIGITAL,			"gpmc_ad6",			NULL		},
	{"GPIO1_7",		39,		DIGITAL,			"gpmc_ad7",			NULL		},
	{"GPIO1_2",		34,		DIGITAL,			"gpmc_ad2",			NULL		},
	{"GPIO1_3",		35,		DIGITAL,			"gpmc_ad3",			NULL		},
	{"TIMER4",		66,		DIGITAL,			"gpmc_advn_ale",	NULL		},
	{"TIMER7",		67,		DIGITAL,			"gpmc_oen_ren",		NULL		},
	{"TIMER5",		69,		DIGITAL,			"gpmc_ben0_cle",	NULL		},
	{"TIMER6",		68,		DIGITAL,			"gpmc_wen",			NULL		},
	{"GPIO1_13",	45,		DIGITAL,			"gpmc_ad13",		NULL		},
	{"GPIO1_12",	44,		DIGITAL,			"gpmc_ad12",		NULL		},
	{"EHRPWM2B",	23,		DIGITAL,			"gpmc_ad9",			NULL		},
	{"GPIO0_26",	26,		DIGITAL,			"gpmc_ad10",		NULL		},
	{"GPIO1_15",	47,		DIGITAL,			"gpmc_ad15",		NULL		},
	{"GPIO1_14",	46,		DIGITAL,			"gpmc_ad14",		NULL		},
	{"GPIO0_27",	27,		DIGITAL,			"gpmc_ad11",		NULL		},
	{"GPIO2_1",		65,		DIGITAL,			"gpmc_clk",			NULL		},
	{"EHRPWM2A",	22,		DIGITAL,			"gpmc_ad8",			NULL		},
	{"GPIO1_31",	63,		DIGITAL,			"gpmc_csn2",		NULL		},
	{"GPIO1_30",	62,		DIGITAL,			"gpmc_csn1",		NULL		},
	{"GPIO1_5",		37,		DIGITAL,			"gpmc_ad5",			NULL		},
	{"GPIO1_4",		36,		DIGITAL,			"gpmc_ad4",			NULL		},
	{"GPIO1_1",		33,		DIGITAL,			"gpmc_ad1",			NULL		},
	{"GPIO1_0",		32,		DIGITAL,			"gpmc_ad0",			NULL		},
	{"GPIO1_29",	61,		DIGITAL,			"gpmc_csn0",		NULL		},
	{"GPIO2_22",	86,		DIGITAL,			"lcd_vsync",		NULL		},
	{"GPIO2_24",	88,		DIGITAL,			"lcd_pclk",			NULL		},
	{"GPIO2_23",	87,		DIGITAL,			"lcd_hsync",		NULL		},
	{"GPIO2_25",	89,		DIGITAL,			"lcd_ac_bias_en",	NULL		},
	{"UART5_CTSN",	10,		DIGITAL,			"lcd_data14",		NULL		},
	{"UART5_RTSN",	11,		DIGITAL,			"lcd_data15",		NULL		},
	{"UART4_RTSN",	9,		DIGITAL,			"lcd_data13",		NULL		},
	{"UART3_RTSN",	81,		DIGITAL,			"lcd_data11",		NULL		},
	{"UART4_CTSN",	8,		DIGITAL,			"lcd_data12",		NULL		},
	{"UART3_CTSN",	80,		DIGITAL,			"lcd_data10",		NULL		},
	{"UART5_TXD",	78,		DIGITAL | SERIAL,	"lcd_data8",		"ttyO5"		},
	{"UART5_RXD",	79,		DIGITAL | SERIAL,	"lcd_data9",		"ttyO5"		},
	{"GPIO2_12",	76,		DIGITAL,			"lcd_data6",		NULL		},
	{"GPIO2_13",	77,		DIGITAL,			"lcd_data7",		NULL		},
	{"GPIO2_10",	74,		DIGITAL,			"lcd_data4",		NULL		},
	{"GPIO2_11",	75,		DIGITAL,			"lcd_data5",		NULL		},
	{"GPIO2_8",		72,		DIGITAL,			"lcd_data2",		NULL		},
	{"GPIO2_9",		73,		DIGITAL,			"lcd_data3",		NULL		},
	{"GPIO2_6",		70,		DIGITAL,			"lcd_data0",		NULL		},
	{"GPIO2_7",		71,		DIGITAL,			"lcd_data1",		NULL		}};

io_pin P9_pins[46] = {
	{"GND",			0,		POWER,				NULL,				NULL		},
	{"GND",			0,		POWER,				NULL,				NULL		},
	{"VDD_3V3EXP",	0,		POWER,				NULL,				NULL		},
	{"VDD_3V3EXP",	0,		POWER,				NULL,				NULL		},
	{"VDD_5V",		0,		POWER,				NULL,				NULL		},
	{"VDD_5V",		0,		POWER,				NULL,				NULL		},
	{"SYS_5V",		0,		POWER,				NULL,				NULL		},
	{"SYS_5V",		0,		POWER,				NULL,				NULL		},
	{"PWR_BUT",		0,		SYSTEM,				NULL,				NULL		},
	{"SYS_RESETn",	0,		SYSTEM,				NULL,				NULL		},
	{"UART4_RXD",	30,		DIGITAL | SERIAL,	"gpmc_wait0",		"ttyO4"		},
	{"GPIO1_28",	60,		DIGITAL,			"gpmc_ben1",		NULL		},
	{"UART4_TXD",	31,		DIGITAL | SERIAL,	"gpmc_wpn",			"ttyO4"		},
	{"EHRPWM1A",	50,		DIGITAL | PWM,		"gpmc_a2",			"ehrpwm.1:0"},
	{"GPIO1_16",	48,		DIGITAL,			"gpmc_a0",			NULL		},
	{"EHRPWM1B",	51,		DIGITAL | PWM,		"gpmc_a3",			"ehrpwm.1:1"},
	{"I2C1_SCL",	5,		DIGITAL,			"spi0_cs0",			NULL		},
	{"I2C1_SDA",	4,		DIGITAL,			"spi0_d1",			NULL		},
	{"I2C2_SCL",	13,		DIGITAL,			"uart1_rtsn",		NULL		},
	{"I2C2_SDA",	12,		DIGITAL,			"uart1_ctsn",		NULL		},
	{"UART2_TXD",	3,		DIGITAL | SERIAL,	"spi0_d0",			"ttyO2"		},
	{"UART2_RXD",	2,		DIGITAL | SERIAL,	"spi0_sclk",		"ttyO2"		},
	{"GPIO1_17",	49,		DIGITAL,			"gpmc_a1",			NULL		},
	{"UART1_TXD",	15,		DIGITAL | SERIAL,	"uart1_txd",		"ttyO1"		},
	{"GPIO3_21",	88,		DIGITAL,			"mcasp0_ahclkx",	NULL		},
	{"UART1_RXD",	14,		DIGITAL | SERIAL,	"uart1_rxd",		"ttyO1"		},
	{"GPIO3_19",	86,		DIGITAL,			"mcasp0_fsr",		NULL		},
	{"SPI1_CS0",	84,		DIGITAL,			"mcasp0_ahclkr",	NULL		},
	{"SPI1_D0",		82,		DIGITAL,			"mcasp0_fsx",		NULL		},
	{"SPI1_D1",		116,	DIGITAL,			"mscasp0_axr0", 	NULL		},
	{"SPI1_SCLK",	110,	DIGITAL,			"mcasp0_aclkx",		NULL		},
	{"VDD_ADC",		0,		POWER,				NULL,				NULL		},
	{"AIN4",		4,		ANALOG,				NULL, 				NULL		},
	{"GNDA_ADC",	0,		POWER,				NULL,				NULL		},
	{"AIN6",		6,		ANALOG,				NULL, 				NULL		},
	{"AIN5",		5,		ANALOG,				NULL, 				NULL		},
	{"AIN2",		2,		ANALOG,				NULL, 				NULL		},
	{"AIN3",		3,		ANALOG,				NULL, 				NULL		},
	{"AIN0",		0,		ANALOG,				NULL, 				NULL		},
	{"AIN1",		1,		ANALOG,				NULL, 				NULL		},
	{"CLKOUT2",		20,		DIGITAL,			"xdma_event_intr1",	NULL		},
	{"GPIO0_7",		7,		DIGITAL,			"ecap0_in_pwm0_out",NULL		},
	{"GND",			0,		POWER,				NULL,				NULL		},
	{"GND",			0,		POWER,				NULL,				NULL		},
	{"GND",			0,		POWER,				NULL,				NULL		},
	{"GND",			0,		POWER,				NULL,				NULL		}};

io_pin usr_pins[4] = {
	{"USR0",		53,		DIGITAL,			"gpmc_a5",			NULL		},
	{"USR1",		54,		DIGITAL,			"gpmc_a6",			NULL		},
	{"USR2",		55,		DIGITAL,			"gpmc_a7",			NULL		},
	{"USR3",		56,		DIGITAL,			"gpmc_a8",			NULL		}};

#endif /* BEAGLEIO_H_ */
