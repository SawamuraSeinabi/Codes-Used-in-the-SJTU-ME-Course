#include <IRremote.h>
int RECV_PIN = 11;
int ledPin = 10;                // LED – digital 10
boolean ledState = LOW;         // ledstate用来存储LED的状态
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
     Serial.begin(9600);
     irrecv.enableIRIn();
     pinMode(ledPin,OUTPUT);       // 设置LED为输出状态
}

void loop() {
     if (irrecv.decode(&results)) {
          Serial.println(results.value, HEX);
          //一旦接收到电源键的代码, LED翻转状态，HIGH变LOW，或者LOW变HIGH
          if(results.value == 0xFD00FF){
               ledState = !ledState;             //取反
               digitalWrite(ledPin,ledState);    //改变LED相应状态
          }
     irrecv.resume();
     }
}
