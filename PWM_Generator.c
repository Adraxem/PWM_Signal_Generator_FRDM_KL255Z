/* module3.c: Based on Mazidi etal book. 
 * Initialize and display "EEE212" on the first row 
 * Display the number a on the second raw as decimal and hexadecimal 
 * using 8-bit data mode.
 * Data pins use Port D, control pins use Port A.
 * Then wait until a key pressed and display the typed keys on the f
 * first row after clearing screen
 * The LCD’s data pins are connected to PORTD of the microcontroller.
 * The LCD’s RS pin is connected to Pin 2 of PORTA of the microcontroller.
 * The LCD’s R/W pin is connected to Pin 4 of PORTA of the microcontroller.
 * The LCD’s E pin is connected to Pin 5 of PORTA of the microcontroller.
 * Polling of the busy bit of the LCD status bit is used for timing.
 * Raws of the keypad are connected to PORTC 0-3, Columns are connected to PORTC4-7.
  * pull-ups are enabled
 */

#include <MKL25Z4.H>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#define RS 0x04     /* PTA2 mask */ 
#define RW 0x10     /* PTA4 mask */ 
#define EN 0x20     /* PTA5 mask */

void Delay(volatile unsigned int time_del);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
void LCD_ready(void);
void keypad_init(void);
uint32_t keypad_getkey(void);


