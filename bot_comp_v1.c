#include <avr/io.h>
#include <util/delay.h>

void init_adc()								         // STEP 1 : ADC initialising function  (1. enable ADC. 2.choose reference voltage, 3. choose the sampling rate)
{
	ADCSRA = ADCSRA| (1<<ADEN);                     // Enable the ADC (0b00000001<<ADEN). Its left shift operator that creates ob10000000 i.e. ADEN is 1 rest of 7 other registors 0)
	ADCSRA = ADCSRA| (1<<ADPS2);			         // Set the sampling rate (ADPS2 because DIVISION FACTOR FOR 1MHZ/50K to 1MHZ/200K, is 8 & 16. we choose 16 i.e. 100)
	ADMUX  = ADMUX | (1<<REFS0);			         // Set the reference voltage (REFS1 & REFS0 as 10. ie. VCC to ATMEGA16) 
	
}


unsigned int pot1()						 			 // STEP 2: CONVERSION FUNCTION (1. choose input channel 2. start conversion 3. check conversion is complete 4. read digital output)
{
	ADMUX = ADMUX & (0b01000000);
	int p1 = 0b00000001;							 // select the input channel (mux1 that is PA1, connecting blue wire to 3RD PIN OF POTENTIOMETER). Variable is selected. Instead of writting three sepearate for MUX0, MUX1, MUX2)
	ADMUX = ADMUX |p1;							     // ADMUX = 01000000   (selecting the channel MUX0, leaving the REFS1 (0) AND REFS0(1))
	ADCSRA = ADCSRA| (1<<ADSC);				     // Start the conversion (set ADSC to 1, rest of the registers o, lets to start conversion factor)
	
	while ((ADCSRA & (0b00000001<<ADIF))==0);       // Check for end conversion  (check conversion is complete or not, during conversion ADIF is 0, at the end of conversion, ADIF is 1. when ADIF is 1, it goes out of while loop)
	{}
	ADCSRA = ADCSRA| (1<<ADIF);				     // clear ADIF bit (to start next digital conversion)
	return (ADC);								 	 // get the ouput from ADC
}

unsigned int read_adc_pot2()					     // STEP 2: CONVERSION FUNCTION (1. choose input channel 2. start conversion 3. check conversion is complete 4. read digital output)
{
	ADMUX = ADMUX & (0b01000000);
	int p2 = 0b00000011;							 // select the input channel (mux1 that is PA1, connecting blue wire to 3RD PIN OF POTENTIOMETER). Variable is selected. Instead of writting three sepearate for MUX0, MUX1, MUX2)
	ADMUX = ADMUX |p2;							 	 // ADMUX = 01000000   (selecting the channel MUX0, leaving the REFS1 (0) AND REFS0(1))
	ADCSRA = ADCSRA| (1<<ADSC);				 	 // Start the conversion (set ADSC to 1, rest of the registers o, lets to start conversion factor)
	
	while ((ADCSRA & (0b00000001<<ADIF))==0); 		 // Check for end conversion  (check conversion is complete or not, during conversion ADIF is 0, at the end of conversion, ADIF is 1. when ADIF is 1, it goes out of while loop)
	{}
	ADCSRA = ADCSRA| (1<<ADIF);					 // clear ADIF bit (to start next digital conversion)
	return (ADC);									 // get the ouput from ADC
}

