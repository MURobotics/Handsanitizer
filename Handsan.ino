#include <Servo.h>
const int echoPin = 2;  //For Sensor
const int trigPin = 3;  //For Sensor
const int motorPin = 4; //For Motor
uint64_t dispenseTimes = 0;  //Keeps track of Number of dispenses
const int dispensePos = 500;
const int dispenseDefault = 0;
const int waitTime = 500;

const int DISTANCE_THRESHOLD = 10; //Theshold to Dispense


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
  int distance = getData();
  if(distance < DISTANCE_THRESHOLD){
    dispense();
    dispenseTimes++;
  }

}



bool dispense(){
    servo.write(180);
    delay(waitTime);
    servo.write(0);
    delay(waitTime*2);
    
    return true;
}

int getData() {
  int duration, cm, distance;
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