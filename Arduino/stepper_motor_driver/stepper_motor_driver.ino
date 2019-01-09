const int stepPin = 8; //clk
const int dirPin = 9; //CW
const int enPin = 13;


char rx_byte = '0';
void setup() {
  Serial.begin(9600);
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
 
 
}
void loop() {
if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();
}
if(rx_byte == '1'){    
  digitalWrite(dirPin,HIGH);     //  anticlockwise direction
  for(int x = 0; x < 2000; x++) 
  
  {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  }
 //delay(1000); // One second delay
}
if(rx_byte == '2'){  
  digitalWrite(dirPin,LOW);    // clockwise driection
  for(int x = 0; x < 2000; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  }
  //delay(1000);
 }
}
