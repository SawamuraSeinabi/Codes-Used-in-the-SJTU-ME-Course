char incomingbyte[10];
char pin=9;
int buttonPin = 2;
bool state=false;
int buttonState;
int lastButtonState = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin,OUTPUT);
  pinMode(buttonPin, INPUT);
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
    }
  }
    int reading = digitalRead(buttonPin);   //reading用来存储buttonPin的数据
      if (reading != lastButtonState) {
        state=!state;
        astButtonState=!lastButtonState;
        digitalWrite(pin,state);
      }
}
