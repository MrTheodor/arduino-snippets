//http://arduino.cc/en/Tutorial/PWM

int output = 6;
int delayValue = 10;


void setup()  {
  randomSeed(analogRead(0));
} 

void loop()  { 
  analogWrite(output, random(255));
  delay(delayValue);
}
