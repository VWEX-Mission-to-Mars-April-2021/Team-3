
#include <NewPing.h>
#define TRIGGER_PIN 4
#define ECHO_PIN 5
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN,MAX_DISTANCE);

const int LEFT_FEEDBACK = 2; // Pin numbers on Rover
const int RIGHT_FEEDBACK = 3;

volatile int leftcounter = 0; // initiate counter to zero for start
volatile int rightcounter = 0; // counter could always be reset
volatile int leftspeed = 160;
volatile int rightspeed = 160;
volatile int direction = 0;//what the rover is doing right now
volatile int times = 0;


const int RIGHT_FORWARD = 12;
const int RIGHT_REVERSE = 11;
const int RIGHT_ENABLE = 10;
const int LEFT_ENABLE = 9;
const int LEFT_FORWARD = 8;
const int LEFT_REVERSE = 7;

const int FORWARD_IN_MILLISECONDS = 5000;
const int STOP_IN_MILLISECONDS = 1000;
const int REVERSE_IN_MILLISECONDS = 2000;

const int COUNTS_PER_METRE = 435;


void setup()
{
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK),LeftMotorISR,RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK),RightMotorISR,RISING);
  
  sonar.ping_cm();
  
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  
  pinMode(RIGHT_ENABLE, OUTPUT);
  pinMode(LEFT_ENABLE, OUTPUT);
  
  pinMode(RIGHT_REVERSE, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);
  
  
}

void loop()
{
  delay(50);
  Serial.print("Ping:");
  int distance = sonar.ping_cm();
  Serial.print(distance);
  Serial.println("cm");
  
  if (distance <= 12)
  {
  TurnOffMotors();
  delay(2000);
  Reverse();
  TurnOnMotors();
  delay(2000);
  TurnOffMotors();
  delay(1000);
  Left90();
  delay(1000);
  }
  else
  {
    TurnOnMotors();
    MoveForward();
  }

}

void MoveForward()
{
  TurnOnMotors();
  digitalWrite(RIGHT_REVERSE, LOW);
  digitalWrite(LEFT_REVERSE, LOW);
  
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(LEFT_FORWARD, HIGH);
}

void Reverse()
{ 
  TurnOnMotors();
  
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(LEFT_FORWARD, LOW);
  
  digitalWrite(RIGHT_REVERSE, HIGH);
  digitalWrite(LEFT_REVERSE, HIGH);
}

void TurnOffMotors()
{  
  digitalWrite(RIGHT_ENABLE,LOW);
  digitalWrite(LEFT_ENABLE,LOW);
}

void TurnRight()
{
  digitalWrite(RIGHT_REVERSE, HIGH);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(LEFT_REVERSE, LOW);
}

void TurnLeft()
{
  digitalWrite(RIGHT_REVERSE, LOW);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(LEFT_REVERSE, HIGH);
}

void TurnOnMotors()
{
  digitalWrite(RIGHT_ENABLE, HIGH);
  digitalWrite(LEFT_ENABLE, HIGH);
}

void Left90()
{
    TurnOnMotors();
    TurnLeft();
  delay(690);
    TurnOffMotors();
    direction = 0;
    delay(1000);
}

void Right90()
{
  TurnOnMotors();
    TurnRight();
  delay(690);
    TurnOffMotors();
    direction = 0;
    delay(100);
}

void LeftMotorISR(){
  // adds one to the counter on each motor revolution
  leftcounter++;
}
void RightMotorISR() {
  // adds one to the counter on each motor revolution
  rightcounter++;
}
