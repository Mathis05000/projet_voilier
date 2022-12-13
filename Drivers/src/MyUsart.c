#include "stm32f10x.h"
#include <string.h>

//  9600 Bd

void myUsartInit(USART_TypeDef * usart) {
	usart->BRR |= 468 << 4; // Fixe le baud rate à 9600bps
	usart->BRR |= 75; // Fixe le baud rate à 9600bps
	usart->CR1 |= USART_CR1_UE; // Activation de l'USART
	usart->CR1 &= ~USART_CR1_M; // Choix d'une taille de 8 bits de données
	usart->CR2 &= USART_CR2_STOP; // Choix d'un seul bit de stop
	usart->CR1 |= USART_CR1_TE; // Envoi de la première trame d'attente
	usart->CR1 |= USART_CR1_RE;
	
}

void myUsartWrite(USART_TypeDef * usart, char s) {

	while (!(usart->SR & USART_SR_TXE));
	usart->DR = s;
	
	//usart->DR |= s;
	//while(!(usart->SR & USART_SR_TC)) {} // Attente de la fin de transmission
}



