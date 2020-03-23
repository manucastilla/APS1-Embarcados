/*
 * functions.h
 *
 * Created: 12/03/2020 11:40:36
 *  Author: mathe
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "asf.h"
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

#define maxMus 500

typedef struct
{
	int notes[maxMus];
	int tempo[maxMus];
} Musica;

/***********/
/*Prototype*/
/***********/
void pause(void);
void sing(int freq[], int tempo[], int size);
void init(void);


#endif /* FUNCTIONS_H_ */