int pinOut = 3;
char rx_byte = '0';

void setup() {
  Serial.begin(9600);
  pinMode(pinOut, OUTPUT);
  //digitalWrite(pinOut, LOW);
}

void loop() {             
  listenForCharacter();
  if (rx_byte == '1'){
    digitalWrite(pinOut, LOW);
   // pinMode(pinOut,INPUT);
    Serial.println('1');
  }else if(rx_byte == '2') {
    //pinMode(pinOut,OUTPUT);
    digitalWrite(pinOut, HIGH);
    Serial.println('2');
  }
  delay(500);            
}

void listenForCharacter() {
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();
  }
}
