// Copyright jkrajniak@gmail.com (Jakub Krajniak)
// Generate the half of the sin function on the output
// with some random noice on the top.
// 
//http://arduino.cc/en/Tutorial/PWM

int output = 6;
int delayValue = 10;
float noiseLevel = 0.9; // from 0.0 to 1.0

float sinVal;
float ledVal;
int randomMax;

void setup()  {
  randomSeed(analogRead(0));
  randomMax = int(noiseLevel * 255);
} 

void loop()  { 
  for (int x=0; x < 180; x++){
    sinVal = sin(radians(x));
    ledVal = sinVal*(255-radomMax) + sinVal*random(randomMax);
    ledVal = map(ledVal, 0, 255, 0, 100);
    analogWrite(output, ledVal);
    delay(delayValue);
  }
}


