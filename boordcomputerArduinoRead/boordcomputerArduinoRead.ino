int incomingByte = 0;   // for incoming serial data

int wwCheck = 0;

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {

        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                if (incomingByte == 97) {
                  wwCheck = 1;
                }

                // say what you got:
                Serial.write(1);
                Serial.write(incomingByte);
        }

        if (wwCheck == 1) {
        int potentiometer = analogRead(A0);                  // read the input pin
        int mappedPot = map(potentiometer, 0, 1023, 0, 255); // remap the pot value to fit in 1 byte
        Serial.write(mappedPot);                             // print it out the serial port
        delay(1);                                            // slight delay to stabilize the ADC
        }
}
 
