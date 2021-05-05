#include "mbed.h"

#define ANALOG_IN A1
#define PWM_OUT D3


int val = 0;
float intensity = 0;
mbed::PwmOut pollSensor(digitalPinToPinName(PWM_OUT));

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pollSensor.period(0.01f);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(ANALOG_IN);
  Serial.print("Pot: ");
  Serial.println(val);
//  Serial.print("PWM: ");
//  Serial.println(val/4);
  intensity = ((float)val)/1024;
  Serial.println(intensity);
  pollSensor.write((float)intensity);
}
