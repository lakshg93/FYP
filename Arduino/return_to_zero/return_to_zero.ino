const int stepPinX = 8; //clk
const int dirPinX = 9; //CW
const int enablePinX = 10; //en

const int stepPinY = 11;  //clk
const int dirPinY = 12;   //CW
const int enablePinY = 13; //en

const int limitSwitchXFront = 4;
const int limitSwitchXBack = 5;
const int limitSwitchYFront = 6;
const int limitSwitchYBack = 7;

const int stepTime = 500;  // half clock time

long xStepCount = 0; // no of X steps
long yStepCount = 0; // no of X steps

char rx_byte = '0'; // input byte from the serial monitor

boolean xDirection = HIGH; // initial directions of movement
boolean yDirection = HIGH;


int maxStepsX = 14000; //maximum steps towards X direction
int maxStepsY = 9000;  //maximum steps towards Y direction

void setup() {
  Serial.begin(9600);

  pinMode(dirPinX, OUTPUT);
  pinMode(stepPinX, OUTPUT);
  pinMode(enablePinX,OUTPUT);
  pinMode(enablePinY,OUTPUT);
  pinMode(dirPinY, OUTPUT);
  pinMode(stepPinY, OUTPUT);

  pinMode(limitSwitchXFront, INPUT);
  pinMode(limitSwitchXBack, INPUT);
  pinMode(limitSwitchYFront, INPUT);
  pinMode(limitSwitchYBack, INPUT);

  digitalWrite(dirPinX, xDirection);
  digitalWrite(dirPinY, yDirection);
  returnToZero();
}

void loop() {
  listenForCharacter();         // listen for inputs from serial monitor and update it with rx_byte
  if (rx_byte == '1') {
      motion (1000,1000);
    }
  else if (rx_byte == '2') {
      motion (8000,2000);
   }
   else if (rx_byte == '3') {
      moveBackward(2000);
      moveRight(1000);
   }

   delay(10000);
}

boolean forwardDirection(){return LOW;}
boolean backwardDirection(){return HIGH;}
boolean leftDirection(){return LOW;}
boolean rightDirection(){return HIGH;}


boolean changeMovingDirection(boolean state) {
  state = !state;
  return state;
}

void motion(int finalXLocation, int finalYLocation){
  if (xStepCount < finalXLocation){
    moveForward(finalXLocation - xStepCount);
  } else{
    moveBackward(xStepCount - finalXLocation);
  }
  
  if (yStepCount < finalYLocation){
    moveLeft(finalYLocation - yStepCount);
  } else if (yStepCount > finalYLocation){
    moveRight(yStepCount - finalYLocation);
  }
  
}


void moveForward(int steps) {
  enableMotor(enablePinX);
  digitalWrite(dirPinX, forwardDirection());
  while (reachedLimitSwitch(limitSwitchXBack) == LOW || xStepCount == steps) {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(stepTime);
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(stepTime);
    xStepCount = xStepCount + 1;
  }
  disableMotor(enablePinX);
}

void moveBackward(int steps) {
  enableMotor(enablePinX);
  digitalWrite(dirPinX, backwardDirection());
  while (reachedLimitSwitch(limitSwitchXFront) == LOW || xStepCount == steps) {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(stepTime);
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(stepTime);
    xStepCount = xStepCount - 1;
  }
  disableMotor(enablePinX);
}

void moveLeft(int steps) {
  enableMotor(enablePinY);
  digitalWrite(dirPinY, leftDirection());
  while (reachedLimitSwitch(limitSwitchYBack) == LOW || yStepCount == steps) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(stepTime);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(stepTime);
    yStepCount = yStepCount + 1;
  }
  disableMotor(enablePinY);
}

void moveRight(int steps) {
  enableMotor(enablePinY);
  digitalWrite(dirPinY, rightDirection());
  while (reachedLimitSwitch(limitSwitchYFront) == LOW || yStepCount == steps) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(stepTime);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(stepTime);
    yStepCount = yStepCount - 1;
  }
  disableMotor(enablePinY);
}

void returnToZero() {
    moveBackward(10000);
    moveRight(10000);
    xStepCount=0;
    yStepCount = 0;
}

boolean reachedLimitSwitch(int switchPin) {
  if (digitalRead(switchPin) == LOW) {
    return HIGH;
  }
  else {
    return LOW;
  }
}

void listenForCharacter(){
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();
    Serial.print(xStepCount);
    Serial.print(' ');
    Serial.print(yStepCount);
    Serial.print('\n');
  }
}

void disableMotor(int pinNumber){
  digitalWrite(pinNumber, LOW); 
}

void enableMotor(int pinNumber){
  digitalWrite(pinNumber, HIGH); 
}
