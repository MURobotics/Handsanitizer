#include <Servo.h>
const int echoPin = 2;
const int trigPin = 3;
const int motorPin = 4;
int dispenseTimes = 0;
const int dispensePos = 500;
const int dispenseDefault = 0;
const int waitTime = 1000;

long floorDist;

Servo servo;

void setup() {
  // put your setup code here, to run once
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(motorPin);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  long distance = getData();
  if(distance < 20.8){
    dispense();
    dispenseTimes++;
  }
  

}



bool dispense(){
    servo.write(dispensePos);
    delay(waitTime);
    servo.write(dispenseDefault);
    delay(waitTime);
  
  return true;
}

long getData() {
  long duration, cm, distance;
  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * (0.034 / 2); //speed of sound in air divided by 2

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  
  return distance;
  
}
