int redperson =7;
int greenperson =8;
int button =9;
int greencar =10;
int yellowcar =11;
int redcar =12;

void setup() {
  // put your setup code here, to run once:
  pinMode(redperson,OUTPUT);
  pinMode(greenperson,OUTPUT);
  pinMode(redcar,OUTPUT);
  pinMode(yellowcar,OUTPUT);
  pinMode(greencar,OUTPUT);
  pinMode(button,INPUT);
  digitalWrite(redperson,HIGH);
  digitalWrite(greencar,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x=digitalRead(button);
  if(x==HIGH)
  {
    digitalWrite(greencar,LOW);
    digitalWrite(yellowcar,HIGH);
    delay(2000);
    digitalWrite(yellowcar,LOW);
    digitalWrite(redcar,HIGH);
    digitalWrite(redperson,LOW);
    digitalWrite(greenperson,HIGH);
    delay(5000);
    for(int i=0;i<10;i++)
    {
      digitalWrite(greenperson,HIGH);
      delay(200);
      digitalWrite(greenperson,LOW);
      delay(200);
      }
    digitalWrite(redperson,HIGH);
    digitalWrite(yellowcar,HIGH);
    delay(2000);
    digitalWrite(redcar,LOW);
    digitalWrite(yellowcar,LOW);
    digitalWrite(greencar,HIGH);
    }
}
