float sinVal;
int toneVal;
static int times = 0;
int diaodiao[9] = {262,294,330,349,392,440,494,523,587};  //网上能搜到音律的赫兹数,用数组保存
char SUNANA[128]="83333215122321.3388886565555553.6688655555665333.4345666655555555";   //随便搜个曲子，用字符数组保存
void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int index[128];
  for(int i=0;i<128;i++){
    index[i] = SUNANA[i]-48;
    }
  tone(10, diaodiao[index[1]],200);
  tone(10, diaodiao[index[2]],200);
  tone(10, diaodiao[index[3]],100);
  tone(10, diaodiao[index[4]],100);
  tone(10, diaodiao[index[5]],100);
  tone(10, diaodiao[index[6]],100);
  tone(10, diaodiao[index[7]],100);
  tone(10, diaodiao[index[8]],200);
  tone(10, diaodiao[index[9]],100);
  tone(10, diaodiao[index[10]],100);
  tone(10, diaodiao[index[11]],100);
  tone(10, diaodiao[index[12]],100);
  tone(10, diaodiao[index[13]],100);
goSing(SUNANA);
}
void goSing(char *music){
  for(int i=0;i<128;i++){
    int index = music[i]-48;     //ascii码里字符 '1'= 49，所以需要减去48
    if(index >0 && index <10){
      tone(10, diaodiao[index],100);    //发出声音，200毫秒持续时间
    }else{
      delay(250);
    }
    if(music[i] == 0){       //由于C语言数组默认是0，所以遇到0就break（跳出循环）
      break;
    }
    delay(200);
  }
}
