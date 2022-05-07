void setup()
{
Serial.begin(38400);
pinMode( 2 , OUTPUT);
pinMode( 3 , OUTPUT);
pinMode( 4 , OUTPUT);
pinMode( 5 , OUTPUT);
pinMode( 6, OUTPUT);
pinMode( 7 , OUTPUT);
pinMode( 8 , OUTPUT);
pinMode( 9 , OUTPUT);
pinMode( 10 , OUTPUT);
pinMode( 11 , OUTPUT);
pinMode( 12 , OUTPUT);
pinMode( 13 , OUTPUT);
digitalWrite( 2 , LOW );
digitalWrite( 3 , LOW );//towardright
digitalWrite( 4 , LOW );
digitalWrite( 5 ,LOW );
digitalWrite( 6 ,LOW );//LEFT
digitalWrite( 7 ,LOW );
digitalWrite( 8 ,LOW );//TUP
digitalWrite( 9 ,LOW );//backup
digitalWrite( 10 ,LOW );
digitalWrite( 11 ,LOW );//BACK
digitalWrite( 12 ,LOW );
digitalWrite( 13 ,LOW);//T
}

void loop()
{
char x=Serial.read();
Serial.print("massage" );
delay(100);
if (( ( '1' ) == ( x )))
{
digitalWrite( 7 ,LOW );
digitalWrite( 8 ,HIGH );//TUP
}
if (( ( '2' ) == ( x ) ))
{
digitalWrite( 9 ,HIGH );//backup
digitalWrite( 10 ,LOW );
}
if (( ( '3' ) == ( x ) ))
{
digitalWrite( 7 ,HIGH );
digitalWrite( 8 ,LOW );//TUP
}
if (( ( '4' ) == ( x ) ))
{
digitalWrite( 9 ,LOW );//backup
digitalWrite( 10 ,HIGH);
}
if (( ( '7' ) == ( x ) ))
{
digitalWrite( 3 , HIGH );//towardright
digitalWrite( 4 , LOW );
digitalWrite( 5 ,LOW );
digitalWrite( 6 ,HIGH );//LEFT
}
if (( ( '8' ) == ( x ) ))
{
digitalWrite( 3 , LOW );//towardright
digitalWrite( 4 , HIGH );
digitalWrite( 5 ,HIGH );
digitalWrite( 6 ,LOW );//LEFT
}
if (( ( '9' ) == ( x ) ))
{
digitalWrite( 2 , LOW );
digitalWrite( 3 , LOW );//towardright
digitalWrite( 4 , LOW );
digitalWrite( 5 ,LOW );
digitalWrite( 6 ,LOW );//LEFT
digitalWrite( 7 ,LOW );
digitalWrite( 8 ,LOW );//TUP
digitalWrite( 9 ,LOW );//backup
digitalWrite( 10 ,LOW );
digitalWrite( 11 ,LOW );//BACK
digitalWrite( 12 ,LOW );
digitalWrite( 13 ,LOW);//T
}
if (( ( '0' ) == ( x ) ))
{
digitalWrite( 11 ,HIGH );//BACK
digitalWrite( 12 ,LOW );
digitalWrite( 13 ,HIGH);//T
digitalWrite( 2 ,LOW );
}
if (( ( '5' ) == ( x ) ))
{
digitalWrite( 3 , HIGH );//towardright
digitalWrite( 4 , LOW );
digitalWrite( 6 ,LOW );//LEFT
digitalWrite( 7 ,HIGH );
}
if (( ( '6' ) == ( x ) ))
{
digitalWrite( 3 , LOW );//towardright
digitalWrite( 4 , HIGH );
digitalWrite( 6 ,HIGH );//LEFT
digitalWrite( 7 ,LOW );
}
}