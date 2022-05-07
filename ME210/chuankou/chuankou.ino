char incomingbyte[10];
char pin=9;
bool state=false;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW);
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    Serial.readBytes(incomingbyte,7);
    if(!strcmp(incomingbyte,"Cmd001E"))
    {
      state=!state;
    digitalWrite(pin,state);
    }}
}
