/*
 * function.c
 *
 * Created: 23/03/2020 17:09:48
 *  Author: mathe
 */ 

#include "functions.h"


void pause()
{
	delay_s(1);
	while (pio_get(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK))
	{
	}
}

/************************************************************************************************************************/
/* Adaptado de                                                                                                          */
/* https://create.arduino.cc/projecthub/jrance/super-mario-theme-song-w-piezo-buzzer-and-arduino-1cc2e4                 */
/* https://www.tutorialspoint.com/arduino/arduino_tone_library.htm                                                      */
/* https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Tone.cpp                                        */
/************************************************************************************************************************/
void sing(int freq[], int tempo[], int size)
{
	//NECESSÁRIO AJUSTAR ALGUMAS DAS CONTAS PARA MELHORES RESULTADOS
	for (int note = 0; note < size; note++)
	{
		if (!pio_get(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK))
		{
			pause();
		}

		// 1000000 microsegundos = 1 segundo 
		// multiplicado por 1/frequência equivale ao tempo que a nota tem que ser tocada
		int delay = 1000000 / freq[note];

		pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);

		// 1000 => para ser microsegundos
		for (int i = 0; i < 1000 * tempo[note] / delay; i++)
		{
			pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
			delay_us(delay / 2);
			pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
			delay_us(delay / 2);
		}
		pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
		delay_us(tempo[note] * 1100); //velocidade entre cada nota
	}
}