int main(void)
{
	
	char first_var[8]; /* these two will hold the operands (input)*/
	char sec_var[8];
	char third_var[8];
	char fourth_var[8];
	
	int firstop;
	int secop; // the converted integers willbe here
	int thirdop;
	int fourthop;
	
/* uWu */
	
	uint32_t key;

	
	uint32_t checkfor;
	
	char lookup[]= {'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};

	
	
	LCD_init();
	LCD_command(0x01);
	LCD_command(0x80);      /* set cursor at first line */
	LCD_data('E');          /* write the word on LCD */
	LCD_data('E');
	LCD_data('E');
	LCD_data('2');
	LCD_data('1');
	LCD_data('2');
	LCD_data('-');          /* write the word on LCD */
	LCD_data('E');
	LCD_data('F');
	LCD_data('E');
	LCD_data('/');
	LCD_data('A');
	LCD_data('R');          /* write the word on LCD */
	LCD_data('D');
	LCD_data('A');
	LCD_command(0xC0);  /* set cursor at second line */
	LCD_data('P');          /* write the word on LCD */
	LCD_data('W');
	LCD_data('M');
	LCD_data(' ');
	LCD_data('S');
	LCD_data('I');
	LCD_data('G');          /* write the word on LCD */
	LCD_data('N');
	LCD_data('A');
	LCD_data('L');



	
		keypad_init();
    while(keypad_getkey() == 0)
    {
		}
    LCD_command(0x01);
		LCD_data('F');
		LCD_data('1');
		LCD_data(':');

		
	
		//OUR CODE STARTS HERE
		int i = 0;
		while(i < 3)	
		{
			
		Delay(300000);	
		key=keypad_getkey();
			while(key == 0){
				key=keypad_getkey();
		}
		
			if(key != 0){
				checkfor = keypad_getkey();
				while(checkfor != 0){
				checkfor=keypad_getkey();
		}
				if (key != 4 && key != 8 && key != 12 && key != 13 && key != 15 && key != 16) 
			{
		  LCD_data(lookup[key-1]);
				first_var[i] = lookup[key-1]; 
				Delay(300000);
				key =0;
				++i;
		}
			
		
		
	}
			
	
		}
	first_var[++i] = '\0'; //end the char array with EOL
		LCD_data('H');
	LCD_data('z');
	LCD_data(' ');
	LCD_data('D');
	LCD_data('1');
	LCD_data(':');
	LCD_data('%');
	
// with the end of this loop, the first operand and operation and operand is stored as a string 
		//now its time for the second operand
	
	
		i = 0;
		while(i < 2)	
		{
			
		Delay(300000);	
		key=keypad_getkey();
			while(key == 0){
				key=keypad_getkey();
		}
		
			if(key != 0){
				checkfor = keypad_getkey();
				while(checkfor != 0){
				checkfor=keypad_getkey();
		}
				if (key != 4 && key != 8 && key != 12 && key != 13 && key != 15 && key != 16) // if it is pressed and not an operand //cascaded code is problematic check here!
			{
		  LCD_data(lookup[key-1]);
				sec_var[i] = lookup[key-1]; 
				Delay(300000);
				key =0;
				++i;
		}
	}
			
			
		}
		sec_var[i] = '\0'; //end the char array with EOL
	
		
		LCD_command(0xC0); //second line
			LCD_data('F');
		LCD_data('2');
		LCD_data(':');
		i=0;
		while(i < 3)	
		{
			
		Delay(300000);	
		key=keypad_getkey();
			while(key == 0){
				key=keypad_getkey();
		}
		
			if(key != 0){
				checkfor = keypad_getkey();
				while(checkfor != 0){
				checkfor=keypad_getkey();
		}
				if (key != 4 && key != 8 && key != 12 && key != 13 && key != 15 && key != 16) // if it is pressed and not an operand //cascaded code is problematic check here!
			{
		  LCD_data(lookup[key-1]);
				third_var[i] = lookup[key-1]; 
				Delay(300000);
				key =0;
				++i;
		}
			
		
		
	}
			
}
third_var[++i] = '\0'; //end the char array with EOL
	
	LCD_data('H');
	LCD_data('z');
	LCD_data(' ');
	LCD_data('D');
	LCD_data('2');
	LCD_data(':');
	LCD_data('%');
	
// with the end of this loop, the first operand and operation and operand is stored as a string 
		//now its time for the second operand
	
	
		i = 0;
		while(i < 2)	
		{
			
		Delay(300000);	
		key=keypad_getkey();
			while(key == 0){
				key=keypad_getkey();
		}
		
			if(key != 0){
				checkfor = keypad_getkey();
				while(checkfor != 0){
				checkfor=keypad_getkey();
		}
				if (key != 4 && key != 8 && key != 12 && key != 13 && key != 15 && key != 16) // if it is pressed and not an operand //cascaded code is problematic check here!
			{
		  LCD_data(lookup[key-1]);
				fourth_var[i] = lookup[key-1]; 
				Delay(300000);
				key =0;
				++i;
		}
	}
			
			
		}
		fourth_var[i] = '\0'; //end the char array with EOL

		
		
firstop= (first_var[0] - '0')*100 + (first_var[1] - '0')*10 + (first_var[2] - '0');
secop = (sec_var[0] - '0')*10 + (sec_var[1] - '0');
thirdop= (third_var[0] - '0')*100 + (third_var[1] - '0')*10 + (third_var[2] - '0');
fourthop = (fourth_var[0] - '0')*10 + (fourth_var[1] - '0');
		
	uint32_t mod;
	uint32_t mod2;
	uint32_t cv_1;
	uint32_t cv_2;
	unsigned int rounded_mod;
	unsigned int rounded_cv1;
	unsigned int rounded_mod2;
	unsigned int rounded_cv2;	
	

	mod = (((20.97152 * pow(10,6))/(256 * firstop))-1);
  cv_1 = (secop/100.0) * (mod + 1);


rounded_mod = round(mod);
rounded_mod = (uint32_t)rounded_mod;
rounded_cv1 = round(cv_1);
cv_1 = (uint32_t)cv_1;

mod2 = (((20.97152 * pow(10,6))/(256 * thirdop))-1);
  cv_2 = ((100.0 - fourthop)/100.0) * (mod2 + 1);

rounded_mod2 = round(mod2);
rounded_mod2 = (uint32_t)rounded_mod2;
rounded_cv2 = round(cv_2);
cv_2 = (uint32_t)cv_2;
		
		
SIM->SCGC5 |= (1ul << 13); /* enable clock to Port D */
PORTE->PCR[31] = 0x0300; /* PTD1 used by TPM0 */
SIM->SCGC6 |= 0x01000000; /* enable clock to TPM0 */
SIM->SOPT2 |= 0x01000000; /* use MCGFLLCLK as timer counter clock */
TPM0->SC = 0; /* disable timer */
TPM0->CONTROLS[4].CnSC = 0x20 | 0x08; /* center-aligned, pulse high */
TPM0->MOD = rounded_mod; /* Set up modulo register for 1 kHz */
TPM0->CONTROLS[4].CnV = cv_1; /* Set up channel value for 40% duty cycle */
TPM0->SC = 0x0F | 0x20; /* enable TPM0 with prescaler /16, center-aligned */


SIM->SCGC5 |= (1ul << 9); /* enable clock to Port D */
PORTA->PCR[12] = 0x0300; /* PTD1 used by TPM0 */
SIM->SCGC6 |= 0x02000000; /* enable clock to TPM0 */
SIM->SOPT2 |= 0x01000000; /* use MCGFLLCLK as timer counter clock */
TPM1->SC = 0; /* disable timer */
TPM1->CONTROLS[0].CnSC = 0x20 | 0x08; /* center-aligned, pulse high */
TPM1->MOD = rounded_mod2; /* Set up modulo register for 1 kHz */
TPM1->CONTROLS[0].CnV = cv_2; /* Set up channel value for 40% duty cycle */
TPM1->SC = 0x0F | 0x20; /* enable TPM0 with prescaler /16, center-aligned */


while (1) {
	Delay(300000);
	key = keypad_getkey();
		if ( key == 13){
		firstop = firstop * 2;
		thirdop = thirdop *2;
			
			
		mod = (((20.97152 * pow(10,6))/(256 * firstop))-1);
  cv_1 = (secop/100.0) * (mod + 1);


rounded_mod = round(mod);
rounded_mod = (uint32_t)rounded_mod;
rounded_cv1 = round(cv_1);
cv_1 = (uint32_t)cv_1;

mod2 = (((20.97152 * pow(10,6))/(256 * thirdop))-1);
  cv_2 = ((100.0 - fourthop)/100.0) * (mod2 + 1);

rounded_mod2 = round(mod2);
rounded_mod2 = (uint32_t)rounded_mod2;
rounded_cv2 = round(cv_2);
cv_2 = (uint32_t)cv_2;
	
			TPM1->SC = 0; /* disable timer */
TPM1->CONTROLS[0].CnSC = 0x20 | 0x08; /* center-aligned, pulse high */
TPM1->MOD = rounded_mod2; /* Set up modulo register for 1 kHz */
TPM1->CONTROLS[0].CnV = cv_2; /* Set up channel value for 40% duty cycle */
TPM1->SC = 0x0F | 0x20; /* enable TPM0 with prescaler /16, center-aligned */
TPM0->SC = 0; /* disable timer */
TPM0->CONTROLS[4].CnSC = 0x20 | 0x08; /* center-aligned, pulse high */
TPM0->MOD = rounded_mod; /* Set up modulo register for 1 kHz */
TPM0->CONTROLS[4].CnV = cv_1; /* Set up channel value for 40% duty cycle */
TPM0->SC = 0x0F | 0x20; /* enable TPM0 with prescaler /16, center-aligned */
			
		}else if (key == 15){
			secop = secop + 10;
			fourthop = fourthop-10;
		mod = (((20.97152 * pow(10,6))/(256 * firstop))-1);
  cv_1 = (secop/100.0) * (mod + 1);


rounded_mod = round(mod);
rounded_mod = (uint32_t)rounded_mod;
rounded_cv1 = round(cv_1);
cv_1 = (uint32_t)cv_1;

mod2 = (((20.97152 * pow(10,6))/(256 * thirdop))-1);
  cv_2 = ((100.0 - fourthop)/100.0) * (mod2 + 1);

rounded_mod2 = round(mod2);
rounded_mod2 = (uint32_t)rounded_mod2;
rounded_cv2 = round(cv_2);
cv_2 = (uint32_t)cv_2;
	
			TPM1->SC = 0; /* disable timer */
TPM1->CONTROLS[0].CnSC = 0x20 | 0x08; /* center-aligned, pulse high */
TPM1->MOD = rounded_mod2; /* Set up modulo register for 1 kHz */
TPM1->CONTROLS[0].CnV = cv_2; /* Set up channel value for 40% duty cycle */
TPM1->SC = 0x0F | 0x20; /* enable TPM0 with prescaler /16, center-aligned */
TPM0->SC = 0; /* disable timer */
TPM0->CONTROLS[4].CnSC = 0x20 | 0x08; /* center-aligned, pulse high */
TPM0->MOD = rounded_mod; /* Set up modulo register for 1 kHz */
TPM0->CONTROLS[4].CnV = cv_1; /* Set up channel value for 40% duty cycle */
TPM0->SC = 0x0F | 0x20; /* enable TPM0 with prescaler /16, center-aligned */
		}
			
	}




	}
	


void LCD_init(void)
{
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */ 
    PORTD->PCR[0] = 0x100;      /* make PTD0 pin as GPIO */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PORTD->PCR[2] = 0x100;      /* make PTD2 pin as GPIO */
    PORTD->PCR[3] = 0x100;      /* make PTD3 pin as GPIO */
    PORTD->PCR[4] = 0x100;      /* make PTD4 pin as GPIO */
    PORTD->PCR[5] = 0x100;      /* make PTD5 pin as GPIO */
    PORTD->PCR[6] = 0x100;      /* make PTD6 pin as GPIO */
    PORTD->PCR[7] = 0x100;      /* make PTD7 pin as GPIO */
    PTD->PDDR = 0xFF;           /* make PTD7-0 as output pins */
    
    SIM->SCGC5 |= 0x0200;       /* enable clock to Port A */ 
    PORTA->PCR[2] = 0x100;      /* make PTA2 pin as GPIO */
    PORTA->PCR[4] = 0x100;      /* make PTA4 pin as GPIO */
    PORTA->PCR[5] = 0x100;      /* make PTA5 pin as GPIO */
    PTA->PDDR |= 0x34;          /* make PTA5, 4, 2 as output pins */
    
    LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x01);      /* clear screen, move cursor to home */
    LCD_command(0x0F);      /* turn on display, cursor blinking */
}

