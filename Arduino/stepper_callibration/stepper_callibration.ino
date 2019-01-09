const int stepPin = 9; //clk
const int dirPin = 8; //CW
const int enPin = 13;

long stepCount = 0;
char rx_byte = '0';

void setup() {
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

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
    digitalWrite(dirPin, HIGH);    //  anticlockwise direction
    for (int x = 0; x < 800; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);

      stepCount = stepCount + 1;
    }
    //delay(1000); // One second delay
  }
  if (rx_byte == '2') {
    digitalWrite(dirPin, LOW);   // clockwise driection
    for (int x = 0; x < 800; x++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
      stepCount = stepCount + 1;
    }
    //delay(1000);
  }
}
