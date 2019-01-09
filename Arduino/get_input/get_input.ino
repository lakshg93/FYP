String inString = "";    // string to hold input
int location[2];
int index = 0;
boolean newData;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
}

void loop() {
  readLocation();
}
void readLocation(){
  newData = true;
  while (Serial.available() > 0 && newData == true) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == ','){
        location[index] = inString.toInt();
        inString = "";
        index +=1;
      }
    if (inChar == '\n') {
      location[index] = inString.toInt();
      Serial.print("Value:");
      Serial.print(location[0]);
      Serial.print(',');
      Serial.println(location[1]);
      // clear the string for new input:
      inString = "";
      index = 0;
      newData = false;
    }
  }
}


