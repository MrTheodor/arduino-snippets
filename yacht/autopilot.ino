// Yacht autopilot
// Copyright jkrajniak@gmail.com (Jakub Krajniak)
// 
// It is a very simple piece of code for the Arduino Uno board.
// The idea is to read from the serial port the NMEA $GPRMB sentence
// (http://aprs.gids.nl/nmea/#rmb) and set the appropriate signal on the
// pins. 
// eg1. $GPRMB,A,0.66,L,003,004,4917.24,N,12309.57,W,001.3,052.5,000.5,V*0B
// 
// 

String inputString = "";   // a string to hold incoming data
String groupString = "";
boolean stringComplete = false;  // whether the string is complete
#define LED_L 8
#define LED_R 9
float cerr = 0.0;
int steerCounter = 0;
int counter = 10;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  pinMode(LED_L, OUTPUT);
  pinMode(LED_R, OUTPUT);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    int stringLength = inputString.length();
    int idx = 0;
    int group = 0;
    groupString = "";
    for (idx=0; idx<stringLength; idx++) {
      if (inputString[idx] == ',') { // next group
        if (group == 2) { // check if it is a group 2
          char buf[groupString.length() + 1];
          groupString.toCharArray(buf, sizeof(buf));
          cerr = atof(buf); 
          groupString = "";
        }
        group++;
      } else {
        // group 3, 
        if (group == 3) { 
          boolean change = false;
          // output reset
          digitalWrite(LED_L, LOW);
          digitalWrite(LED_R, LOW);
          // if we are close to the path then we don't send the signal
          if (cerr < 0.02 && steerCounter % counter != 0) {
            steerCounter++;
            continue;
          }
          
          if (inputString[idx] == 'L') {
            digitalWrite(LED_L, HIGH);
          } else {
            digitalWrite(LED_R, HIGH);
          }
          steerCounter++;
          cerr = 0.0;
        } else if (group == 2) {
          groupString += inputString[idx];
        }
      }
    } 
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}
