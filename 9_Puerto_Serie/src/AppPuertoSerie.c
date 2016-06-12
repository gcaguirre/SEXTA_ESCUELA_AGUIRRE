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
//#include "string.h"
#include "AppPuertoSerie.h"       /* <= own header */
#include "led.h"
#include "interrupcion.h"
#include "teclas.h"
#include "dac.h"
#include "adquisicion.h"
#include "puerto_serie.h"
/*==================[macros and definitions]=================================*/
#define NRO_MAX  35000000
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
int nro_led=PURO_ROJO; //determina el led a prender


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
   /* perform the needed initialization here */
      uint64_t j;
	  uint8_t size = 28;
	  uint8_t i = 0;
//	  uint8_t data = 0;
	  uint8_t tecla=0;
	  char message[] = "Follow the white rabbit...\n\r";


	DriverInicializaLed();
	DriverInicializaInterrupcion();
	DriverInicializaTeclas();
	DriverInicializaDac();
	DriverPeriodoInterrupcion(500);
	DriverInicializaUART();
	while(1)
	{
		tecla=DriverLeeTeclado();
		switch(tecla)
		{
		case 'r': // se precionó la tecla r
			i=0;
			ApagaLeds();
			DriverEnciendeLed(PURO_ROJO);
			nro_led=PURO_ROJO;
			break;
		case 'v': // se precionó la tecla v
			i=0;
			ApagaLeds();
			DriverEnciendeLed(PURO_VERDE);
			nro_led=PURO_VERDE;
			break;
		case 'a': // se precionó la tecla a
			i=0;
			ApagaLeds();
			DriverEnciendeLed(PURO_AMARILLO);
			nro_led=PURO_AMARILLO;
			break;
		default:
			break;
		} // end case


//		while(tecla==DriverLeeTeclado());
/*		if(tecla!=0)
		{
			ApagaLeds();
		}
*/

		//Envia el mensaje byte por byte
		 while((DriverEstadoTeclado() != 0) && (i < size))
	      {
	         /* send first byte */
			 DriverEnviaByte(message[i]);
//	         Chip_UART_SendByte((LPC_USART_T *)LPC_USART2, message[i]);
	         /* bytes written */

	         /*delay*/
	         for (j=0;j<500000;j++);
	         i++;
	      } //end while(((Chip_UART_ReadLineStatus((

	}// end while(1)
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

