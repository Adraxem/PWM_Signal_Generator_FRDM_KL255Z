/* p7_1.c: A to D conversion of channel 0
* This program converts the analog input from channel 0 (PTE20)
* using software trigger continuously.
* Bits 10-8 are used to control the tri-color LEDs. LED code is
* copied from p2_7. Connect a potentiometer between 3.3V and
* ground. The wiper of the potentiometer is connected to PTE20.
* When the potentiometer is turned, the LEDs should change color.
*/
#include <MKL25Z4.h>
#include <math.h>
#define PI 3.1415
#define MASK(x) (1UL << (x))
#ifndef GPIO_DEFS_H
#define GPIO_DEFS_H

#define DBG_ISR_POS (0)
#define DBG_MAIN_POS (1)

#define DEBUG_PORT PTB

#endif
#define SW_POS (1)


void ADC0_init(void);
void LED_set(int s);
void pin_init(void);

void timedel_timer (double timdel);
void delayMs(int n);
volatile unsigned int result;
void init_switch(void);
void PORTA_IRQHandler(void);
volatile unsigned int direction;  /* 0 = to right, 1 = to left*/

int main (void)
{
	
	
	direction = 0;
	double doub_result;
	double mapped_res;
	
	
	__enable_irq();
	init_switch();
	pin_init(); /* Configure LEDs */
	ADC0_init(); /* Configure ADC0 */
	PTD->PDOR = 0x00000000;
while (1) {		
		ADC0->SC1[0] = 0; /* start conversion on channel 0 */
		
		result = ADC0->R[0]; /* read conversion result and clear COCO flag */
		
		


	while(!(ADC0->SC1[0] & 0x80)) {}
doub_result  = result/4095.0;
		mapped_res = (doub_result*(295.0));
			/* wait for conversion complete */
		
		if (direction == 0){
		
		PTD->PTOR = MASK(0);
		
	timedel_timer (mapped_res);
		
		PTD->PTOR = MASK(1);
			timedel_timer (mapped_res);
		
		PTD->PTOR = MASK(2);
			timedel_timer (mapped_res);
		
		PTD->PTOR = MASK(3);
		
			timedel_timer (mapped_res);
		
		PTD->PTOR = MASK(4);
		
		timedel_timer (mapped_res);
		
		PTD->PTOR = MASK(6);
		
			timedel_timer (1638-5*mapped_res);
			/*if (result <=1365.0){
			PTB->PSOR = MASK(2);
				PTB->PCOR |= (~MASK(2));
			}
			else if ((1365.0<result)&(result<2730.0)){
			PTB->PSOR = MASK(1);
				PTB->PCOR |= (~MASK(1));
			}
			else if ((2730.0<result)&(result<4095.0)){
			PTB->PSOR = MASK(8);
				PTB->PCOR |= (~MASK(8));
			}*/
		} else if (direction == 1){
		PTD->PTOR = MASK(6);
		
	timedel_timer (mapped_res);
		
		PTD->PTOR = MASK(4);
			timedel_timer (mapped_res);
		
		PTD->PTOR = MASK(3);
			timedel_timer (mapped_res);
		
		PTD->PTOR = MASK(2);
		
			timedel_timer (mapped_res);
		
		PTD->PTOR = MASK(1);
		
		timedel_timer (mapped_res);
		
		PTD->PTOR = MASK(0);
		
			timedel_timer (1638-5*mapped_res);
					/*	if (result <=1365.0){
			PTB->PSOR = MASK(2);
			PTB->PCOR |= (~MASK(2));	
			}
			else if ((1365.0<result)&(result<2730.0)){
			PTB->PSOR = MASK(3);
				PTB->PCOR |= (~MASK(3));
			}
			else if ((2730.0<result)&(result<4095.0)){
			PTC->PSOR = MASK(2);
				PTC->PCOR |= (~MASK(2));
			}*/
		}
		

	}
}

