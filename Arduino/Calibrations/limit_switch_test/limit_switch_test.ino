const int limitSwitchXFront = 7;
const int limitSwitchXBack = 6;
const int limitSwitchYFront = 4;
const int limitSwitchYBack = 5;

char rx_byte = '0';

void setup() {
  Serial.begin(9600);

  pinMode(limitSwitchXFront, INPUT);
  pinMode(limitSwitchXBack, INPUT);
  pinMode(limitSwitchYFront, INPUT);
  pinMode(limitSwitchYBack, INPUT);
}

void loop() {
  listenForCharacter();         // listen for inputs from serial monitor and update it with rx_byte
  if (rx_byte = '1') {
    if (reachedLimitSwitch(limitSwitchXFront) == HIGH) {
      Serial.println('1');
      }else if (reachedLimitSwitch(limitSwitchXBack) == HIGH) {
      Serial.println('2');
      }else if (reachedLimitSwitch(limitSwitchYFront) == HIGH) {
      Serial.println('3');
    } else if (reachedLimitSwitch(limitSwitchYBack) == HIGH){
      Serial.println('4');
    }
}
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

void listenForCharacter() {
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();
  }
}
