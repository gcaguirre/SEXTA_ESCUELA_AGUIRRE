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

/** \brief Blinking Bare Metal driver teclas
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
#include "teclas.h"












/*==================[macros and definitions]=================================*/
#define TECLA_1_PAQUETE 1
#define TECLA_2_PAQUETE 1
#define TECLA_3_PAQUETE 1
#define TECLA_4_PAQUETE 1


#define GPIO0 0
#define GPIO1 1

#define GPIO0_4 4
#define GPIO0_8 8
#define GPIO0_9 9
#define GPIO1_9 9

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
// Inicializa las teclas
void DriverInicializaTeclas(void)
{
	Chip_GPIO_Init(LPC_GPIO_PORT);

	Chip_SCU_PinMux(TECLA_1_PAQUETE,0,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_SCU_PinMux(TECLA_2_PAQUETE,1,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_SCU_PinMux(TECLA_3_PAQUETE,2,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_SCU_PinMux(TECLA_4_PAQUETE,6,MD_PUP|MD_EZI|MD_ZI,FUNC0);

	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO0,1<<GPIO0_4,0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO0,1<<GPIO0_8,0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO0,1<<GPIO0_9,0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO1,1<<GPIO1_9,0);
}


//Detecta la tecla presionada
 uint8_t DriverPresionadaTecla(void)
{
	uint8_t tecla=0;
	if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO0,GPIO0_4))
		tecla=1;
	if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO0,GPIO0_8))
		tecla=2;
	if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO0,GPIO0_9))
		tecla=3;
	if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO1,GPIO1_9))
		tecla=4;
	return tecla;
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

