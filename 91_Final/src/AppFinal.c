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
#include "AppFinal.h"       /* <= own header */
#include "led.h"
#include "interrupcion.h"
#include "teclas.h"
#include "dac.h" //Uso los tres drivers de Mariela
#include "adc.h"
#include "uart.h"
/*==================[macros and definitions]=================================*/
#define NRO_MAX  35000000
#define DO	31 //revisar el offset
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
uint32_t dac_value; //valor a sacar por el dac
int nro_muestra; //muestra actual
float ganancia=1,offset=0;
int nro_led=5; //determina el led a prender
uint32_t valor_periodo; //determina el periodo del parpadeo
int next_led=0; // determina si enciende el led a la der(1) o a la izq(-1)
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
	IniciaDAC();  // Mariela
	IniciaADC();  // Mariela
	IniciaUART();  // Mariela
//	DriverInicializaDac();
	DriverPeriodoInterrupcion(10); // en ms
	while(1)
	{
		uint8_t tecla=0;
		tecla=DriverPresionadaTecla();
		switch(tecla)
		{
		case 1: // Aumenta la ganancia
			DriverEnciendeLed(AZUL);
			nro_led=AZUL;
			ganancia=ganancia+0.1;
			if(ganancia>1.2)
				ganancia=1.2;
			break;
		case 2: // Disminuye la ganancia
			DriverEnciendeLed(PURO_AMARILLO);
			nro_led=PURO_AMARILLO;
			ganancia=ganancia-0.1;
			if(ganancia<0.8)
				ganancia=0.8;
			break;
		case 3: // Aumenta el offset
			DriverEnciendeLed(PURO_ROJO);
			nro_led=PURO_ROJO;
			offset=offset+DO; //revisar Delta offset
			if(offset>1023)
				offset=1023;
			break;
		case 4: // Disminuye el offset
			DriverEnciendeLed(PURO_VERDE);
			nro_led=PURO_VERDE;
			offset=offset-DO;
			if(offset<-1023)
				offset=1023;
			break;
		default:
			break;
		} // end case
		while(tecla==DriverPresionadaTecla());
		if(tecla!=0)
		{
			ApagaLeds();
		}
	}// end while(1)
}

void envia_terminal(char *cadena) //saca una cadena por la terminal
{
	while()//recorre la cadena sacando de a un byte
	{

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
	nro_muestra++;

	//envía señal analógica
	EscribeDAC(dac_value);

	//leo entrada
	entrada_adc=LeeADC();//unit16_t

	//adapto según teclas y transformo
	//  el valor leído se multiplica por la ganacia
	//y se le suma el offser para determinar el valor a sacar

	transformada=entrada_dac*ganancia+offset

	//controla los límites
	if(transformada>maximo)
		maximo=transformada;
	if(transformada<minimo)
		minimo=transformada;

	//cada un segundo saco la lectura transformada
	if(nro_muestra % 100==0)
	{
		DriverCambiaLed(nro_led); //muestra que está con vida

		//tranformo la info a cadenas
		sprintf(s_ganacia, "%d", ganancia); //función de C que transforma nros a cadenas
		sprintf(s_offset, "%d", offset);
		sprintf(s_maximo, "%d", maximo);
		sprintf(s_minimo, "%d", minimo);

		//armo cadenas con carteles e información
		sal_ganancia="Ganancia:.."+s_ganancia;  //transformo la ganacia a string
		sal_offset="Offset.."+s_offset;   //transformo el offset a string
		sal_maximo="Maximo:.."+s_maximo;   //transformo el maximo a string
		sal_minimo="Minimo:.."+s_minimo;   //transformo el minimo a string

		//manda a la PC la info
		envia_terminal(sal_ganancia);	//saco ganancia actual
		envia_terminal(sal_offset);	//saco offset actual
		envia_terminal(sal_maximo);	//saco máximo del último segundo
		envia_terminal(sal_minimo);	//saco mínimo del último segundo
	}



	DriverLimpiaInt();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