void main()
{
	DDRD = 0b00000000; 					// Set Part A to receive INPUT  port
	DDRB = 0b11111111;					// Set Part B to give    OUTPUT port
	PORTD= 0b11111111;	    			// Pullup DDRD and Assign HIGH value to all pins

	init_adc();							// call ADC initialising function
	_delay_ms(500);

	int c;								// Declare a variable to receive PORTD value

	//unsigned int p1;					// initialsed as unsigned int as it relates to an analog input
	unsigned int p2;					// initialsed as unsigned int as it relates to an analog input
	unsigned int a2;

	unsigned int T2;
	unsigned int TON2;
	unsigned int TOFF2;

	unsigned int DC;
	
	while(1)	{							// Start the indefinite loop using  1 (True always) 
		c = PIND;
		
		while(c==0b11111100) { 			// NO OBSTACLE on SIDE, 	NO		CENTRE & LT sensor on LIGHT SURFACE & RT sensor on LIGHT SURFACE   
			
			/*p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);*/
			
			PORTB = 0b00001010;			// Move forward Lt Motor (10) & Rt Motor (10) 														& beep (index 4 = 1)  
			/*_delay_ms(TON2);
			PORTB = 0b00000000;
			_delay_ms(TOFF2);*/
		}
		
		while (c==0b11111101) {			// NO OBSTACLE on SIDE, 	NO		CENTRE & Lt.sensor on LIGHT SURFACE & Rt.sensor on BLACK LINE  
			
			/*p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);*/
			
			PORTB = 0b00001001;			// RT turn (Lt.Mot Fwd, Rt.Mot Rev) 
			/*_delay_ms(TON2);
			PORTB = 0b00000000;
			_delay_ms(TOFF2);*/
		}
		
		while (c==0b11111110) { 		// NO OBSTACLE on SIDE, 	NO		CENTRE & Lt.sensor on BLACK LINE    & Rt.sensor on LIGHT SURFACE  
			/*p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);*/
			
			PORTB = 0b00000110;			// LT turn (Lt.Mot Rev, Rt.Mot Fwd)     
			/*_delay_ms(TON2);
			PORTB = 0b00000000;
			_delay_ms(TOFF2);*/
		}
		
		while (c==0b11111111) {			// NO OBSTACLE on SIDE,     NO		CENTRE & Lt.sensor on BLACK LINE    & Rt.sensor on BLACK LINE  
			
			/*p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);*/
			
			PORTB = 0b00011010;			// FORWARD (Lt.Mot Fwd, Rt.Mot Fwd) + (BEEPS)
			/*_delay_ms(TON2);
			PORTB = 0b00000000;
			_delay_ms(TOFF2);*/
		}
		
		while (c==0b11111000) {			// NO OBSTACLE on SIDE, OBSTACLE IN CENTRE & LT sensor on LIGHT SURFACE & RT sensor on LIGHT SURFACE    
			
			/*p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);*/
			
			PORTB = 0b00010000;			// STOP    (Lt.Mot STP, Rt.Mot STP) + (BEEPs)
			/*_delay_ms(TON2);
			PORTB = 0b00000000;
			_delay_ms(TOFF2);*/
		}
		
		while (c==0b11111001) {			// NO OBSTACLE on SIDE, OBSTACLE IN CENTRE & LT sensor on LIGHT SURFACE & RT sensor on BLACK LINE 
			
			/*p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);*/
			
			PORTB = 0b00010000;			// STOP    (Lt.Mot STP, Rt.Mot STP) + (BEEPs)
			/*_delay_ms(TON2);
			PORTB = 0b00000000;
			_delay_ms(TOFF2);*/
		}
		
		while (c==0b11111010) {				// NO OBSTACLE on SIDE, OBSTACLE IN CENTRE & LT sensor on BLACK LINE    & RT sensor on LIGHT SURFACE 
			
			/*p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);*/
			
			PORTB = 0b00010000;			// STOP    (Lt.Mot STP, Rt.Mot STP) + (BEEPs)
			/*_delay_ms(TON2);
			PORTB = 0b00000000;
			_delay_ms(TOFF2);*/
		}
		
		while (c==0b11111011) { 		// NO OBSTACLE on SIDE, OBSTACLE IN CENTRE & LT sensor on BLACK LINE    & RT sensor on BLACK LINE 
			
			/*p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);*/
			
			PORTB = 0b00010000;			// STOP    (Lt.Mot STP, Rt.Mot STP) + (BEEPs)
			/*_delay_ms(TON2);
			PORTB = 0b00000000;
			_delay_ms(TOFF2);*/
		}
		
		while (c==0b11110100) {			// OBSTACLE on SIDE,        NO      CENTRE & LT sensor on LIGHT SURFACE & RT sensor on LIGHT SURFACE 
			p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);
			
			PORTB = 0b00001010;			// SLOW    (Lt.Mot Fwd, Rt.Mot Fwd)
			_delay_ms(DC);
			PORTB = 0b00000000;			// STOP    (Lt.Mot STP, Rt.Mot STP)  
			_delay_ms(T2-DC);
		}
		
		while(c==0b11110101) {			// OBSTACLE on SIDE,        NO      CENTRE & LT sensor on LIGHT SURFACE & RT sensor on BLACK LINE 
			
			p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);
			
			PORTB = 0b00001001;			// SLOW RT (Lt.Mot Fwd, Rt.Mot Rev)
			_delay_ms(DC);
			PORTB = 0b00000000;			// STOP    (Lt.Mot STP, Rt.Mot STP)  
			_delay_ms(T2-DC);
		}
		
		while (c==0b11110110) {			// OBSTACLE on SIDE,        NO      CENTRE & LT sensor on BLACK LINE    & RT sensor on LIGHT SURFACE 
			
			p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);
			
			PORTB = 0b00000110;			// SLOW LT (Lt.Mot Rev, Rt.Mot Fwd)
			_delay_ms(DC);
			PORTB = 0b00000000;			// STOP    (Lt.Mot STP, Rt.Mot STP)  
			_delay_ms(T2-DC);
		}
		
		while (c==0b11110111) {			// OBSTACLE on SIDE,        NO      CENTRE & LT sensor on BLACK LINE    & RT sensor on BLACK LINE 
			
			p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);
			
			PORTB = 0b00011010;			// SLOW FW (Lt.Mot Fwd, Rt.Mot Fwd) + (BEEP)
			_delay_ms(DC);
			PORTB = 0b00000000;			// STOP    (Lt.Mot STP, Rt.Mot STP)  
			_delay_ms(T2-DC);
		}
		
		while (c==0b11110000) {			// OBSTACLE on SIDE, OBSTACLE IN CENTRE   & LT sensor on LIGHT SURFACE  & RT sensor on LIGHT SURFACE 
			
			/*p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);*/
			
			PORTB = 0b00010000;			// STOP    (Lt.Mot STP, Rt.Mot STP) + (BEEP)
			_delay_ms(DC);
		}
		
		while (c==0b11110001) {			// OBSTACLE on SIDE, OBSTACLE IN CENTRE   & LT sensor on LIGHT SURFACE  & RT sensor on BLACK LINE 
			
			/*p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);*/
			
			PORTB = 0b00010000;			// STOP    (Lt.Mot STP, Rt.Mot STP) + (BEEP)
			_delay_ms(DC);
		}
		
		while (c==0b11110010) {			// OBSTACLE on SIDE, OBSTACLE IN CENTRE   & LT sensor on BLACK LINE     & RT sensor on LIGHT SURFACE 
			
			/*p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);*/
			
			PORTB = 0b00010000;			// STOP    (Lt.Mot STP, Rt.Mot STP) + (BEEP)
			_delay_ms(DC);
		}
		
		while (c==0b11110011) {			// OBSTACLE on SIDE, OBSTACLE IN CENTRE   & LT sensor on BLACK LINE     & RT sensor on BLACK LINE 
			
			/*p2 = read_adc_pot2();
			a2 = (p2/40);
			T2  = 25.6;
			TOFF2 = a2;
			TON2 = T2 - TOFF2;
			DC = (TON2*0.4);*/
			
			PORTB = 0b00010000;			// STOP    (Lt.Mot STP, Rt.Mot STP) + (BEEP)
			_delay_ms(DC);
		}	
	}
}