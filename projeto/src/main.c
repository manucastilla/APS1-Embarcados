#include "asf.h"
#include "musicas.h"
#include "functions.h"

/***********/
/*Prototype*/
/***********/
void pause(void);
void sing(int freq[], int tempo[], int size);
void init(void);

volatile char but1_flag;
volatile char but2_flag;
volatile char but3_flag;

void but1_callback(void);
void but2_callback(void);
void but3_callback(void);

/**********/
/*Callback*/
/**********/

volatile char but1_flag = 0;
void but1_callback(void){
	but1_flag = 1;
}

volatile char but2_flag = 0;
void but2_callback(void){
	but2_flag = 1;
}

volatile char but3_flag = 0;
void but3_callback(void){
	but3_flag = 1;
}

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
	pio_configure(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK, PIO_PULLUP);
	
	pio_handler_set(BUT1_PIO, BUT1_PIO_ID, BUT1_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but1_callback);
	pio_enable_interrupt(BUT1_PIO, BUT1_PIO_IDX_MASK);
	NVIC_EnableIRQ(BUT1_PIO_ID);
	NVIC_SetPriority(BUT1_PIO_ID, BUT1_priority);

	pmc_enable_periph_clk(BUT2_PIO_ID);
	pio_configure(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK, PIO_PULLUP);

	pio_handler_set(BUT2_PIO, BUT2_PIO_ID, BUT2_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but2_callback);
	pio_enable_interrupt(BUT2_PIO, BUT2_PIO_IDX_MASK);
	NVIC_EnableIRQ(BUT2_PIO_ID);
	NVIC_SetPriority(BUT2_PIO_ID, BUT2_priority);

	pmc_enable_periph_clk(BUT3_PIO_ID);
	pio_set_input(BUT3_PIO, BUT3_PIO_IDX_MASK, PIO_PULLUP);
	
	pio_handler_set(BUT3_PIO, BUT3_PIO_ID, BUT3_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but3_callback);
	pio_enable_interrupt(BUT3_PIO, BUT3_PIO_IDX_MASK);
	NVIC_EnableIRQ(BUT3_PIO_ID);
	NVIC_SetPriority(BUT3_PIO_ID, BUT3_priority);

	// Inicialização BUZZER
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 0, 0, 0);
}

void music_setup_notes(Musica* musica, int notas[maxMus], int tempo[maxMus], int notas_size) {
	for (unsigned int i = 0; i < notas_size; i++)
	{
		musica->notes[i] = notas[i];
		musica->tempo[i] = tempo[i];
	}
}

int main(void)
{
	sysclk_init();
	WDT->WDT_MR = WDT_MR_WDDIS;

	init();
	delay_ms(200);
	but1_flag = 0;
	but2_flag = 0;
	but3_flag = 0;
	int musica_atual = 0;

	Musica piratas, mario, underworld;
	music_setup_notes(&piratas, pirate_notes, pirate_tempo, sizeof(pirate_notes) / sizeof(pirate_notes[0]));

	music_setup_notes(&mario, mario_theme_notes, mario_theme_tempo, sizeof(mario_theme_notes) / sizeof(mario_theme_notes[0]));

	music_setup_notes(&underworld, underworld_melody, underworld_tempo, sizeof(underworld_melody) / sizeof(underworld_melody[0]));

	while (1)
	{	
		pmc_sleep(SAM_PM_SMODE_SLEEP_WFI);
		if (but1_flag)
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
			but1_flag = 0;
		}

		if (but2_flag)
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
				sing(piratas.notes, piratas.tempo, sizeof(piratas.notes) / sizeof(piratas.notes[0]));

				break;

			default:
				sing(imperial_march_notes, imperial_march_tempo, sizeof(imperial_march_notes) / sizeof(imperial_march_notes[0]));
				break;
			
			}
			
			but2_flag=0;
		}
	}
	return 0;
}