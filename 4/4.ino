void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPIUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int a=0; a<=255;a++) //循环语句，控制PWM亮度的增加
  {
    analogWrite(9,a);
    delay(8); //当前亮度级别维持的时间,单位毫秒
}
for (int a=255; a>=0;a--) //循环语句，控制PWM亮度减小
{
    analogWrite(9,a);
    delay(8); //当前亮度的维持的时间,单位毫秒
}
    delay(300); //完成一个循环后等待的时间,单位毫秒
}
