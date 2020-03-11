#include "asf.h"
#include "musicas.h"

// Configuração LED da placa
#define LED_PIO PIOC
#define LED_PIO_ID 12
#define LED_PIO_IDX 8
#define LED_PIO_IDX_MASK (1 << LED_PIO_IDX)

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

// Configuracoes do botao3
#define BUT_PIO PIOA
#define BUT_PIO_ID ID_PIOA
#define BUT_PIO_IDX 11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)

//Configurações buzzer
#define BUZZER_PIO PIOA
#define BUZZER_PIO_ID ID_PIOA
#define BUZZER_PIO_IDX 13
#define BUZZER_PIO_IDX_MASK (1 << BUZZER_PIO_IDX)

#define max 500


void pause();
void sing(int freq[], int tempo[], int size);
void init();

	
typedef struct{
	int notes[max];
	int tempo[max];
}Musica;
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

// Função de inicialização do uC
void init(void)
{
	sysclk_init();

	WDT->WDT_MR = WDT_MR_WDDIS;

	//Inicialização LEDs
	pmc_enable_periph_clk(LED_PIO_ID);
	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);

	pmc_enable_periph_clk(LED1_PIO_ID);
	pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 0, 0, 0);

	pmc_enable_periph_clk(LED2_PIO_ID);
	pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 0, 0, 0);

	pmc_enable_periph_clk(LED3_PIO_ID);
	pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 0, 0, 0);

	// Inicialização Buttons
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pio_set_input(BUT1_PIO, BUT1_PIO_IDX_MASK, PIO_PULLUP);

	pmc_enable_periph_clk(BUT2_PIO_ID);
	pio_set_input(BUT2_PIO, BUT2_PIO_IDX_MASK, PIO_PULLUP);

	pmc_enable_periph_clk(BUT3_PIO_ID);
	pio_set_input(BUT3_PIO, BUT3_PIO_IDX_MASK, PIO_PULLUP);

	pmc_enable_periph_clk(BUT_PIO_ID);
	pio_set_input(BUT_PIO, BUT_PIO_IDX_MASK, PIO_PULLUP);

	// Inicialização BUZZER
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 0, 0, 0);
}

int main(void)
{
	int status;
	int btn1;

	init();
	int musica_atual = 0;

	
	Musica piratas;
	for(int i=0; i< sizeof(pirate_notes)/sizeof(pirate_notes[0]); i++){
	piratas.notes[i] = pirate_notes[i];
	piratas.tempo[i] = pirate_tempo[i];
	}
	
	Musica mario;
	for(int i=0; i< sizeof(mario_theme_notes)/sizeof(mario_theme_notes[0]); i++){
		mario.notes[i] = mario_theme_notes[i];
		mario.tempo[i] = mario_theme_tempo[i];
	}
	
	Musica underworld;
	for(int i=0; i< sizeof(underworld_melody)/sizeof(underworld_melody[0]); i++){
		underworld.notes[i] = underworld_melody[i];
		underworld.tempo[i] = underworld_tempo[i];
	}
	
	//Musica darth;
	//for(int i=0; i< sizeof(imperial_march_notes)/sizeof(imperial_march_notes[0]); i++){
		//darth.notes[i] = imperial_march_notes[i];
		//darth.tempo[i] = imperial_march_tempo[i];
//	}

	
	
	while (1)
	{
		status = pio_get(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK);
		btn1 = pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK);

		if (!btn1)
		{
			musica_atual++;
			if (musica_atual > 4)
			{
				musica_atual = 0;
			}
			for (int i = 0; i < musica_atual; i++)
			{
				pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
				delay_ms(100);
				pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
				delay_ms(100);
			}
		}

		if (!status)
		{
			switch (musica_atual)
			{
			case (1):
				sing(mario.notes, mario.tempo, sizeof(mario.notes) / sizeof(mario.notes[0]));
				break;

			case (2):
				sing(imperial_march_notes, imperial_march_tempo, sizeof(imperial_march_notes) / sizeof(imperial_march_notes[0]));
				break;

			case (3):
				sing(underworld.notes, underworld.tempo, sizeof(underworld.notes) / sizeof(underworld.notes[0]));
				break;

			default:
				sing(piratas.notes, piratas.tempo, sizeof(piratas.notes) / sizeof(piratas.notes[0]));
				break;
			}
		}
	}
	return 0;
}