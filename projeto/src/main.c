#include "asf.h"
#include "musicas.h"
#include "functions.h"

#define maxMus 500

typedef struct
{
	int notes[maxMus];
	int tempo[maxMus];
} Musica;

// Função de inicialização do uC
void init(void)
{
	sysclk_init();

	WDT->WDT_MR = WDT_MR_WDDIS;

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
	for (unsigned int i = 0; i < sizeof(pirate_notes) / sizeof(pirate_notes[0]); i++)
	{
		piratas.notes[i] = pirate_notes[i];
		piratas.tempo[i] = pirate_tempo[i];
	}

	Musica mario;
	for (unsigned int i = 0; i < sizeof(mario_theme_notes) / sizeof(mario_theme_notes[0]); i++)
	{
		mario.notes[i] = mario_theme_notes[i];
		mario.tempo[i] = mario_theme_tempo[i];
	}

	Musica underworld;
	for (unsigned int i = 0; i < sizeof(underworld_melody) / sizeof(underworld_melody[0]); i++)
	{
		underworld.notes[i] = underworld_melody[i];
		underworld.tempo[i] = underworld_tempo[i];
	}

	// Musica darth;
	// for (int i = 0; i < sizeof(imperial_march_notes) / sizeof(imperial_march_notes[0]); i++)
	// {
	// 	darth.notes[i] = imperial_march_notes[i];
	// 	darth.tempo[i] = imperial_march_tempo[i];
	// }

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
				sing(underworld.notes, underworld.tempo, sizeof(underworld.notes) / sizeof(underworld.notes[0]));
				break;

			case (3):
				sing(imperial_march_notes, imperial_march_tempo, sizeof(imperial_march_notes) / sizeof(imperial_march_notes[0]));
				break;

			default:
				sing(piratas.notes, piratas.tempo, sizeof(piratas.notes) / sizeof(piratas.notes[0]));
				break;
			}
		}
	}
	return 0;
}