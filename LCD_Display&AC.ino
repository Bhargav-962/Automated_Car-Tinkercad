#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float temp;
int tempPin = A1;
int relayPin = 8;
int input=6;
int state=0;

#define fan 9

void setup(){
  	pinMode(input,INPUT);
	pinMode(fan, OUTPUT);
    pinMode(relayPin, OUTPUT);
  here:
  	state=digitalRead(input);
  	Serial.println(state);
  if(state==HIGH)
  {

  	lcd.begin(16, 3);
  
  	lcd.setCursor(2, 0);
  	lcd.print("Temp Control");
  	lcd.setCursor(3, 1);
  	lcd.print("Starting..");
    delay(20);
    lcd.clear();
  }
  if(state==LOW)
    goto here;
}

void loop()
{
  
  if(state==HIGH)
  {
    lcd.setCursor(0,2);
    temp = analogRead(tempPin);
    //temp = temp*0.48828125;
    float voltage = temp * 5.0;
      voltage /= 1024.0; 

      // print out the voltage
      //lcd.print(voltage); lcd.println(" volts");

      // now print out the temperature
      float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                    //to degrees ((voltage - 500mV) times 100)

    lcd.setCursor(0, 0);
    lcd.print("Temp = ");
    lcd.setCursor(9,0);
    lcd.print(temperatureC); 
    lcd.println(" C");
    lcd.setCursor(0,1);

    if(temperatureC >= 20)
    {
      poweronRelay();
      if(temperatureC >= 20 && temperatureC <= 25)
      {
        analogWrite(fan,51);
        lcd.print("Fan Speed: 20% ");
        delay(20);
        lcd.clear();
      }
      else if(temperatureC <= 35)
      {
        analogWrite(fan,102);
        lcd.print("Fan Speed: 40% ");
        delay(20);
        lcd.clear();
      }
      else if(temperatureC <= 40)
      {
        analogWrite(fan,153);
        lcd.print("Fan Speed: 60% ");
        delay(20);
        lcd.clear();
      }
      else if(temperatureC <= 44)
      {
        analogWrite(fan,200);
        lcd.print("Fan Speed: 80% ");
        delay(20);
        lcd.clear();
      }
      else if(temperatureC >= 45)
      {
        analogWrite(fan,255);
        lcd.print("Fan Speed: 100% ");
        delay(20);
        lcd.clear();
      }
    }
    else if(temperatureC < 20)
    {
      poweroffRelay();
      lcd.print("Fan Speed: 0% ");
      delay(20);
      lcd.clear();
    }
    state=digitalRead(input);
  }
  if(state==LOW)
  {
    lcd.clear();
    state=digitalRead(input);
  }
}

void poweronRelay()
  {
  	digitalWrite(relayPin, HIGH);
  }

void poweroffRelay()
  {
  	digitalWrite(relayPin, LOW);
  	analogWrite(fan,0);
  }