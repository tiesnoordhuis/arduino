int measuredResist = 0;
int incomingByte = 0; 
int resistWrite = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  measuredResist = analogRead(A0);

  if (measuredResist < 200) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
  }
  else {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
  }

  if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                if (incomingByte == 97) {
                 digitalWrite(5, HIGH);
                }

                if (incomingByte == 98) {
                  digitalWrite(5, LOW);
                }

                Serial.write(incomingByte);
        }
  if (measuredResist < 255) {
    Serial.write(measuredResist);
  }
  resistWrite = map(measuredResist, 0, 1023, 0, 255);
  Serial.write(resistWrite);
  
  delay(100);
}
