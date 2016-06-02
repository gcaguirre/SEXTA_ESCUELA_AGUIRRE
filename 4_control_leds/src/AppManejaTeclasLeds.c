/* Copyright 2016, XXXXXX
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

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
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
#include "AppManejaTeclasLeds.h"       /* <= own header */
#include "led.h"
#include "interrupcion.h"
#include "teclas.h"
/*==================[macros and definitions]=================================*/
#define NRO_MAX  35000000
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

int nro_led=5; //determina el led a prender
uint32_t valor_periodo; //determina el periodo del parpadeo
int next_led=0; // deternina si enciende el led a la der(1) o a la izq(-1)
int next_periodo=0; // determina si aumenta el periodo o si lo disminuye


/*==================[internal functions definition]==========================*/

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



int main(void)
{
//	uint32_t i;
   /* perform the needed initialization here */
	DriverInicializaLed();
	DriverInicializaInterrupcion();
	DriverInicializaTeclas();
	DriverPeriodoInterrupcion(200);
	ApagaLeds();
	while(1)
	{
		int i;
		uint8_t tecla=0;
		tecla=DriverPresionadaTecla();
		switch(tecla)
		{
		case 1:
			nro_led--;
			if(nro_led<0)
				nro_led=5;
			break;
		case 2:
			nro_led++;
			if(nro_led>5)
				nro_led=0;
			break;
		case 3:
			valor_periodo=valor_periodo-10;
			if(valor_periodo<50)
				valor_periodo=50;
			DriverPeriodoInterrupcion(valor_periodo);
			break;
		case 4:
			valor_periodo=valor_periodo+10;
			if(valor_periodo>530)
				valor_periodo=530;
			DriverPeriodoInterrupcion(valor_periodo);
			break;
		default:
			break;
		} // end case
		if(tecla!=0)
		{
			ApagaLeds();
		}
		while(tecla==DriverPresionadaTecla());
//		for(i=1;i<50000;i++);
	}
}
void ApagaLeds(void)
{
	DriverApagaLed(0);
	DriverApagaLed(1);
	DriverApagaLed(2);
	DriverApagaLed(3);
	DriverApagaLed(4);
	DriverApagaLed(5);
//	DriverEnciendeLed(5);
}
void ISR_RIT(void)
{
	DriverCambiaLed(nro_led);
	DriverLimpiaInt();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

