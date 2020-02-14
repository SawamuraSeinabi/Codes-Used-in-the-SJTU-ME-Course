char incomingbyte[10];
char pin=10;
char pin2 =3;
bool state=false;
unsigned long changeTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW);
  pinMode(pin2, INPUT);
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  char state1=digitalRead(pin2);
  if(state1==HIGH&&(millis()-changeTime>5000))
  {
    Serial.write("Cmd001E");
    changeTime=millis();
  }
  if(Serial.available())
  {
    Serial.readBytes(incomingbyte,7);
    if(!strcmp(incomingbyte,"Cmd001E"))
    {
      state=!state;
    digitalWrite(pin,state);
    }}
}
