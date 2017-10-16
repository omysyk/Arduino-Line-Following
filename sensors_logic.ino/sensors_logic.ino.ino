#define lineTracking1 11
#define lineTracking2 4
#define lineTracking3 2
int in1=9;
int in2=8;
int in3=6;
int in4=7;
int ENA=10;
int ENB=5;
int ABS=150;
int RED=140;
int ROL=130;
int delayTime=200;
bool num1, num2, num3;
bool onum1, onum2, onum3;
bool flag;

void _mForward(){
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("go forward! l,h l,h");
}
void _mBack(){
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("go back! h,l h,l");
}
void _mleft(){
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("go left! l,h h,l");
}
void _mright(){
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("go right! h,l l,h");
}
void _mStop(){
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.println("Stop!");
}
void _mslowLeft() {
  analogWrite(ENB,RED);
  delay(delayTime);
  analogWrite(ENB,ABS);
}
void _mslowRight() {
  analogWrite(ENA,RED);
  delay(delayTime);
  analogWrite(ENA,ABS);
}
void _mrollLeft() {
  analogWrite(ENB,ROL);
}
void _mrollRight() {
  analogWrite(ENA,ROL);
}
void setup(){
  Serial.begin(9600);
  num1 = num2 = num3 = true;
}
void loop() {
  Serial.println("start");
  //delay(1000);
  onum1 = num1; onum2 = num2; onum3 = num3;
  //analogWrite(ENA,ABS);
  //analogWrite(ENB,ABS);
  num1 = digitalRead(lineTracking1);
  num2 = digitalRead(lineTracking2);
  num3 = digitalRead(lineTracking3);
  Serial.print(num1); Serial.print(num2); Serial.print(num3); Serial.println();
  if(!num1 && num2 && !num3){
    // middle sensor on; move forward
    Serial.println("!num1 num2 !num3");
    _mForward();
  } else if(num1 && num2 && !num3) {
    // middle and left sensors on - off course, correct to left
    Serial.println("num1 num2 !num3 : slow left");
    //_mslowLeft();
    _mslowRight();
  } else if(num1 && !num2 && !num3) {
    // only left sensor on, drifted to the right, turn left
    Serial.println("num1 !num2 !num3: left");
    //_mleft();
    _mslowRight();
  } else if(!num1 && !num2 && !num3) {
    // all sensors off, seek the line
    Serial.println("num1 num2 num3: all off, stop");
    //_mStop();
    //delay(100);
    if (!onum1 && onum2 && !onum3) {
      // abrupt change to no line, seek the line by turning left
      _mleft();
    } else if (onum1 && onum2 && !onum3) {
      // drifted to the right, turn left
      //_mleft();
      _mright();
    } else if (!onum1 && onum2 && onum3) {
      // drifted to the right, turn left
      //_mleft();
      _mright();
    } else if (!onum1 && onum2 && onum3) {
      // drifted to the left very hard, turn right
      //_mright();
      _mleft();
    } else if (!onum1 && !onum2 && onum3) {
      // drifted to the left hard, turn right
      //_mright();
      _mleft();
    } else {
      _mleft();
      //delay(2000);
    }
  } else if(!num1 && num2 && num3) {
    // middle and right sensor on - off course, correct to right
    Serial.println("!num1 num2 num3: slow right");
    //_mslowRight();
    _mslowLeft();
  } else if(!num1 && !num2 && num3) {
    // only right sensor on, drifted to the left, turn right
    Serial.println("!num1 !num2 num3: right");
    //_mright();
    _mslowLeft();
  } else {
    Serial.println("not covered");
  }
}