/*double timedel_generator(double angle){

	double time;
	time = (0.06) * (12/343) *PI* (0.858358 - sin(angle));

	return time;

}*/
void delayMs(int n) 
{
	int i;
	int j;
	for(i = 0 ; i < n; i++)
	for (j = 0; j < 7000; j++) {}
}
void timedel_timer (double timdel){

	
	unsigned int rounded_mod;
	SIM->SCGC6 |= 0x01000000; /* enable clock to TPM0 */
	SIM->SOPT2 |= 0x01000000; /* use MCGFLLCLK as timer counter clock */
	TPM0->SC = 0; /* disable timer */
	
	
	rounded_mod = round(timdel);
	rounded_mod = (uint32_t) rounded_mod;
	delayMs(1);
  TPM0 ->MOD =  rounded_mod;
	TPM0->SC |= 0x8E; 
	
	
	while((TPM0->SC & 0x80) == 0) { }/* wait until the TOF is set */
	TPM0->SC |= 0x80; /* clear TOF */
	TPM0->SC = 0; /* disable timer */


	
	
}



void ADC0_init(void)
{
	SIM->SCGC5 |= 0x2000; /* clock to PORTE */
	SIM->SCGC5 |= (1UL<<10);
	SIM->SCGC5 |= (1UL<<11);
	PORTE->PCR[20] = 0; /* PTE20 analog input */
	PORTE -> PCR[29] = 0x100;
	PTE->PDDR |= (1UL << 29);
	SIM->SCGC6 |= 0x8000000; /* clock to ADC0 */
	ADC0->SC2 &= ~0x40; /* software trigger */
	/* clock div by 4, long sample time, single ended 12 bit, bus clock */
	ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00;
}

void pin_init(void) 
{
	SIM->SCGC5 |= (1UL <<9) | (1UL <<12); /* enable clock to Port D */
	PORTD->PCR[0] = 0x100; /* make PTD0 pin as GPIO */
	
	PORTD->PCR[1] = 0x100; /* make PTD1 pin as GPIO */
	
	PORTD->PCR[2] = 0x100; /* make PTD2 pin as GPIO */
	
	PORTD->PCR[3] = 0x100; /* make PTD3 pin as GPIO */
	
	PORTD->PCR[4] = 0x100; /* make PTD4 pin as GPIO */
	
	PORTD->PCR[6] = 0x100; /* make PTD5 pin as GPIO */
	/*
	PORTC->PCR[2] = 0x100;
	
	PORTB->PCR[3] = 0x100;
	
	PORTB->PCR[2] = 0x100;
	
	PORTB->PCR[1] = 0x100;
	
	PORTB->PCR[8] = 0x100;

	PTB->PDDR |= 0x1E;
	PTC->PDDR |= 0x0F;
	*/
	PTD->PDDR |= 0xFF; /* make PTD0-4 and 6 as output pin */
	
	
	
	
}


void init_switch(void) {
	SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK; /* enable clock for port D */

	/* Select GPIO and enable pull-up resistors and interrupts 
		on falling edges for pins connected to switches */
	PORTA->PCR[SW_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	
	/* Set port D switch bit to inputs */
	

	/* Enable Interrupts */
	NVIC_SetPriority(PORTA_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTA_IRQn); 
	NVIC_EnableIRQ(PORTA_IRQn);
}

void PORTA_IRQHandler(void) {  
	DEBUG_PORT->PSOR = MASK(DBG_ISR_POS);
	PTD -> PDOR &= 0x00000000; 
	
	// clear pending interrupts
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	if ((PORTA->ISFR & MASK(SW_POS))) {
		  direction ^= 1;
		
	
	}
	// clear status flags 
	PORTA->ISFR = 0xffffffff;
	DEBUG_PORT->PCOR = MASK(DBG_ISR_POS);
	
}

void LED_set(int s) 
{
	if (s & 1) /* use bit 0 of s to control red LED */
	PTB->PCOR = 0x40000; /* turn on red LED */
	else
	PTB->PSOR = 0x40000; /* turn off red LED */
	if (s & 2) /* use bit 1 of s to control green LED */
	PTB->PCOR = 0x80000; /* turn on green LED */
	else
	PTB->PSOR = 0x80000; /* turn off green LED */
	if (s & 4) /* use bit 2 of s to control blue LED */
	PTD->PCOR = 0x02; /* turn on blue LED */
	else
	PTD->PSOR = 0x02; /* turn off blue LED */
}
