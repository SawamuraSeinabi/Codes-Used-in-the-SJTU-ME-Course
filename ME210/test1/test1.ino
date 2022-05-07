
void setup() {
  // put your setup code here, to run once:
  pinMode(7,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(7,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(4,HIGH);
  delay(1000);
  digitalWrite(4,LOW);
  delay(1000);
}
