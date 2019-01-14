const int stepPinX = 11; //clk
const int dirPinX = 12; //CW
const int enablePinX = 13; //en

const int stepPinY = 8;  //clk
const int dirPinY = 9;   //CW
const int enablePinY = 10; //en

const int limitSwitchXFront = 7;
const int limitSwitchXBack = 6;
const int limitSwitchYFront = 4;
const int limitSwitchYBack = 5;

const int ledPin = 3;

const int stepTime = 750;  // half clock time

long xStepCount = 0; // no of X steps
long yStepCount = 0; // no of X steps

char rx_byte = '0'; // input byte from the serial monitor

int maxStepsX = 14900; //maximum steps towards X direction
int maxStepsY = 10190;  //maximum steps towards Y direction

String inString = "";    // string to hold input
int location[2];
int index = 0;
boolean newData;

void setup() {
  Serial.begin(115200);

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

  pinMode(ledPin, OUTPUT);
  lightOff();

  returnToZero();
}

void loop() {
  
  //listenForCharacter();         // listen for inputs from serial monitor and update it with rx_byte
  readLocation();
  delay(200);
  location[0] = xCorrection(location[0]);
  location[1] = yCorrection(location[1]);
  moveToLocation(location[0],location[1]);
  
   //delay(3000);
}

void readLocation() {
  newData = true;
  while (Serial.available() > 0 && newData == true) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == ',') {
      location[index] = inString.toInt()*10;
      inString = "";
      index += 1;
    }
    if (inChar == '$') {
      location[0] = 0;
      location[1] = 0;
      returnToZero();
    }
    if (inChar == '\n') {
      location[index] = inString.toInt()*10;
//      Serial.print("Value:");
//      Serial.print(location[0]);
//      Serial.print(',');
//      Serial.println(location[1]);
      // clear the string for new input:
      inString = "";
      index = 0;
      newData = false;
    }
  }
}

void returnToZero() {
    moveBackward(20000);
    moveRight(20000);
    
    xErrorCorrection();
    //xStepCount=0;
    //yStepCount=0;
    yErrorCorrection();
    Serial.write("initialposition\n");
}

void moveToLocation(int finalXLocation, int finalYLocation){

  int xDirection = getMovingDirection(xStepCount, finalXLocation);
  int yDirection = getMovingDirection(yStepCount, finalYLocation);
  int stepsX = (finalXLocation - xStepCount)*xDirection;  // no of steps need to be moved in the x direction
  int stepsY = (finalYLocation - yStepCount)*yDirection;  // no of steps need to be moved in the y direction

  if((finalXLocation != xStepCount) || finalYLocation != yStepCount){
//
//  Serial.print("Cordinates:");
//  Serial.print(finalXLocation);
//  Serial.print(",:");
//  Serial.println(finalYLocation);
  
  enableMotor(enablePinX);
  enableMotor(enablePinY);
  digitalWrite(dirPinX, xMovingDirection(xDirection));
  digitalWrite(dirPinY, yMovingDirection(yDirection));
  
  int currentXStep = 0; 
  int currentYStep = 0; 
  boolean reachedX = false;
  boolean reachedY = false;
  
  boolean xLimitSwitchReading;
  boolean yLimitSwitchReading;
      
  while (!(reachedX && reachedY)) {
        xLimitSwitchReading = getXLimitSwitchReading(xDirection);
        yLimitSwitchReading = getYLimitSwitchReading(yDirection);
        
        if(currentXStep < stepsX && xLimitSwitchReading == LOW ){
          digitalWrite(stepPinX, HIGH);
          currentXStep = currentXStep +1;
          xStepCount = xStepCount + xDirection;
        }else if (currentXStep >= stepsX || xLimitSwitchReading == HIGH ){
          digitalWrite(stepPinX, LOW);
          reachedX = true;
          
        } 
          
        if(currentYStep < stepsY && yLimitSwitchReading == LOW){
          digitalWrite(stepPinY, HIGH);
          currentYStep = currentYStep +1;
          yStepCount = yStepCount + yDirection;
        }else if (currentYStep >= stepsY || yLimitSwitchReading == HIGH){
          digitalWrite(stepPinY, LOW);
          reachedY = true;
          
        } 
          delayMicroseconds(stepTime);
          digitalWrite(stepPinX, LOW);
          digitalWrite(stepPinY, LOW);
          delayMicroseconds(stepTime);    

  }
  disableMotor(enablePinX);
  disableMotor(enablePinY);
//  Serial.print("While loop break: ");
//  Serial.print(xStepCount);
//  Serial.print(' ');
//  Serial.println(yStepCount);
  //Serial.print(reachedLimitSwitch(limitSwitchXFront));
  //Serial.print(reachedLimitSwitch(limitSwitchXBack));
  //Serial.print(reachedLimitSwitch(limitSwitchYFront));
 // Serial.print(reachedLimitSwitch(limitSwitchYBack));
  
//  Serial.print('\n');


  if(reachedLimitSwitch(limitSwitchXFront)){
      xErrorCorrection();
      }
  if(reachedLimitSwitch(limitSwitchYFront)){
      yErrorCorrection();
  }
  
  
  delay(1500);
  lightOn();
  delay(1000);
  Serial.write("position\n");
  delay(6000);
  lightOff();
 }
  
}   




