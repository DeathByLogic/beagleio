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

#include "beagleIO.h"

/*
 * P8 Header Pins
 */

beagleDigital P8_03("GPIO1_6",		38);
beagleDigital P8_04("GPIO1_7",		39);
beagleDigital P8_05("GPIO1_2",		34);
beagleDigital P8_06("GPIO1_3",		35);
beagleDigital P8_07("TIMER4",		66);
beagleDigital P8_08("TIMER7",		67);
beagleDigital P8_09("TIMER5",		69);
beagleDigital P8_10("TIMER6",		68);
beagleDigital P8_11("GPIO1_13",		45);
beagleDigital P8_12("GPIO1_12",		44);
beagleDigital P8_13("EHRPWM2B",		23);
beagleDigital P8_14("GPIO0_26",		26);
beagleDigital P8_15("GPIO1_15",		47);
beagleDigital P8_16("GPIO1_14",		46);
beagleDigital P8_17("GPIO0_27",		27);
beagleDigital P8_18("GPIO2_1",		65);
beagleDigital P8_19("EHRPWM2A",		22);
beagleDigital P8_20("GPIO1_31",		63);
beagleDigital P8_21("GPIO1_30",		62);
beagleDigital P8_22("GPIO1_5",		37);
beagleDigital P8_23("GPIO1_4",		36);
beagleDigital P8_24("GPIO1_1",		33);
beagleDigital P8_25("GPIO1_0",		32);
beagleDigital P8_26("GPIO1_29",		61);
beagleDigital P8_27("GPIO2_22",		86);
beagleDigital P8_28("GPIO2_24",		88);
beagleDigital P8_29("GPIO2_23",		87);
beagleDigital P8_30("GPIO2_25",		89);
beagleDigital P8_31("UART5_CTSN",	10);
beagleDigital P8_32("UART5_RTSN",	11);
beagleDigital P8_33("UART4_RTSN",	9);
beagleDigital P8_34("UART3_RTSN",	81);
beagleDigital P8_35("UART4_CTSN",	8);
beagleDigital P8_36("UART3_CTSN",	80);
beagleSerial  P8_37("UART5_TXD",	78, 	"ttyO5");
beagleSerial  P8_38("UART5_RXD",	79,		"ttyO5");
beagleDigital P8_39("GPIO2_12",		76);
beagleDigital P8_40("GPIO2_13",		77);
beagleDigital P8_41("GPIO2_10",		74);
beagleDigital P8_42("GPIO2_11",		75);
beagleDigital P8_43("GPIO2_8",		72);
beagleDigital P8_44("GPIO2_9",		73);
beagleDigital P8_45("GPIO2_6",		70);
beagleDigital P8_46("GPIO2_7",		71);

/*
 * P9 Header Pins
 */

beagleSerial  P9_11("UART4_RXD",	30,		"ttyO4");
beagleDigital P9_12("GPIO1_28",		60);
beagleSerial  P9_13("UART4_TXD",	31,		"ttyO4");
beagleDigital P9_14("EHRPWM1A",		50);
beagleDigital P9_15("GPIO1_16",		48);
beagleDigital P9_16("EHRPWM1B",		51);
beagleDigital P9_17("I2C1_SCL",		5);
beagleDigital P9_18("I2C1_SDA",		4);
beagleDigital P9_19("I2C2_SCL",		13);
beagleDigital P9_20("I2C2_SDA",		12);
beagleSerial  P9_21("UART2_TXD",	3,		"ttyO2");
beagleSerial  P9_22("UART2_RXD",	2,		"ttyO2");
beagleDigital P9_23("GPIO1_17",		49);
beagleSerial  P9_24("UART1_TXD",	15,		"ttyO1");
beagleDigital P9_25("GPIO3_21",		88);
beagleSerial  P9_26("UART1_RXD",	14,		"ttyO1");
beagleDigital P9_27("GPIO3_19",		86);
beagleDigital P9_28("SPI1_CS0",		84);
beagleDigital P9_29("SPI1_D0",		82);
beagleDigital P9_30("SPI1_D1",		116);
beagleDigital P9_31("SPI1_SCLK",	110);
// Pin P9_32 is VDD_ADC
beagleAnalog  P9_33("AIN4",			"ANI4");
// Pin P9_34 is GNDA_ADC
beagleAnalog  P9_35("AIN6",			"ANI6");
beagleAnalog  P9_36("AIN5",			"ANI5");
beagleAnalog  P9_37("AIN2",			"ANI2");
beagleAnalog  P9_38("AIN3",			"ANI3");
beagleAnalog  P9_39("AIN0",			"ANI0");
beagleAnalog  P9_40("AIN1",			"ANI1");
beagleDigital P9_41("CLKOUT2",		20);
beagleDigital P9_42("GPIO0_7",		7);

