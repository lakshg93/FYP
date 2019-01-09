const int limitSwitchXFront = 4;
const int limitSwitchXBack = 5;
const int limitSwitchYFront = 6;
const int limitSwitchYBack = 7;

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
      Serial.print('1');
      Serial.print('\n');
    }
    else if (reachedLimitSwitch(limitSwitchXBack) == HIGH) {
      Serial.print('2');
      Serial.print('\n');
    }
    else if (reachedLimitSwitch(limitSwitchYFront) == HIGH) {
      Serial.print('3');
      Serial.print('\n');
    } else if (reachedLimitSwitch(limitSwitchYBack) == HIGH) {
      Serial.print('4');
      Serial.print('\n');
    }
  }
}


boolean reachedLimitSwitch(int switchPin) {
  if (digitalRead(switchPin) == LOW) {
    return HIGH;
  }
  else {
    return LOW;
  }
}

void listenForCharacter() {
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();
  }
}
