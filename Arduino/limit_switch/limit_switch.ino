const int limit_switch = 10;
void setup() {
Serial.begin(9600);
  pinMode(limit_switch,INPUT);
  pinMode (13, OUTPUT);

  digitalWrite (13, LOW);
}

void loop() {
  if (1){
    Serial.write('1');
    digitalWrite (13, HIGH);
    
  }else{
      Serial.write('0');
      digitalWrite (13, LOW);
    }

    Serial.write('\n');

}
