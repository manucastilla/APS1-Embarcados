/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************/
/* includes                                                             */
/************************/

#include "asf.h"
#include "musicas.h"

/************************/
/* defines                                                              */
/************************/

#define LED_PIO				PIOC
#define LED_PIO_ID			12
#define LED_PIO_IDX			8
#define LED_PIO_IDX_MASK		(1<< LED_PIO_IDX)


// Configuracoes do botao
#define BUT_PIO				PIOA
#define BUT_PIO_ID			10
#define BUT_PIO_IDX			11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)

// Configuracoes do botao
#define BUT2_PIO				PIOD
#define BUT2_PIO_ID			ID_PIOD
#define BUT2_PIO_IDX			30
#define BUT2_PIO_IDX_MASK (1u << BUT2_PIO_IDX)

#define BUZZER_PIO				PIOA
#define BUZZER_PIO_ID			ID_PIOA
#define BUZZER_PIO_IDX			13
#define BUZZER_PIO_IDX_MASK		(1<< BUZZER_PIO_IDX)

/************************/
/* constants                                                            */
/************************/

/************************/
/* variaveis globais                                                    */
/************************/

/************************/
/* prototypes                                                           */
/************************/

void init(void);


/************************/
/* interrupcoes                                                         */
/************************/

/************************/
/* funções */                               
/************************/

// Função de inicialização do uC
void init(void){
// Initialize the board clock
sysclk_init();

//Inicializa PC8 como saída
pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);

// Desativa WatchDog Timer
WDT->WDT_MR = WDT_MR_WDDIS;

// Inicializa PIO do botao
pmc_enable_periph_clk(BUT_PIO_ID);

// configura pino ligado ao botão como entrada com um pull-up.
pio_set_input(BUT_PIO,BUT_PIO_IDX_MASK, PIO_DEFAULT);

// resistor alimenta o VCC
 pio_pull_up(BUT_PIO, BUT_PIO_IDX_MASK, 1);
// Ativa o PIO na qual o LED foi conectado
// para que possamos controlar o LED.
pmc_enable_periph_clk(LED_PIO_ID);

// Inicializa PIO do botao
pmc_enable_periph_clk(BUT2_PIO_ID);
pio_set_input(BUT2_PIO, BUT2_PIO_IDX_MASK, PIO_PULLUP);

pmc_enable_periph_clk(BUZZER_PIO_ID);
pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 0, 0, 0);

}

/************************/
/* Main                                                                 */
/************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
int status;
  init();
int i=0;
  // super loop
  // aplicacoes embarcadas não devem sair do while(1).
  while (1)
  {
	  status = pio_get(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK);
	  
	  if (status == 0){
		  // iterate over the notes of the melody:
		  int size = sizeof(pirate_notes)/sizeof(pirate_notes[0]);
		  for (int nota = 0; nota < size; nota++) {
			  for(int i=0; i<pirate_tempo[nota]; i++){
				  //double delay = 1000000.0*(double)pirate_notes[nota]/2.0;
				  pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
				  delay_us(1000000/pirate_notes[nota]/2);
				  pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
				  delay_us(1000000/pirate_notes[nota]/2);
			  }
			  
		  }
	  }
  }
  return 0;
}