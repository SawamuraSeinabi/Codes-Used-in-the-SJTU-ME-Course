
int pin = 9;
int buzzerpin=10;
int potpin=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin,OUTPUT);
  pinMode(buzzerpin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pot = analogRead(potpin);
  Serial.print(pot);
  if (pot<10||pot>1010)
  {tone(buzzerpin,355);}
  if (pot>10&&pot<1010)
  {noTone(10);}
  int val = map(pot,0,1023,0,255);
    analogWrite(9,val);
  }
