const int stepPin = 9; //clk
const int dirPin = 8; //CW
const int enPin = 13;

const int limit_switch = 7;

long stepCount = 0;
char rx_byte = '0';

boolean state = HIGH;



void setup() {
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
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

  if(rx_byte == '1'){

    if (digitalRead(limit_switch) == LOW){
      state = !state;
      Serial.print(state);
      digitalWrite(dirPin, state);
      Serial.print(stepCount);
      stepCount = 0;
      Serial.print('\n');
      delay (3000);
      }
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);

      stepCount = stepCount + 1;
    //delay(1000); // One second delay

}
}
