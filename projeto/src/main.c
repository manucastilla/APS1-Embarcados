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

//Configurações buzzer
#define BUZZER_PIO PIOA
#define BUZZER_PIO_ID ID_PIOA
#define BUZZER_PIO_IDX 13
#define BUZZER_PIO_IDX_MASK (1 << BUZZER_PIO_IDX)

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

	//Inicialização LEDs
	pmc_enable_periph_clk(LED_PIO_ID);
	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);

	pmc_enable_periph_clk(LED1_PIO_ID);
	pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 0, 0, 0);

	pmc_enable_periph_clk(LED2_PIO_ID);
	pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 0, 0, 0);

	pmc_enable_periph_clk(LED3_PIO_ID);
	pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 0, 0, 0);

	WDT->WDT_MR = WDT_MR_WDDIS;

	// Inicialização Buttons
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pio_set_input(BUT1_PIO, BUT1_PIO_IDX_MASK, PIO_PULLUP);

	pmc_enable_periph_clk(BUT2_PIO_ID);
	pio_set_input(BUT2_PIO, BUT2_PIO_IDX_MASK, PIO_PULLUP);

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
	while (1)
	{
		status = pio_get(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK);
		btn1 = pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK);

		if (musica_atual > 4)
		{
			musica_atual = 0;
		}

		if (!btn1)
		{
			musica_atual++;
			for (int i = 0; i < musica_atual; i++)
			{
				pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
				delay_s(0.1);
				pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
				delay_s(0.1);
			}
		}

		if (!status)
		{
			switch (musica_atual)
			{
			case (1):
				sing(mario_theme_notes, mario_theme_tempo, sizeof(mario_theme_notes) / sizeof(mario_theme_notes[0]));
				break;

			case (2):
				sing(imperial_march_notes, imperial_march_tempo, sizeof(imperial_march_notes) / sizeof(imperial_march_notes[0]));
				break;

			case (3):
				sing(underworld_melody, underworld_tempo, sizeof(underworld_melody / sizeof(underworld_melody[0])));
				break;

			default:
				sing(pirate_notes, pirate_tempo, sizeof(pirate_notes) / sizeof(pirate_notes[0]));
				break;
			}
		}
	}
	return 0;
}