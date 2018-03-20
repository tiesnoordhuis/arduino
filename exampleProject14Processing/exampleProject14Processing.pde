import processing.serial.*;

// The serial port:
Serial myPort;

PImage logo;
int bgcolor = 0;
void setup() {
  colorMode(HSB, 255);
  logo = loadImage("logo.png");
  size(170, 116);
  // List all the available serial ports:
  println("Available serial ports: ");
  println(Serial.list());

  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[1], 9600);
}

void draw() {
  if (myPort.available() > 0) {
    bgcolor = myPort.read();
    println(bgcolor);
  }
  background(bgcolor, 255, 255);
  image(logo, 0, 0);
}
