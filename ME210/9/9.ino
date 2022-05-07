void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  int val=0;
}

void loop() {
  int val=0;
  // put your main code here, to run repeatedly:
  val=analogRead(0);
  Serial.println(val);
  if(val<1000){digitalWrite(13,LOW);}else{digitalWrite(13,HIGH);}
  delay(100);
}
