#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <LiquidCrystal.h>
//#include <.h>

int engine_on =0;
int adc_reading =0,
adc_val;

int input=11;
int state=0;
void setup()
{
  pinMode(input, INPUT);
}


void init_ports()
{
  DDRC &= ~(1<<PC0);
  DDRD &= ~((1<<PD2)|(1<<PD3));
  DDRD |= ((1<<PD4)|(1<<PD6));
  PORTD &= ~(1<<PD4);
  PORTD |= (1<<PD6);
}

int read_adc()
{
   ADCSRA |= (1<<ADSC);
    while((ADCSRA & 0x10) == 0x10);
    {
      adc_reading = (ADCH<<8);
      adc_reading |= ADCL;
    }
  return (adc_reading);
}


int main()
{

  init_ports();
  // registers-------------
  sei();
  Serial.begin(9600);
  //for engine ON button(PD2) & engine OFF (PD3)
  EICRA |= ((1<<ISC11)|(1<<ISC01));
  EIMSK |= ((1<<INT0)|(1<<INT1));
  // adc
  ADMUX |= (1<<REFS0);
  ADCSRA |= (1<<ADEN);
  //-----pwm--
  TCCR0A |= (1<<WGM01);
  OCR0A = 200;
  OCR0B = 255;
  TIMSK0 |= ((1<<OCIE0A)|(1<<OCIE0B));
  while(1)
  {	
    state=digitalRead(input);
    Serial.println(state);
    if(engine_on == 1 && state==HIGH)
    {
     PORTD |= (1<<PD4);
     adc_val=read_adc();    //read adc value
    //Serial.println(adc_val);
      if(adc_val >= 0 && adc_val < 250 ) //low light,bright headlight
        {
           TCCR0B |= 0x00;
           OCR0A = 240;
           OCR0B = 255;
           TCCR0B |= ((1<<CS00)|(1<<CS02));
        }
      else if(adc_val >= 250 && adc_val < 500)//medium light,medium brightness
        {
           TCCR0B |= 0x00;
           OCR0A = 100;
           OCR0B =255;
           TCCR0B |= ((1<<CS00)|(1<<CS02));
        }
      else if(adc_val >= 500)   //bright light, low headlight
        {
           TCCR0B |= 0x00;
           OCR0A = 20;
           OCR0B = 255;
           TCCR0B |= ((1<<CS00)|(1<<CS02));
         }
     }
     else
     {
       PORTD &= ~(1<<PD6);
       PORTD &= ~(1<<PD4);
     }
   }  
}
ISR(INT0_vect)
{
  engine_on =1;
  digitalWrite(12, HIGH);
}
ISR(INT1_vect)
{
  engine_on =0;
  digitalWrite(12, LOW);
}
ISR(TIMER0_COMPA_vect)
{
  PORTD &= ~(1<<PD6);
}
ISR(TIMER0_COMPB_vect)
{
  PORTD |= (1<<PD6);
}
