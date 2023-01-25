/* p7_1.c: A to D conversion of channel 0

*/
#include <MKL25Z4.h>
#include <math.h>
#ifndef GPIO_DEFS_H
#define GPIO_DEFS_H

#define MASK(x) (1UL << (x))

// Debug status bits
#define DBG_ISR_POS (0)
#define DBG_MAIN_POS (1)

#define DEBUG_PORT PTB

#endif
#define SW_POS (6)
void ADC0_init(void);
void LED_set(int s);
void LED_init(void);
void DAC0_init(void);
void delayMs(int n);
void init_switch(void);
void PORTD_IRQHandler(void);



	volatile int wave_number; 
	volatile int frek_counter;
int main (void)
{
	wave_number = 0;
	int i,k;
init_switch();
	__enable_irq();
const static int Wave[3][72] ={ 
{1536,2048,2560,3072,3584,4095,4095,3584,3072,2560,2048,1536,1024,512,0,0,512,1024,1536,2048,2560,3072,3584,4095,4095,3584,3072,2560,2048,1536,1024,512,0,0,512,1024,1536,2048,2560,3072,3584,4095,4095,3584,3072,2560,2048,1536,1024,512,0,0,512,1024,1536,2048,2560,3072,3584,4095,4095,3584,3072,2560,2048,1536,1024,512,0,0,512,1024},
{2048,2404,2748,3072,3364,3617,3822,3972,4065,4096,4065,3972,3822,3617,3364,3072,2748,2404,2048,1692,1348,1024,732,479,274,124,31,0,31,124,274,479,732,1024,1348,1692,2048,2404,2748,3072,3364,3617,3822,3972,4065,4096,4065,3972,3822,3617,3364,3072,2748,2404,2048,1692,1348,1024,732,479,274,124,31,0,31,124,274,479,732,1024,1348,1692},
{0,0,0,0,4095,4095,4095,4095,4095,4095,4095,4095,4095,0,0,0,0,0,0,0,0,0,4095,4095,4095,4095,4095,4095,4095,4095,4095,0,0,0,0,0,0,0,0,0,4095,4095,4095,4095,4095,4095,4095,4095,4095,0,0,0,0,0,0,0,0,0,4095,4095,4095,4095,4095,4095,4095,4095,4095,0,0,0,0,0}
};
	DAC0_init(); /* Configure DAC0 */
	int result;
	double mult;

	LED_init(); /* Configure LEDs */
	ADC0_init(); /* Configure ADC0 */
	while (1) {

		ADC0->SC1[0] = 0; /* start conversion on channel 0 */
		/*conversion here*/
		
		result = ADC0->R[0]; /* read conversion result and clear COCO flag */
		/*mult = (result >> 8);*/
		
		
		
		
		while(!(ADC0->SC1[0] & 0x80)) {
		
		
		for (i = 0; i < 72; i++) {
			/*mult = sineWave[i] * mult;*/
			/*mult = round(mult);*/
			/* write value to DAC0 */
			
			for (frek_counter = (wave_number != 2) ? 20 : 20 ; frek_counter>0; frek_counter--){
			mult = Wave[wave_number][i] * result/(4095);
			DAC0->DAT[0].DATL = ((int)mult & 0xff); /* write low byte */
			DAC0->DAT[0].DATH = ((int)mult >> 8) & 0x0f;/* write high byte */
			delayMs(1);}
		}}
		
				  /* wait for conversion complete */
	}
}


/*  DUC  */

void ADC0_init(void)
{
	SIM->SCGC5 |= 0x2000; /* clock to PORTE */
	PORTE->PCR[20] = 0; /* PTE20 analog input */
	PORTE -> PCR[29] = 0x100;
	PTE->PDDR |= (1UL << 29);
	SIM->SCGC6 |= 0x8000000; /* clock to ADC0 */
	ADC0->SC2 &= ~0x40; /* software trigger */
	/* clock div by 4, long sample time, single ended 12 bit, bus clock */
	ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00;
}

void LED_init(void) 
{
	SIM->SCGC5 |= 0x400; /* enable clock to Port B */
	SIM->SCGC5 |= 0x1000; /* enable clock to Port D */
	PORTB->PCR[18] = 0x100; /* make PTB18 pin as GPIO */
	PTB->PDDR |= 0x40000; /* make PTB18 as output pin */
	PORTB->PCR[19] = 0x100; /* make PTB19 pin as GPIO */
	PTB->PDDR |= 0x80000; /* make PTB19 as output pin */
	PORTD->PCR[1] = 0x100; /* make PTD1 pin as GPIO */
	PTD->PDDR |= 0x02; /* make PTD1 as output pin */
}
void DAC0_init(void) 
{
	SIM->SCGC6 |= 0x80000000; /* clock to DAC module */
	DAC0->C1 = 0; /* disable the use of buffer */
	DAC0->C0 = 0x80 | 0x20; /* enable DAC and use software trigger */
}

/* Delay n milliseconds
* The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
*/
void delayMs(int n) 
{
	int i;
	int j;
	for(i = 0 ; i < n; i++)
	for (j = 0; j < 7000; j++) {}
}


void init_switch(void) {
	SIM->SCGC5 |=  SIM_SCGC5_PORTD_MASK; /* enable clock for port D */

	/* Select GPIO and enable pull-up resistors and interrupts 
		on falling edges for pins connected to switches */
	PORTD->PCR[SW_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	
	/* Set port D switch bit to inputs */
	PTD->PDDR &= ~MASK(SW_POS);

	/* Enable Interrupts */
	NVIC_SetPriority(PORTD_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTD_IRQn); 
	NVIC_EnableIRQ(PORTD_IRQn);
}

void PORTD_IRQHandler(void) {  
	DEBUG_PORT->PSOR = MASK(DBG_ISR_POS);

	
	// clear pending interrupts
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	if ((PORTD->ISFR & MASK(SW_POS))) {
		  ++wave_number;
		
	wave_number = wave_number % 3;
	}
	// clear status flags 
	PORTD->ISFR = 0xffffffff;
	DEBUG_PORT->PCOR = MASK(DBG_ISR_POS);
	
}
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
