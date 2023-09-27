#include <Servo.h>

int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int data;

int linearStepDuration = 200;
int rotateStepDuration = 45;

void power(bool state){
  if(state){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

void linear(bool direction){
  power(true);

  servo1.write(180 * direction);
  servo2.write(180 * direction);
  servo3.write(180 * !direction);
  servo4.write(180 * !direction);

  delay(linearStepDuration);

  stop();
}

void rotate(bool clockwise){
  power(true);

  servo1.write(180 * clockwise);
  servo2.write(180 * clockwise);
  servo3.write(180 * clockwise);
  servo4.write(180 * clockwise);
  delay(rotateStepDuration);

  stop();
}

void stop(){
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
}

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  power(false);

  servo1.attach(8);
  servo2.attach(9);
  servo3.attach(10);
  servo4.attach(11);
  stop();

  Serial.begin(9600);
}

void loop() {
  while(Serial.available() > 0){
    data = Serial.read();
    Serial.println(data);

    //forward
    if(data == 49 || data == 'w' ){
      linear(true);
    }

    //backward
    if(data == 50 || data == 's'){
      linear(false);
    }

    //right
    if(data == 51 || data == 'd'){
     rotate(true);
    }

    //left
    if(data == 52 || data == 'a'){
      rotate(false);
    }
  }
}
