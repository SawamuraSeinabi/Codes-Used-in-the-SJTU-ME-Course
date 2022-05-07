void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(buttonPin);   //reading用来存储buttonPin的数据
       // 一旦检测到数据发生变化，记录当前时间
      if (reading != lastButtonState) {
        lastDebounceTime = millis();
        }
       // 等待50ms，再进行一次判断，是否和当前button状态相同
       // 如果和当前状态不相同，改变button状态
       // 同时，如果button状态为高（也就是被按下），那么就改变继电器的状态
        if ((millis() - lastDebounceTime) > debounceDelay) {
          if (reading != buttonState) {
            buttonState = reading;
              if (buttonState == HIGH) {
              }
          }
        }
}
