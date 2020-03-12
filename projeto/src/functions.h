/*
 * functions.h
 *
 * Created: 12/03/2020 11:40:36
 *  Author: mathe
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

/*********************************************/
/* Configurações LEDS 1 a 3                  */
#define LED1_PIO PIOC
#define LED1_PIO_ID ID_PIOC
#define LED1_PIO_IDX 19
#define LED1_PIO_IDX_MASK (1 << LED1_PIO_IDX)

#define LED2_PIO PIOD
#define LED2_PIO_ID ID_PIOD
#define LED2_PIO_IDX 26
#define LED2_PIO_IDX_MASK (1 << LED2_PIO_IDX)

#define LED3_PIO PIOD
#define LED3_PIO_ID ID_PIOD
#define LED3_PIO_IDX 11
#define LED3_PIO_IDX_MASK (1 << LED3_PIO_IDX)
/********************************************/

// Configuracoes do botao1
#define BUT1_PIO PIOA
#define BUT1_PIO_ID ID_PIOA
#define BUT1_PIO_IDX 2
#define BUT1_PIO_IDX_MASK (1u << BUT1_PIO_IDX)

// Configuracoes do botao2
#define BUT2_PIO PIOD
#define BUT2_PIO_ID ID_PIOD
#define BUT2_PIO_IDX 30
#define BUT2_PIO_IDX_MASK (1u << BUT2_PIO_IDX)

// Configuracoes do botao3
#define BUT3_PIO PIOC
#define BUT3_PIO_ID ID_PIOC
#define BUT3_PIO_IDX 13
#define BUT3_PIO_IDX_MASK (1u << BUT3_PIO_IDX)

//Configurações buzzer
#define BUZZER_PIO PIOA
#define BUZZER_PIO_ID ID_PIOA
#define BUZZER_PIO_IDX 13
#define BUZZER_PIO_IDX_MASK (1 << BUZZER_PIO_IDX)

/***********/
/*Prototype*/
/***********/
void pause(void);
void sing(int freq[], int tempo[], int size);
void init(void);

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

		int delay = 1000000 / freq[note];

		pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);

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

#endif /* FUNCTIONS_H_ */