boolean xMovingDirection(int directionInt){
    if (directionInt == -1){
      return backwardDirection();
    }else if (directionInt == 1){
      return forwardDirection();
    }
}

boolean yMovingDirection(int directionInt){
    if (directionInt == -1){
      return rightDirection();
    }else if (directionInt == 1){
      return leftDirection();
    }
}


boolean forwardDirection(){return LOW;}
boolean backwardDirection(){return HIGH;}
boolean leftDirection(){return HIGH;}
boolean rightDirection(){return LOW;}


boolean changeMovingDirection(boolean state) {
  state = !state;
  return state;
}
void moveForward(int steps) {
  int currentStep = 0;
  enableMotor(enablePinX);
  digitalWrite(dirPinX, forwardDirection());
  while (reachedLimitSwitch(limitSwitchXBack) == LOW && currentStep <= steps) {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(stepTime);
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(stepTime);    
    currentStep = currentStep + 1;
    xStepCount =xStepCount +1;
    //printStepCount(xStepCount);
  }
  disableMotor(enablePinX);
}

void moveBackward(int steps) {
  enableMotor(enablePinX);
  int currentStep = 0;
  digitalWrite(dirPinX, backwardDirection());
  while (reachedLimitSwitch(limitSwitchXFront) == LOW && currentStep <= steps) {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(stepTime);
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(stepTime);
    currentStep = currentStep + 1;
    xStepCount = xStepCount -1;
    //printStepCount(xStepCount);
  }
  disableMotor(enablePinX);
}

void moveLeft(int steps) {
  enableMotor(enablePinY);
  int currentStep = 0;
  digitalWrite(dirPinY, leftDirection());
  while (reachedLimitSwitch(limitSwitchYBack) == LOW && currentStep <= steps) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(stepTime);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(stepTime);
    currentStep = currentStep + 1;
    yStepCount = yStepCount +1;
    //printStepCount(yStepCount);
  }
  disableMotor(enablePinY);
}

void moveRight(int steps) {
  enableMotor(enablePinY);
  int currentStep = 0;
  digitalWrite(dirPinY, rightDirection());
  while (reachedLimitSwitch(limitSwitchYFront) == LOW && currentStep <= steps) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(stepTime);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(stepTime);
    currentStep = currentStep + 1;
    yStepCount = yStepCount - 1;
    //printStepCount(yStepCount);
  }
  disableMotor(enablePinY);
}


boolean reachedLimitSwitch(int switchPin) {
  boolean switchState = LOW;
  if (digitalRead(switchPin) == LOW) {
    delayMicroseconds(2);
    if (digitalRead(switchPin) == LOW) {
      switchState = HIGH;
    }
  }
  return switchState;
}

void listenForCharacter(){
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();
//    Serial.print(xStepCount);
//    Serial.print(' ');
//    Serial.println(yStepCount);
  }
}

void disableMotor(int pinNumber){
  digitalWrite(pinNumber, LOW); 
}

void enableMotor(int pinNumber){
  digitalWrite(pinNumber, HIGH); 
}

void printStepCount(int steps){
//  Serial.println(steps);
  }




int getMovingDirection(int currentLocation, int finalLocation){
  int movingDirection = 0;
  if (currentLocation <= finalLocation){
    movingDirection = 1;
    }
   if(currentLocation > finalLocation){
    movingDirection = -1;
    }
  return movingDirection;
 }

boolean getXLimitSwitchReading(int movingDirection){
  if(movingDirection == 1){
      return reachedLimitSwitch(limitSwitchXBack);
    }else if(movingDirection == -1){
      return reachedLimitSwitch(limitSwitchXFront);
    }
}

boolean getYLimitSwitchReading(int movingDirection){
  if(movingDirection == 1){
      return reachedLimitSwitch(limitSwitchYBack);
    }else if(movingDirection == -1){
      return reachedLimitSwitch(limitSwitchYFront);
    }
}



void xErrorCorrection(){
  if(xStepCount !=0){
//    Serial.print("X Error Corrected:");
//    Serial.println(xStepCount);
//    Serial.print(reachedLimitSwitch(limitSwitchXFront));
//    Serial.print(" ");
//    Serial.println(reachedLimitSwitch(limitSwitchXBack));
    xStepCount=0;
  }
}

void yErrorCorrection(){
  if(yStepCount !=0){
//    Serial.print("Y Error Corrected:");
//    Serial.println(yStepCount);
//    Serial.print(reachedLimitSwitch(limitSwitchYFront));
//    Serial.print(" ");
//    Serial.println(reachedLimitSwitch(limitSwitchYBack));
    yStepCount=0;
  }
}

int xCorrection(int finalXLocation){
  if (finalXLocation > maxStepsX){
      finalXLocation = maxStepsX;
    }
    return finalXLocation;
}
int yCorrection(int finalYLocation){
  if (finalYLocation > maxStepsY){
      finalYLocation = maxStepsY;
    }
    return finalYLocation;
}

void lightOn(){
  digitalWrite(ledPin, HIGH);
  }

void lightOff(){
  
  digitalWrite(ledPin, LOW);
}

