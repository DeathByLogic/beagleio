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
	{"GND",			0,		POWER,				NULL,				NULL,			false},
	{"GND",			0,		POWER,				NULL,				NULL,			false},
	{"GPIO1_6",		38,		DIGITAL,			"gpmc_ad6",			NULL,			false},
	{"GPIO1_7",		39,		DIGITAL,			"gpmc_ad7",			NULL,			false},
	{"GPIO1_2",		34,		DIGITAL,			"gpmc_ad2",			NULL,			false},
	{"GPIO1_3",		35,		DIGITAL,			"gpmc_ad3",			NULL,			false},
	{"TIMER4",		66,		DIGITAL,			"gpmc_advn_ale",	NULL,			false},
	{"TIMER7",		67,		DIGITAL,			"gpmc_oen_ren",		NULL,			false},
	{"TIMER5",		69,		DIGITAL,			"gpmc_ben0_cle",	NULL,			false},
	{"TIMER6",		68,		DIGITAL,			"gpmc_wen",			NULL,			false},
	{"GPIO1_13",	45,		DIGITAL,			"gpmc_ad13",		NULL,			false},
	{"GPIO1_12",	44,		DIGITAL,			"gpmc_ad12",		NULL,			false},
	{"EHRPWM2B",	23,		DIGITAL,			"gpmc_ad9",			NULL,			false},
	{"GPIO0_26",	26,		DIGITAL,			"gpmc_ad10",		NULL,			false},
	{"GPIO1_15",	47,		DIGITAL,			"gpmc_ad15",		NULL,			false},
	{"GPIO1_14",	46,		DIGITAL,			"gpmc_ad14",		NULL,			false},
	{"GPIO0_27",	27,		DIGITAL,			"gpmc_ad11",		NULL,			false},
	{"GPIO2_1",		65,		DIGITAL,			"gpmc_clk",			NULL,			false},
	{"EHRPWM2A",	22,		DIGITAL,			"gpmc_ad8",			NULL,			false},
	{"GPIO1_31",	63,		DIGITAL,			"gpmc_csn2",		NULL,			false},
	{"GPIO1_30",	62,		DIGITAL,			"gpmc_csn1",		NULL,			false},
	{"GPIO1_5",		37,		DIGITAL,			"gpmc_ad5",			NULL,			false},
	{"GPIO1_4",		36,		DIGITAL,			"gpmc_ad4",			NULL,			false},
	{"GPIO1_1",		33,		DIGITAL,			"gpmc_ad1",			NULL,			false},
	{"GPIO1_0",		32,		DIGITAL,			"gpmc_ad0",			NULL,			false},
	{"GPIO1_29",	61,		DIGITAL,			"gpmc_csn0",		NULL,			false},
	{"GPIO2_22",	86,		DIGITAL,			"lcd_vsync",		NULL,			false},
	{"GPIO2_24",	88,		DIGITAL,			"lcd_pclk",			NULL,			false},
	{"GPIO2_23",	87,		DIGITAL,			"lcd_hsync",		NULL,			false},
	{"GPIO2_25",	89,		DIGITAL,			"lcd_ac_bias_en",	NULL,			false},
	{"UART5_CTSN",	10,		DIGITAL,			"lcd_data14",		NULL,			false},
	{"UART5_RTSN",	11,		DIGITAL,			"lcd_data15",		NULL,			false},
	{"UART4_RTSN",	9,		DIGITAL,			"lcd_data13",		NULL,			false},
	{"UART3_RTSN",	81,		DIGITAL,			"lcd_data11",		NULL,			false},
	{"UART4_CTSN",	8,		DIGITAL,			"lcd_data12",		NULL,			false},
	{"UART3_CTSN",	80,		DIGITAL,			"lcd_data10",		NULL,			false},
	{"UART5_TXD",	78,		DIGITAL | SERIAL,	"lcd_data8",		"tty5",			false},
	{"UART5_RXD",	79,		DIGITAL | SERIAL,	"lcd_data9",		"tty5",			false},
	{"GPIO2_12",	76,		DIGITAL,			"lcd_data6",		NULL,			false},
	{"GPIO2_13",	77,		DIGITAL,			"lcd_data7",		NULL,			false},
	{"GPIO2_10",	74,		DIGITAL,			"lcd_data4",		NULL,			false},
	{"GPIO2_11",	75,		DIGITAL,			"lcd_data5",		NULL,			false},
	{"GPIO2_8",		72,		DIGITAL,			"lcd_data2",		NULL,			false},
	{"GPIO2_9",		73,		DIGITAL,			"lcd_data3",		NULL,			false},
	{"GPIO2_6",		70,		DIGITAL,			"lcd_data0",		NULL,			false},
	{"GPIO2_7",		71,		DIGITAL,			"lcd_data1",		NULL,			false}};

