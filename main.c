#include <stm32f4xx.h>


void USART2_Config()
{
	RCC -> AHB1ENR |= (1U<<0);
	RCC -> APB1ENR |= (1U<<17);
	GPIOA -> MODER |= (2U<<4)|(2U<<6);
	GPIOA -> OSPEEDR |= (3U<<4)|(3U<<6);
	GPIOA -> AFR[0] |= (7U<<8)|(7U<<12);

	USART2 -> CR1 |= (1U<<13);
	USART2 -> CR1 &= ~(1U<<12);
	USART2 -> CR1 |= (1U<<3)|(1U<<2);
	USART2 -> BRR = 0x0683;
}


void TXchar(unsigned char data)
{
	USART2 -> DR = data;
	while(!(USART2 -> SR & (1U<<7)));
}

void USART2_string(char *str)
{
	while(*str != '\0')
	{
		while(!(USART2 -> SR & (1U<<6)));
		TXchar(*str);
		str++;
	}
}

unsigned char RXchar()
{
	while(!(USART2 -> SR & (1U<<5)));
	unsigned char temp = USART2 -> DR;
	return temp;
}


int main()
{
	 USART2_Config();

	 unsigned char value;
	while(1)
	{
		value = RXchar();
		TXchar(value);
		USART2_string("");
	}
}
