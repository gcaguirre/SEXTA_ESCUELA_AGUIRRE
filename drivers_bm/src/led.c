/* Copyright 2016, XXXXXXXXX  
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
#include "led.h"












/*==================[macros and definitions]=================================*/
#define RGB_ROJO_PAQUETE 2
#define RGB_VERDE_PAQUETE 2
#define RGB_AZUL_PAQUETE 2
#define PURO_ROJO_PAQUETE 2
#define PURO_VERDE_PAQUETE 2
#define PURO_AMARILLO_PAQUETE 2


#define GPIO5 5
#define GPIO0 0
#define GPIO1 1

#define GPIO5_0 0
#define GPIO5_1 1
#define GPIO5_2 2
#define GPIO0_14 14
#define GPIO1_11 11
#define GPIO1_12 12

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
// Inicializa los leds
void DriverInicializaLed(void)
{
	Chip_GPIO_Init(LPC_GPIO_PORT);

	Chip_SCU_PinMux(RGB_ROJO_PAQUETE,0,MD_PUP,FUNC4);
	Chip_SCU_PinMux(RGB_VERDE_PAQUETE,1,MD_PUP,FUNC4);
	Chip_SCU_PinMux(RGB_AZUL_PAQUETE,2,MD_PUP,FUNC4);
	Chip_SCU_PinMux(PURO_AMARILLO_PAQUETE,10,MD_PUP,FUNC0);
	Chip_SCU_PinMux(PURO_ROJO_PAQUETE,11,MD_PUP,FUNC0);
	Chip_SCU_PinMux(PURO_VERDE_PAQUETE,12,MD_PUP,FUNC0);


	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO5,1<<GPIO5_0,1);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO5,1<<GPIO5_1,1);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO5,1<<GPIO5_2,1);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO0,1<<GPIO0_14,1);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO1,1<<GPIO1_11,1);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO1,1<<GPIO1_12,1);

}


// Enciende el led que se pasa como argumento
void DriverEnciendeLed(uint8_t led)
{
	switch(led)
	{
	case 0:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO5,GPIO5_0);
		break;
	case 1:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO5,GPIO5_1);
		break;
	case 2:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO5,GPIO5_2);
		break;
	case 3:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO0,GPIO0_14);
		break;
	case 4:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO1,GPIO1_11);
		break;
	case 5:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO1,GPIO1_12);
		break;
	default:
		break;
	}
}
// Apaga el led que se pasa como argumento
void DriverApagaLed(uint8_t led)
{
	switch(led)
	{
	case 0:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO5,GPIO5_0);
		break;
	case 1:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO5,GPIO5_1);
		break;
	case 2:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO5,GPIO5_2);
		break;
	case 3:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO0,GPIO0_14);
		break;
	case 4:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO1,GPIO1_11);
		break;
	case 5:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO1,GPIO1_12);
		break;
	default:
		break;
	}
}

// Cambia el estado del led que se pasa como argumento
void DriverCambiaLed(uint8_t led)
{
	switch(led)
	{
	case 0:
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO5,GPIO5_0);
		break;
	case 1:
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO5,GPIO5_1);
		break;
	case 2:
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO5,GPIO5_2);
		break;
	case 3:
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO0,GPIO0_14);
		break;
	case 4:
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO1,GPIO1_11);
		break;
	case 5:
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO1,GPIO1_12);
		break;
	default:
		break;
	}

}
/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */




/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