io_pin P9_pins[46] = {
	{"GND",			0,		POWER,				NULL,				NULL,			false},
	{"GND",			0,		POWER,				NULL,				NULL,			false},
	{"VDD_3V3EXP",	0,		POWER,				NULL,				NULL,			false},
	{"VDD_3V3EXP",	0,		POWER,				NULL,				NULL,			false},
	{"VDD_5V",		0,		POWER,				NULL,				NULL,			false},
	{"VDD_5V",		0,		POWER,				NULL,				NULL,			false},
	{"SYS_5V",		0,		POWER,				NULL,				NULL,			false},
	{"SYS_5V",		0,		POWER,				NULL,				NULL,			false},
	{"PWR_BUT",		0,		SYSTEM,				NULL,				NULL,			false},
	{"SYS_RESETn",	0,		SYSTEM,				NULL,				NULL,			false},
	{"UART4_RXD",	30,		DIGITAL | SERIAL,	"gpmc_wait0",		"tty4",			false},
	{"GPIO1_28",	60,		DIGITAL,			"gpmc_ben1",		NULL,			false},
	{"UART4_TXD",	31,		DIGITAL | SERIAL,	"gpmc_wpn",			"tty4",			false},
	{"EHRPWM1A",	50,		DIGITAL | PWM,		"gpmc_a2",			"ehrpwm.1:0",	false},
	{"GPIO1_16",	48,		DIGITAL,			"gpmc_a0",			NULL,			false},
	{"EHRPWM1B",	51,		DIGITAL | PWM,		"gpmc_a3",			"ehrpwm.1:1",	false},
	{"I2C1_SCL",	5,		DIGITAL,			"spi0_cs0",			NULL,			false},
	{"I2C1_SDA",	4,		DIGITAL,			"spi0_d1",			NULL,			false},
	{"I2C2_SCL",	13,		DIGITAL,			"uart1_rtsn",		NULL,			false},
	{"I2C2_SDA",	12,		DIGITAL,			"uart1_ctsn",		NULL,			false},
	{"UART2_TXD",	3,		DIGITAL | SERIAL,	"spi0_d0",			"tty2",			false},
	{"UART2_RXD",	2,		DIGITAL | SERIAL,	"spi0_sclk",		"tty2",			false},
	{"GPIO1_17",	49,		DIGITAL,			"gpmc_a1",			NULL,			false},
	{"UART1_TXD",	15,		DIGITAL | SERIAL,	"uart1_txd",		"tty1",			false},
	{"GPIO3_21",	88,		DIGITAL,			"mcasp0_ahclkx",	NULL,			false},
	{"UART1_RXD",	14,		DIGITAL | SERIAL,	"uart1_rxd",		"tty1",			false},
	{"GPIO3_19",	86,		DIGITAL,			"mcasp0_fsr",		NULL,			false},
	{"SPI1_CS0",	84,		DIGITAL,			"mcasp0_ahclkr",	NULL,			false},
	{"SPI1_D0",		82,		DIGITAL,			"mcasp0_fsx",		NULL,			false},
	{"SPI1_D1",		116,	DIGITAL,			"mscasp0_axr0", 	NULL,			false},
	{"SPI1_SCLK",	110,	DIGITAL,			"mcasp0_aclkx",		NULL,			false},
	{"VDD_ADC",		0,		POWER,				NULL,				NULL,			false},
	{"AIN4",		4,		ANALOG,				NULL, 				NULL,			false},
	{"GNDA_ADC",	0,		POWER,				NULL,				NULL,			false},
	{"AIN6",		6,		ANALOG,				NULL, 				NULL,			false},
	{"AIN5",		5,		ANALOG,				NULL, 				NULL,			false},
	{"AIN2",		2,		ANALOG,				NULL, 				NULL,			false},
	{"AIN3",		3,		ANALOG,				NULL, 				NULL,			false},
	{"AIN0",		0,		ANALOG,				NULL, 				NULL,			false},
	{"AIN1",		1,		ANALOG,				NULL, 				NULL,			false},
	{"CLKOUT2",		20,		DIGITAL,			"xdma_event_intr1",	NULL,			false},
	{"GPIO0_7",		7,		DIGITAL,			"ecap0_in_pwm0_out",NULL,			false},
	{"GND",			0,		POWER,				NULL,				NULL,			false},
	{"GND",			0,		POWER,				NULL,				NULL,			false},
	{"GND",			0,		POWER,				NULL,				NULL,			false},
	{"GND",			0,		POWER,				NULL,				NULL,			false}};

io_pin usr_pins[4] = {
	{"USR0",		53,		DIGITAL,			"gpmc_a5",			NULL,			false},
	{"USR1",		54,		DIGITAL,			"gpmc_a6",			NULL,			false},
	{"USR2",		55,		DIGITAL,			"gpmc_a7",			NULL,			false},
	{"USR3",		56,		DIGITAL,			"gpmc_a8",			NULL,			false}};

#endif /* BEAGLEIO_H_ */
