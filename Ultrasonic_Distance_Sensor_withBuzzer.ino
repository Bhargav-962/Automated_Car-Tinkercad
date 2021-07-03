int trig = 8;
int echo = 7;
float reading;

int input=9;
int state=0;
int buzzer=13;

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(input, INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);

}

void loop()
{
  state=digitalRead(input);
  Serial.println(state);
  if(state==HIGH)
  {
    float distance;
    digitalWrite(trig,LOW);
      delayMicroseconds(2);
    digitalWrite(trig,HIGH);
      delayMicroseconds(2);
    digitalWrite(trig,LOW);
    reading = pulseIn(echo,HIGH);
    distance=reading*0.017;
    if(distance<50)
    {
      tone(buzzer,200,100);
        delay(10);
      noTone(buzzer);
        delay(10);
    }
    Serial.print("The distance is : ");
    Serial.print(distance);
    Serial.println("cm");

    delay(20);
  }
}