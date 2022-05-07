#include <IRremote.h>
int RECV_PIN = 11;
int pin1=9;
IRrecv irrecv(RECV_PIN);
decode_results results;

int relayPin = 3;                           // 继电器连接到数字3
int relayState = HIGH;                      // 继电器初始状态为HIGH
long lastDebounceTime = 0;
long debounceDelay = 50;                    //去除抖动时间

void setup() {
  // put your setup code here, to run once:
  irrecv.enableIRIn();
  pinMode(pin1, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, relayState);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val;            //用于存储LM35读到的值
      double data;        //用于存储已转换的温度值
      val=analogRead(0);   //LM35连到模拟口，并从模拟口读值
      data = (double) val * (5/10.24);  // 得到电压值，通过公式换成温度
  if(data>27||data<5){        //  如果温度，蜂鸣器响
        relayState = !relayState;
        digitalWrite(relayPin, relayState);
      } else {          // 如果温度小于27
        digitalWrite(relayPin,LOW);
      }
  if(results.value == 0xFD00FF)
  {lastDebounceTime = millis();}
  if ((millis() - lastDebounceTime) > debounceDelay) {
    relayState = !relayState;
    digitalWrite(relayPin, relayState);
    }
    irrecv.resume();
}
