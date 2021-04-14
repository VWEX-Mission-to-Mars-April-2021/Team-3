/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/

// help

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
  
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  
  pinMode(RIGHT_ENABLE, OUTPUT);
  pinMode(LEFT_ENABLE, OUTPUT);
  
  pinMode(RIGHT_REVERSE, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);
  
}

void loop()
{
  delay(1);
  if (direction == 0)
  {
    MoveForward();
    TurnOnMotors();
    delay(1500);
    TurnOffMotors();
    direction = 1;
    delay(100);
   }
  if (direction == 1)
  {
    TurnOnMotors();
    TurnLeft();
  delay(810);
    TurnOffMotors();
    direction = 0;
    times = times + 1;
    delay(100);
    if (times == 4)
    {
      direction = 2;
    }
  }
  
  if (direction == 2){
    TurnOffMotors();
    exit(0);
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

void LeftMotorISR(){
  // adds one to the counter on each motor revolution
  leftcounter++;
}
void RightMotorISR() {
  // adds one to the counter on each motor revolution
  rightcounter++;
}
