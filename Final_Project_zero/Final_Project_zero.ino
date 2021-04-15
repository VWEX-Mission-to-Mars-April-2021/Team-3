 
#include <NewPing.h>
#define TRIGGER_PIN 4
#define ECHO_PIN 5
#define TRIGGER_DOWN 13
#define ECHO_DOWN 17
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN,MAX_DISTANCE);
NewPing Dsonar(TRIGGER_DOWN, ECHO_DOWN,MAX_DISTANCE);

const int LEFT_FEEDBACK = 2; // Pin numbers on Rover
const int RIGHT_FEEDBACK = 3;

volatile int leftcounter = 0; // initiate counter to zero for start
volatile int rightcounter = 0; // counter could always be reset
volatile int leftspeed = 160;
volatile int rightspeed = 160;
volatile int roverDirection = 0;//what the rover is doing right now
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
  Dsonar.ping_cm();
  
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  
  pinMode(RIGHT_ENABLE, OUTPUT);
  pinMode(LEFT_ENABLE, OUTPUT);
  
  pinMode(RIGHT_REVERSE, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);
  
}

void loop()
{
  
  if(roverDirection==0)
  {
    delay(50);
    Serial.print("Ping:");
    int distance = sonar.ping_cm();
    Serial.print(distance);
    Serial.println("cm");
    if(distance <= 12 && distance >0)
    {
      HardStop();
      delay(1000);
      Reverse();
      delay(2000);
      TurnAround();
      roverDirection=1;
      leftcounter  = 0;
      rightcounter = 0;
    }
    else
    {
      Straight();
    }
  }
  if (roverDirection==1)
  {

    delay(50);
    Serial.print("Ping:");
    int distance = Dsonar.ping_cm();
    Serial.print(distance);
    Serial.println("cm");
    if(distance >= 15 && distance != 0)
    {
      HardStop();
      delay(1000);
      Reverse();
      delay(4000);
      TurnOffMotors();
      Boogie();
      TurnOffMotors();
      exit(0);
    }
    else
    {
      Straight();
    }
  }
  
  
}

void Straight()
{
  MoveForward();
  analogWrite(LEFT_ENABLE,leftspeed);
  analogWrite(RIGHT_ENABLE,rightspeed);
  
  if (rightcounter > leftcounter)
  {
    leftspeed = leftspeed + 2;
    rightspeed = rightspeed - 2;
  }
  
  if (leftcounter > rightcounter)
  {
    
    leftspeed = leftspeed - 2;
    rightspeed = rightspeed + 2;
  }
    
  if (leftcounter == rightcounter)
  {
    leftspeed = 160;
    rightspeed = 160;
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
    roverDirection = 0;
    delay(1000);
}

void Right90()
{
    TurnOnMotors();
    TurnRight();
    delay(690);
    TurnOffMotors();
    roverDirection = 0;
    delay(100);
}

void HardStop()
{

  digitalWrite(RIGHT_ENABLE,HIGH);
  digitalWrite(LEFT_ENABLE,HIGH);
  digitalWrite(LEFT_FORWARD,HIGH);
  digitalWrite(RIGHT_FORWARD,HIGH);
  digitalWrite(LEFT_REVERSE,HIGH);
  digitalWrite(RIGHT_REVERSE,HIGH);
}

void TurnAround()
{
  TurnOnMotors();
  TurnRight();
  delay(1960);
  TurnOffMotors();
  roverDirection = 0;
  delay(100);
}
void Boogie()
{
  TurnOnMotors();
  TurnLeft();
  delay(2800);
  TurnRight();
  delay(2800);
  
}
void LeftMotorISR(){
  // adds one to the counter on each motor revolution
  leftcounter++;
}
void RightMotorISR() {
  // adds one to the counter on each motor revolution
  rightcounter++;
}