/* This function waits until LCD controller is ready to
 * accept a new command/data before returns.
 */
void LCD_ready(void)
{
    uint32_t status;
    
    PTD->PDDR = 0x00;          /* PortD input */
    PTA->PCOR = RS;         /* RS = 0 for status */
    PTA->PSOR = RW;         /* R/W = 1, LCD output */
    
    do {    /* stay in the loop until it is not busy */
			  PTA->PCOR = EN;
			  Delay(500);
        PTA->PSOR = EN;     /* raise E */
        Delay(500);
        status = PTD->PDIR; /* read status register */
        PTA->PCOR = EN;
        Delay(500);			/* clear E */
    } while (status & 0x80UL);    /* check busy bit */
    
    PTA->PCOR = RW;         /* R/W = 0, LCD input */
    PTD->PDDR = 0xFF;       /* PortD output */
}

void LCD_command(unsigned char command)
{
    LCD_ready();			/* wait until LCD is ready */
    PTA->PCOR = RS | RW;    /* RS = 0, R/W = 0 */
    PTD->PDOR = command;
    PTA->PSOR = EN;         /* pulse E */
    Delay(500);
    PTA->PCOR = EN;
}

void LCD_data(unsigned char data)
{
    LCD_ready();			/* wait until LCD is ready */
    PTA->PSOR = RS;         /* RS = 1, R/W = 0 */
    PTA->PCOR = RW;
    PTD->PDOR = data;
    PTA->PSOR = EN;         /* pulse E */
    Delay(500);
    PTA->PCOR = EN;
}

