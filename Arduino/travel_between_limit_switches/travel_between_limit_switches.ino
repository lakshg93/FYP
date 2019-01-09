const int stepPin = 9; //clk
const int dirPin = 8; //CW
//const int enPin = 13;

const int limit_switch_front = 4;
const int limit_switch_back = 5;

long stepCount = 0;
char rx_byte = '0';

boolean state = HIGH;



void setup() {
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(limit_switch_front, INPUT);
  pinMode(limit_switch_back, INPUT);

  // pinMode(enPin, OUTPUT);
  //digitalWrite(enPin, LOW);
  digitalWrite(dirPin, state);

  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
}
void loop() {

  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();
    Serial.print(stepCount);
    Serial.print('\n');
    stepCount = 0;
  }

  if (rx_byte == '1') {

    if (digitalRead(limit_switch_front) == LOW && digitalRead(limit_switch_back) == HIGH) {
      state = LOW;

      Serial.print(state);
      Serial.print(' ');
      digitalWrite(dirPin, state);
      Serial.print(stepCount);
      stepCount = 0;
      Serial.print('\n');
      //delay ();
    } 
    else if(digitalRead(limit_switch_front) == HIGH && digitalRead(limit_switch_back) == LOW) {

      state = HIGH;

      Serial.print(state);
      Serial.print(' ');
      digitalWrite(dirPin, state);
      Serial.print(stepCount);
      stepCount = 0;
      Serial.print('\n');
      //delay (3000);

    }

    moving(stepPin,500);      //move one step cycle
    stepCount = stepCount + 1;
    //delay(1000); // One second delay

  }
}




