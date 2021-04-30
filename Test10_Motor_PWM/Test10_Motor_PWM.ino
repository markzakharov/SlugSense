#include "mbed.h"

#define ANALOG_IN A2
#define PWM_OUT 3
#define REF_PIN 10

int val = 0;

mbed::PwmOut pollSensor(digitalPinToPinName(PWM_OUT));

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(REF_PIN, OUTPUT);
  pollSensor.period(0.001f);
  digitalWrite(REF_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = (double)analogRead(ANALOG_IN);
  Serial.print("Pot: ");
  Serial.println(val);
//  Serial.print("PWM: ");
//  Serial.println(val/4);
  pollSensor.write(val/1024.0);
}