/* Delay n milliseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */

/* delay n microseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */


void Delay(volatile unsigned int time_del) {
  while (time_del--) 
		{
  }
}


void keypad_init(void)
{
    SIM->SCGC5 |= 0x0800;       /* enable clock to Port C */ 
    PORTC->PCR[0] = 0x103;      /* make PTC0 pin as GPIO and enable pullup*/
    PORTC->PCR[1] = 0x103;      /* make PTC1 pin as GPIO and enable pullup*/
    PORTC->PCR[2] = 0x103;      /* make PTC2 pin as GPIO and enable pullup*/
    PORTC->PCR[3] = 0x103;      /* make PTC3 pin as GPIO and enable pullup*/
    PORTC->PCR[4] = 0x103;      /* make PTC4 pin as GPIO and enable pullup*/
    PORTC->PCR[5] = 0x103;      /* make PTC5 pin as GPIO and enable pullup*/
    PORTC->PCR[6] = 0x103;      /* make PTC6 pin as GPIO and enable pullup*/
    PORTC->PCR[7] = 0x103;      /* make PTC7 pin as GPIO and enable pullup*/
    PTC->PDDR = 0x00;         /* make PTC7-0 as input pins */
}




uint32_t keypad_getkey(void)
{
    uint32_t row, col;
    const char row_select[] = {0x01, 0x02, 0x04, 0x08}; /* one row is active */

    /* check to see any key pressed */
    PTC->PDDR |= 0x0F;          /* rows output */
    PTC->PCOR = 0x0F;               /* ground rows */
    Delay(500);                 /* wait for signal return */
    col =  PTC->PDIR & 0xF0UL;     /* read all columns */
    PTC->PDDR = 0;              /*  rows input */
    if (col == 0xF0UL)
        return 0;               /* no key pressed */

    /* If a key is pressed, it gets here to find out which key.
     * It activates one row at a time and read the input to see
     * which column is active. */
    for (row = 0; row < 4; row++)
    {
        PTC->PDDR = 0;                  /* disable all rows */
        PTC->PDDR |= row_select[row];   /* enable one row */
        PTC->PCOR = row_select[row];    /* drive the active row low */
        Delay(500);                     /* wait for signal to settle */
        col = PTC->PDIR & 0xF0UL;         /* read all columns */
        if (col != 0xF0UL) break;         /* if one of the input is low, some key is pressed. */
    }
    PTC->PDDR = 0;                      /* disable all rows */
    if (row == 4) 
        return 0;                       /* if we get here, no key is pressed */
 
    /* gets here when one of the rows has key pressed, check which column it is */
    if (col == 0xE0UL) return row * 4 + 1;    /* key in column 0 */
    if (col == 0xD0UL) return row * 4 + 2;    /* key in column 1 */
    if (col == 0xB0UL) return row * 4 + 3;    /* key in column 2 */
    if (col == 0x70UL) return row * 4 + 4;    /* key in column 3 */

    return 0;   /* just to be safe */
}

