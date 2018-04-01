// include the Servo library
#include <Servo.h>

Servo myServo;  // create a servo object

int servoInput;
int measuredResist = 0;
int incomingByte = 0;
int resistWrite = 0;
int servoActive = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  myServo.attach(9); // attaches the servo on pin 9 to the servo object

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
                  if (servoActive == 0) {
                    digitalWrite(5, HIGH);
                    servoActive = 1;
                  }
                }

                if (incomingByte == 98) {
                  digitalWrite(5, LOW);
                  servoActive = 0;
                }

                if (servoActive == 1) {
                  servoInput = map(incomingByte, 100, 279, 0, 179);
                  Serial.write(servoInput);
                  if (servoInput > 179) {
                    servoInput = 0;
                  }
                  // set the servo position
                  myServo.write(servoInput);
                }

                Serial.write(incomingByte);
        }
  resistWrite = map(measuredResist, 0, 1023, 0, 255);
  if (servoActive == 0) {
    Serial.write(resistWrite);
  }

  delay(100);
}
