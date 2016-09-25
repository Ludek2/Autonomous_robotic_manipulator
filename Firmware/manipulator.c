//firmware for autonomous robotic manipulator
//author: Ludek Navratil


#define F_CPU 8000000UL

#include <avr/io.h>			// hlavičkový soubor pro mikrokontrolér ATmega16
#include <stdio.h> 		// definiční soubor pro mikrokontrolér ATmega16
#include ".\avr\interrupt.h" //definicni soubor pro obsluhu preruseni
#include <util/delay.h>		//definicni soubor pro zpozdeni
#include "lcd.h" 		

//-------------------------------------------------------------------------


#define SERVO_PORT		PORTA


#define PIN_OUT0 0
#define PIN_OUT1 1						// Definice pinu OUTPUT 1
#define PIN_OUT2 2						// Definice pinu OUTPUT 2
#define PIN_OUT3 3						// Definice pinu OUTPUT 3
#define PIN_OUT4 4
#define PIN_OUT5 5

#define DDR( x )		( *(&x - 1) )	// adresa směrového registru portu
/* Ovladani OUTPUT 1 */
#define output0low 	SERVO_PORT=SERVO_PORT | (1<<PIN_OUT0)
#define output0hi 	SERVO_PORT=SERVO_PORT & (0xFF-(1<<PIN_OUT0))
/* Ovladani OUTPUT 1 */
#define output1low 	SERVO_PORT=SERVO_PORT | (1<<PIN_OUT1)
#define output1hi 	SERVO_PORT=SERVO_PORT & (0xFF-(1<<PIN_OUT1))
/* Ovladani OUTPUT 2 */
#define output2low 	SERVO_PORT=SERVO_PORT | (1<<PIN_OUT2)
#define output2hi 	SERVO_PORT=SERVO_PORT & (0xFF-(1<<PIN_OUT2))
/* Ovladani OUTPUT 3 */
#define output3low 	SERVO_PORT=SERVO_PORT | (1<<PIN_OUT3)
#define output3hi	SERVO_PORT=SERVO_PORT & (0xFF-(1<<PIN_OUT3))
/* Ovladani OUTPUT 4 */
#define output4low 	SERVO_PORT=SERVO_PORT | (1<<PIN_OUT4)
#define output4hi	SERVO_PORT=SERVO_PORT & (0xFF-(1<<PIN_OUT4))
/* Ovladani OUTPUT 5 */
#define output5low 	SERVO_PORT=SERVO_PORT | (1<<PIN_OUT5)
#define output5hi	SERVO_PORT=SERVO_PORT & (0xFF-(1<<PIN_OUT5))

//--------------------------------------------------------------------------
volatile int timer=0;
volatile int impuls[6];
volatile int doplnek[6];
volatile int stop=0;
volatile int preruseni_on=0;

char LCD_buffer[18];  //text pro LCD
char LCD_buffer2[18]; //text pro LCD
int citac_vypisu=0;   //pouzito ve funkci vypis_LCD

