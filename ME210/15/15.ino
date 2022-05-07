#include <IRremote.h>
int RECV_PIN = 11;             //定义RECV_PIN变量为11
IRrecv irrecv(RECV_PIN);
boolean ledState = HIGH;
decode_results results; //接收红外码
int currentNumber = 0;
//数码管显示0-9的数组
int num[10][8] = {
  {0,0,0,1,0,0,0,1},
  {0,1,1,1,1,1,0,1},
  {0,0,1,0,0,0,1,1},
  {0,0,1,0,1,0,0,1},
  {0,1,0,0,1,1,0,1},
  {1,0,0,0,1,0,0,1},
  {1,0,0,0,0,0,0,1},
  {0,0,1,1,1,1,0,1},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,1,1,0,1}
  };
//定义遥控器的上的12个按钮代码
long codes[12] = {
   0xFD30CF,0xFD08F7,               // 0 ,1
   0xFD8877,0xFD48B7,               // 2 ,3
   0xFD28D7,0xFDA857,               // 4 ,5
   0xFD6897,0xFD18E7,               // 6 ,7
   0xFD9867,0xFD58A7,               // 8 ,9
   0xFD20DF,0xFD609F,               // 前进键>, 后退键<
};
void setup() {
  // put your setup code here, to run once:
  int currentNumber = 0;
  Serial.begin(9600);
  irrecv.enableIRIn();
  for(int i=2;i<=9;i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);   //共阳极时HIGH表示灭的意思
  }
}
//显示数字
void showNumberX(int i){
  for(int pin = 2;pin<10;pin++){
    digitalWrite(pin,num[i][pin-2]);
  }
};


void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
  for(int i=0;i<12;i++){
      if(results.value == codes[i] && i<=9)
      {
        showNumberX(currentNumber = i);
        Serial.println(i);
        break;
      }
      else
      if(results.value == codes[10] && currentNumber !=0)
      {
        currentNumber--;
        showNumberX(currentNumber);
        Serial.println(currentNumber);
        break;
      }
      else
      if(results.value == codes[11] && currentNumber != 9)
      {
        currentNumber++;
        showNumberX(currentNumber);
        Serial.println(currentNumber);
        break;
      }
      if(results.value == 0xFD00FF)
      {
          ledState = !ledState;
          for(int i=2;i<=9;i++)
      {
        digitalWrite(i,ledState);   //共阳极时HIGH表示灭的意思
      }
      break;
      }
  }
    Serial.println(results.value,HEX);
    irrecv.resume();
  }
}
