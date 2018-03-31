/*
Serial write example

Sends a byte to a webSocket server which sends the same byte
out through a serial port.

You can use this with the included Arduino example called PhysicalPixel.
Works with P5 editor as the socket/serial server, version 0.5.5 or later.

written 2 Oct 2015
by Tom Igoe
*/

// Declare a "SerialPort" object
var serial;
// fill in the name of your serial port here:
var portName = "COM3";

// setup om om de zoveel tijd hoogste waarde te resetten
var maxValueReset = 0;
var maxValue = 0;
var maxAvgReset = 0;
var maxAvg = 0;
var averageString = [0,0,0,0,0];
var averageN = averageString.length;
var averageValue = 0;

function setup() {
  // make an instance of the SerialPort object
  serial = new p5.SerialPort();

  // Get a list the ports available
  // You should have a callback defined to see the results. See gotList, below:
  serial.list();

  // Assuming our Arduino is connected,  open the connection to it
  serial.open(portName);

  // When you get a list of serial ports that are available
  serial.on('list', gotList);

  // When you some data from the serial port
  serial.on('data', gotData);
}


// Got the list of ports
function gotList(thelist) {
  console.log("List of Serial Ports:");
  // theList is an array of their names
  for (var i = 0; i < thelist.length; i++) {
    // Display in the console
    console.log(i + " " + thelist[i]);
  }
}

// Called when there is data available from the serial port
function gotData() {
  var currentString = serial.read();
  document.getElementById("display1").innerHTML = currentString;
  updateMax(currentString);
  updateAverage(currentString);
}

function updateMax(currentValue) {
  maxValueReset ++
  if (maxValueReset > 100) {
    maxValueReset = 0;
    maxValue = 0;
    document.getElementById("display2").innerHTML = maxValue;
  } else {
    if (currentValue > maxValue) {
      maxValue = currentValue
      document.getElementById("display2").innerHTML = maxValue;
      maxValueReset = 0;
    }
  }
}

function updateAverage(currentValue) {
  for (var i = 0; i < (averageString.length - 1); i++) {
    averageString[i] = averageString[(i + 1)];
  }
  averageString[(averageN - 1)] = currentValue;
  averageValue = 0;
  for (var i = 0; i < averageString.length; i++) {
    averageValue += averageString[i];
  }
  averageValue = (averageValue/averageN);
  document.getElementById("display3").innerHTML = averageValue;
  updateAvgMax(averageValue);
}

function updateAvgMax(averageValue) {
  maxAvgReset ++
  if (maxAvgReset > 100) {
    maxAvgReset = 0;
    maxAvg = 0;
    document.getElementById("display4").innerHTML = maxAvg;
  } else {
    if (averageValue > maxAvg) {
      maxAvg = averageValue
      document.getElementById("display4").innerHTML = maxAvg;
      if (maxAvg > 150) {
        console.log("connected");
        document.getElementById("inputDom").value = "succes";
        arduinoConnectSucces();
      }
      maxAvgReset = 0;
    }
  }
}

function arduinoConnectSucces() {
  document.getElementById("step3DivMain").style.display = "none";
  document.getElementById("step4DivMain").style.display = "block";
}

// When you click on the screen, the server sends H or L out the serial port
function mouseReleased() {
  outMessage = document.getElementById("inputDom").value;
  serial.write(outMessage);
}