void USART0Init(void)
{
	/*//4800 Baud
	UCSRB=(1<<RXEN)  | (1<<TXEN);
	UCSRC=(1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	UBRRH=0x00;
	UBRRL=0x67;
	*/
	
	// 2400 Baud
	UCSRB=(1<<RXEN) | (1<<TXEN);
	UCSRC=(1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	UBRRL=0xCF;
	
	
	/* pro 9600 Baud
	UCSRB=0x98;
	UCSRC=0x86;           
	UBRRL=0x33;
	*/
}

void USART0SendByte(uint8_t u8Data)
{
//wait while previous byte is completed
while(!(UCSRA&(1<<UDRE))){};
// Transmit data
UDR = u8Data;
}
uint8_t USART0ReceiveByte()
{
// Wait for byte to be received
while(!(UCSRA&(1<<RXC))){};
// Return received data
return UDR;
}



void rizeni( int output,int natoceni);


void servo_init( void){
	
	OCR1A=100;
	DDRA=0xFF;
	TCCR1B=0x0B;
	TIMSK=0x10;

	rizeni( 0, 91);
	rizeni( 1, 180);
	rizeni( 2, 160);
	rizeni( 3, 180);
	rizeni( 4, 180);
	rizeni( 5, 180);
}

ISR(USART_RXC_vect){
	
	if(preruseni_on==10){ 
		uint8_t u8TempData;
		u8TempData = USART0ReceiveByte();
		USART0SendByte(u8TempData);
		if (u8TempData==7){
				stop=1;
				preruseni_on=0;
		}
		
	}	
	
}

external_interupt_init(){
	MCUCR|=(1<<ISC01) | (0<<ISC00);
	GICR|=(1<<INT0);
	
}

ISR(INT0_vect){

	stop=1;
	PORTD=0x00;
	//_delay_ms(10);
}
	
	
ISR( TIMER1_COMPA_vect ){
	
	if(timer==13)timer=0;
	switch(timer){

		//výstup 1
		case 0:{
			output0low;
			OCR1A=impuls[0];
			break;
			
		}
		case 1:{
			output0hi;
			OCR1A=doplnek[0];
			break;
		}
		
		
		//Výstup 2
		case 2:{
			output1low;
			OCR1A=impuls[1];
			break;
		}
		case 3:{
			output1hi;
			OCR1A=doplnek[1];
			break;
		}


		//výstup 3
		case 4:{
			output2low;
			OCR1A=impuls[2];
			break;
		}
		case 5:{
			output2hi;
			OCR1A=doplnek[2];
			break;
		}
		
		
		//Výstup 4
		case 6:{
			output3low;
			OCR1A=impuls[3];
			break;
		}
		case 7:{
			output3hi;
			OCR1A=doplnek[3];
			break;
		}


		//výstup 5
		case 8:{
			output4low;
			OCR1A=impuls[4];
			break;
		}
		case 9:{
			output4hi;
			OCR1A=doplnek[4];
			break;
		}
		
		
		//Výstup 6
		case 10:{
			output5low;
			OCR1A=impuls[5];
			break;
		}
		case 11:{
			output5hi;
			OCR1A=doplnek[5];
			break;
		}


		//Doplněk do 50hz (20ms) 
	
		case 12:{
		
			OCR1A=250; // 2ms
			break;
		}


	}
	timer++;	 
}

void vypis_LCD(){
	
	if(citac_vypisu<20){
		sprintf ( LCD_buffer ,  "S0:%3i X- S2:%3i" , impuls[0], impuls[2] ) ;
		sprintf ( LCD_buffer2 , "S1:%3i -- S3:%3i" , impuls[1], impuls[3] ) ;
	}
	if(citac_vypisu>=20 && citac_vypisu<40){
		sprintf ( LCD_buffer ,  "S0:%3i -X S2:%3i" , impuls[0], impuls[2] ) ;
		sprintf ( LCD_buffer2 , "S1:%3i -- S3:%3i" , impuls[1], impuls[3] ) ;
	}
	if(citac_vypisu>=40 && citac_vypisu<60){
		sprintf ( LCD_buffer ,  "S0:%3i -- S2:%3i" , impuls[0], impuls[2] ) ;
		sprintf ( LCD_buffer2 , "S1:%3i -X S3:%3i" , impuls[1], impuls[3] ) ;
	}
	if(citac_vypisu>=60 && citac_vypisu<80){
		sprintf ( LCD_buffer ,  "S0:%3i -- S2:%3i" , impuls[0], impuls[2] ) ;
		sprintf ( LCD_buffer2 , "S1:%3i X- S3:%3i" , impuls[1], impuls[3] ) ;
		if(citac_vypisu==79)citac_vypisu=0;	
	}	
		
	citac_vypisu++;
	
	lcd_gotoxy(0,0);
	lcd_puts	( LCD_buffer );	
	lcd_gotoxy(0,1);
	lcd_puts	( LCD_buffer2 );
	
}

void rizeni( int output,int natoceni){
	
	impuls[output]=natoceni;
	doplnek[output]=375-natoceni;
	//vypis_LCD();
	
}


	
void automat( int data1[][3], int data2[][3], uint8_t pocet)
{
	
	preruseni_on=1;
	stop=0;
	int skok; 
		
		rizeni( 3, 90);//otevření chňapky
		_delay_ms(1000);
		
		int citac_uchopeni=0;
		int citac_polozeni=0;
		while(citac_uchopeni<pocet)
		{	
			
			for(int srovnani=0;srovnani<5;srovnani++)
			{
				// najetí na 1. pozici --------------------------
				rizeni( 0,data1[citac_uchopeni][0]);
				rizeni( 1,data1[citac_uchopeni][1]);
				rizeni( 2,data1[citac_uchopeni][2]);
				citac_uchopeni++;
				if(srovnani==0)_delay_ms(1000);
				else _delay_ms(110);
				if(stop==1)break;//přerušení uživatelem	
			}
			if(stop==1)break;//přerušení uživatelem
			
			
			rizeni( 3, 320);//uchopení
			_delay_ms(1000);
			
			if(stop==1)break;//přerušení uživatelem
			
			//nadzvednutí kolmo na pracovní plochu
			for(int srovnani=1;srovnani<=4;srovnani++)
			{
				rizeni( 0,data1[citac_uchopeni-srovnani][0]);
				rizeni( 1,data1[citac_uchopeni-srovnani][1]);
				rizeni( 2,data1[citac_uchopeni-srovnani][2]);
				_delay_ms(110);
				if(stop==1)break;//přerušení uživatelem
			}
			if(stop==1)break;//přerušení uživatelem
			//------------------------------------------------
						
			//proces položení
			for(int srovnani=0;srovnani<5;srovnani++)
			{
				// najetí na 2. pozici --------------------------
				rizeni( 0,data2[citac_polozeni][0]);
				rizeni( 1,data2[citac_polozeni][1]);
				rizeni( 2,data2[citac_polozeni][2]);
				citac_polozeni++;
				if(srovnani==0)_delay_ms(1000);
				else _delay_ms(110);
				if(stop==1)break;//přerušení uživatelem
			}
			if(stop==1)break;//přerušení uživatelem
						
			
			if(stop==1)break;//přerušení uživatelem
			
			rizeni( 3, 90);//otevření chňapky
			_delay_ms(1000);
				
			//nadzvednutí kolmo na pracovní plochu
			for(int srovnani=1;srovnani<=4;srovnani++)
			{
				rizeni( 0,data2[citac_polozeni-srovnani][0]);
				rizeni( 1,data2[citac_polozeni-srovnani][1]);
				rizeni( 2,data2[citac_polozeni-srovnani][2]);
				_delay_ms(110);
				
				if(stop==1)break;//přerušení uživatelem
			}
			if(stop==1)break;//přerušení uživatelem
			//------------------------------------------------
		}	
}
	


int main()
{
	uint8_t u8TempData=255;
	
	int a=999;
	lcd_init(LCD_DISP_ON);
	_delay_ms(1000);
	USART0Init();
	servo_init();
	external_interupt_init();
	sei();
	

	int max_pozic=200;
	int pozice1[max_pozic][3];
	int pozice2[max_pozic][3];
	uint8_t pocitadlo_1=0;
	uint8_t pocitadlo_2=0;	
	
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts	( " NENI NAVAZANA  " );
	lcd_gotoxy(0,1);
	lcd_puts	( "KOMUNIKACE S PC" );
	
	/* test */
	DDRC=0x00;
	PORTC=0xFF;
	uint8_t citac=1;
	DDRD=0xF0;
	PORTD=0xF0;
	
	
	while(1){
		
		// Receive data		
		u8TempData = USART0ReceiveByte();
        // Send back to terminal
        USART0SendByte(u8TempData);
		
		if(u8TempData==7){ // zahájení komunikace s programem
			lcd_clrscr();
			lcd_puts	( "   CEKANI NA    " );
			lcd_gotoxy(0,1);
			lcd_puts	( "   INSTRUKCE" );
			// Receive data		
			u8TempData = USART0ReceiveByte();
			// Send back to terminal
			//USART0SendByte(u8TempData);
		}
		
		if(u8TempData==8){ // konec komunikace s programem
			lcd_clrscr();
			lcd_puts	( " NENI NAVAZANA  " );
			lcd_gotoxy(0,1);
			lcd_puts	( "KOMUNIKACE S PC" );
			
		}			
				
		
		if(u8TempData<4){
			a=u8TempData; //cislo serva
		}			
		if(u8TempData>9) {
			rizeni( a,u8TempData+63);
		}			

		if(u8TempData==4){
			
			//lcd_clrscr();
			//lcd_puts	( " ZPRACOVANI DAT " );
			for(int i=0; i<3; i++){
				if(pocitadlo_1>max_pozic-1){
					pocitadlo_1=0;
					break;
				}					
				u8TempData = USART0ReceiveByte();
				//USART0SendByte(u8TempData);
				pozice1[pocitadlo_1][i] = u8TempData+63;
			}
			++pocitadlo_1;
		
		} 
		
		if(u8TempData==5){
			
			//lcd_clrscr();
			//lcd_puts	( " ZPRACOVANI DAT " );
			for(int i=0; i<3; i++){
				if(pocitadlo_2>max_pozic-1){
					pocitadlo_2=0;
					break;
				}					
				u8TempData = USART0ReceiveByte();
				//USART0SendByte(u8TempData);
				pozice2[pocitadlo_2][i] = u8TempData+63;
				
			}
			++pocitadlo_2;
			

		}
		
		if(u8TempData==6){
			stop=0;
			PORTD=0xF0;
			lcd_clrscr();
			lcd_puts	( "    PROBIHA     " );
			lcd_gotoxy(0,1);
			lcd_puts	( "   MANIPULACE   " );
			if(pocitadlo_2==pocitadlo_1)automat( pozice1, pozice2, pocitadlo_1);
			rizeni( 0, 91);
			rizeni( 1, 180);
			rizeni( 2, 160);
			rizeni( 3, 180);
			pocitadlo_1=0;
			pocitadlo_2=0;
			preruseni_on=1;
			
			_delay_ms(3000);
			lcd_clrscr();
			lcd_puts	( "   MANIPULACE   " );
			lcd_gotoxy(0,1);
			lcd_puts	( "   DOKONCENA    " );
			// Send to terminal
			USART0SendByte(9);// odeslání bytu pro signalizaci ukončení funkce automat
			
			

		}
		
	} 

}