// I/O Header Pins
//io_pin P8_pins[46] = {
//	{"GND",			0,		POWER,				NULL,				NULL		},
//	{"GND",			0,		POWER,				NULL,				NULL		},
//	{"GPIO1_6",		38,		DIGITAL,			"gpmc_ad6",			NULL		},
//	{"GPIO1_7",		39,		DIGITAL,			"gpmc_ad7",			NULL		},
//	{"GPIO1_2",		34,		DIGITAL,			"gpmc_ad2",			NULL		},
//	{"GPIO1_3",		35,		DIGITAL,			"gpmc_ad3",			NULL		},
//	{"TIMER4",		66,		DIGITAL,			"gpmc_advn_ale",	NULL		},
//	{"TIMER7",		67,		DIGITAL,			"gpmc_oen_ren",		NULL		},
//	{"TIMER5",		69,		DIGITAL,			"gpmc_ben0_cle",	NULL		},
//	{"TIMER6",		68,		DIGITAL,			"gpmc_wen",			NULL		},
//	{"GPIO1_13",	45,		DIGITAL,			"gpmc_ad13",		NULL		},
//	{"GPIO1_12",	44,		DIGITAL,			"gpmc_ad12",		NULL		},
//	{"EHRPWM2B",	23,		DIGITAL,			"gpmc_ad9",			NULL		},
//	{"GPIO0_26",	26,		DIGITAL,			"gpmc_ad10",		NULL		},
//	{"GPIO1_15",	47,		DIGITAL,			"gpmc_ad15",		NULL		},
//	{"GPIO1_14",	46,		DIGITAL,			"gpmc_ad14",		NULL		},
//	{"GPIO0_27",	27,		DIGITAL,			"gpmc_ad11",		NULL		},
//	{"GPIO2_1",		65,		DIGITAL,			"gpmc_clk",			NULL		},
//	{"EHRPWM2A",	22,		DIGITAL,			"gpmc_ad8",			NULL		},
//	{"GPIO1_31",	63,		DIGITAL,			"gpmc_csn2",		NULL		},
//	{"GPIO1_30",	62,		DIGITAL,			"gpmc_csn1",		NULL		},
//	{"GPIO1_5",		37,		DIGITAL,			"gpmc_ad5",			NULL		},
//	{"GPIO1_4",		36,		DIGITAL,			"gpmc_ad4",			NULL		},
//	{"GPIO1_1",		33,		DIGITAL,			"gpmc_ad1",			NULL		},
//	{"GPIO1_0",		32,		DIGITAL,			"gpmc_ad0",			NULL		},
//	{"GPIO1_29",	61,		DIGITAL,			"gpmc_csn0",		NULL		},
//	{"GPIO2_22",	86,		DIGITAL,			"lcd_vsync",		NULL		},
//	{"GPIO2_24",	88,		DIGITAL,			"lcd_pclk",			NULL		},
//	{"GPIO2_23",	87,		DIGITAL,			"lcd_hsync",		NULL		},
//	{"GPIO2_25",	89,		DIGITAL,			"lcd_ac_bias_en",	NULL		},
//	{"UART5_CTSN",	10,		DIGITAL,			"lcd_data14",		NULL		},
//	{"UART5_RTSN",	11,		DIGITAL,			"lcd_data15",		NULL		},
//	{"UART4_RTSN",	9,		DIGITAL,			"lcd_data13",		NULL		},
//	{"UART3_RTSN",	81,		DIGITAL,			"lcd_data11",		NULL		},
//	{"UART4_CTSN",	8,		DIGITAL,			"lcd_data12",		NULL		},
//	{"UART3_CTSN",	80,		DIGITAL,			"lcd_data10",		NULL		},
//	{"UART5_TXD",	78,		DIGITAL | SERIAL,	"lcd_data8",		"ttyO5"		},
//	{"UART5_RXD",	79,		DIGITAL | SERIAL,	"lcd_data9",		"ttyO5"		},
//	{"GPIO2_12",	76,		DIGITAL,			"lcd_data6",		NULL		},
//	{"GPIO2_13",	77,		DIGITAL,			"lcd_data7",		NULL		},
//	{"GPIO2_10",	74,		DIGITAL,			"lcd_data4",		NULL		},
//	{"GPIO2_11",	75,		DIGITAL,			"lcd_data5",		NULL		},
//	{"GPIO2_8",		72,		DIGITAL,			"lcd_data2",		NULL		},
//	{"GPIO2_9",		73,		DIGITAL,			"lcd_data3",		NULL		},
//	{"GPIO2_6",		70,		DIGITAL,			"lcd_data0",		NULL		},
//	{"GPIO2_7",		71,		DIGITAL,			"lcd_data1",		NULL		}};
//
//io_pin P9_pins[46] = {
//	{"GND",			0,		POWER,				NULL,				NULL		},
//	{"GND",			0,		POWER,				NULL,				NULL		},
//	{"VDD_3V3EXP",	0,		POWER,				NULL,				NULL		},
//	{"VDD_3V3EXP",	0,		POWER,				NULL,				NULL		},
//	{"VDD_5V",		0,		POWER,				NULL,				NULL		},
//	{"VDD_5V",		0,		POWER,				NULL,				NULL		},
//	{"SYS_5V",		0,		POWER,				NULL,				NULL		},
//	{"SYS_5V",		0,		POWER,				NULL,				NULL		},
//	{"PWR_BUT",		0,		SYSTEM,				NULL,				NULL		},
//	{"SYS_RESETn",	0,		SYSTEM,				NULL,				NULL		},
//	{"UART4_RXD",	30,		DIGITAL | SERIAL,	"gpmc_wait0",		"ttyO4"		},
//	{"GPIO1_28",	60,		DIGITAL,			"gpmc_ben1",		NULL		},
//	{"UART4_TXD",	31,		DIGITAL | SERIAL,	"gpmc_wpn",			"ttyO4"		},
//	{"EHRPWM1A",	50,		DIGITAL | PWM,		"gpmc_a2",			"ehrpwm.1:0"},
//	{"GPIO1_16",	48,		DIGITAL,			"gpmc_a0",			NULL		},
//	{"EHRPWM1B",	51,		DIGITAL | PWM,		"gpmc_a3",			"ehrpwm.1:1"},
//	{"I2C1_SCL",	5,		DIGITAL,			"spi0_cs0",			NULL		},
//	{"I2C1_SDA",	4,		DIGITAL,			"spi0_d1",			NULL		},
//	{"I2C2_SCL",	13,		DIGITAL,			"uart1_rtsn",		NULL		},
//	{"I2C2_SDA",	12,		DIGITAL,			"uart1_ctsn",		NULL		},
//	{"UART2_TXD",	3,		DIGITAL | SERIAL,	"spi0_d0",			"ttyO2"		},
//	{"UART2_RXD",	2,		DIGITAL | SERIAL,	"spi0_sclk",		"ttyO2"		},
//	{"GPIO1_17",	49,		DIGITAL,			"gpmc_a1",			NULL		},
//	{"UART1_TXD",	15,		DIGITAL | SERIAL,	"uart1_txd",		"ttyO1"		},
//	{"GPIO3_21",	88,		DIGITAL,			"mcasp0_ahclkx",	NULL		},
//	{"UART1_RXD",	14,		DIGITAL | SERIAL,	"uart1_rxd",		"ttyO1"		},
//	{"GPIO3_19",	86,		DIGITAL,			"mcasp0_fsr",		NULL		},
//	{"SPI1_CS0",	84,		DIGITAL,			"mcasp0_ahclkr",	NULL		},
//	{"SPI1_D0",		82,		DIGITAL,			"mcasp0_fsx",		NULL		},
//	{"SPI1_D1",		116,	DIGITAL,			"mscasp0_axr0", 	NULL		},
//	{"SPI1_SCLK",	110,	DIGITAL,			"mcasp0_aclkx",		NULL		},
//	{"VDD_ADC",		0,		POWER,				NULL,				NULL		},
//	{"AIN4",		0,		ANALOG,				NULL, 				"ani5"		},
//	{"GNDA_ADC",	0,		POWER,				NULL,				NULL		},
//	{"AIN6",		0,		ANALOG,				NULL, 				"ani7"		},
//	{"AIN5",		0,		ANALOG,				NULL, 				"ani6"		},
//	{"AIN2",		0,		ANALOG,				NULL, 				"ani3"		},
//	{"AIN3",		0,		ANALOG,				NULL, 				"ani4"		},
//	{"AIN0",		0,		ANALOG,				NULL, 				"ani1"		},
//	{"AIN1",		0,		ANALOG,				NULL, 				"ani2"		},
//	{"CLKOUT2",		20,		DIGITAL,			"xdma_event_intr1",	NULL		},
//	{"GPIO0_7",		7,		DIGITAL,			"ecap0_in_pwm0_out",NULL		},
//	{"GND",			0,		POWER,				NULL,				NULL		},
//	{"GND",			0,		POWER,				NULL,				NULL		},
//	{"GND",			0,		POWER,				NULL,				NULL		},
//	{"GND",			0,		POWER,				NULL,				NULL		}};

// BeagleIO objects for P8 & P9 connectors
//beagleGPIO P8(P8_pins, 46);
//beagleGPIO P9(P9_pins, 46);

// BeagleIO objects for UARTs
//beagleSerial serial1("/dev/ttyO1");
//beagleSerial serial2("/dev/ttyO2");
//beagleSerial serial4("/dev/ttyO4");
//beagleSerial serial5("/dev/ttyO5");

