const int buzzer = 7;
const int forcePin = A1;
int ForceValue = 0;

int input=11;
int state=0;

void setup()
{
  pinMode(input, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(forcePin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  state=digitalRead(input);
  Serial.println(state);
  if(state==HIGH)
  {
    ForceValue = analogRead(forcePin);
    Serial.println(ForceValue);

    if (ForceValue >= 300)
      tone(7,523,1000);

    else
      noTone(7);
  }
  else
      noTone(7);
}