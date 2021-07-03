#include <IRremote.h>
#include <Servo.h>

int RECV_PIN = 3;

int signal=0;

int servoPin = 11;
Servo servo;
int pos = 0;  

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{ 
  Serial.begin(9600);
  irrecv.enableIRIn();
    
  pinMode(signal, OUTPUT);
  
  servo.attach(servoPin);
  servo.write(0);
}
void loop() {
  if (irrecv.decode(&results)) {
     	switch(results.value)
      {
        case 16582903:	Serial.println("1");
        				digitalWrite(5,HIGH);
          				digitalWrite(12,HIGH);
          				//delay(10);
          				for (pos; pos < 90; pos += 1)
          				{
    						servo.write(pos);
  						}
          		 		break;
           
        case 16615543:  Serial.println("2"); 
                        digitalWrite(5,LOW);
          				digitalWrite(12,LOW);
          				//delay(10);
          				for (pos; pos > 0; pos -= 1)
                        {
    						servo.write(pos);
                        }
                        break;
        case 16599223:	Serial.println("3");
          				digitalWrite(2,HIGH);
          				break;
        case 16591063:	Serial.println("4");
          				digitalWrite(2,LOW);
          				break;
        default: 		Serial.println(results.value);
          				//delay(10);
      }  
    irrecv.resume();
  }
}