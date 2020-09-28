/*  
 *　9/28動作確認済み
 *　西田-用　バズーカ、ガトリングロボット
 */

#include <Arduino.h>
#include <Servo.h>
#include "AntiChattering.hpp"
#include "Observer.hpp"
#include "Adafruit_NeoPixel.h"
#include "UNO_PWM_frequency.h"

#define servo_angle_launch 180
#define servo_angle_reset 0

#define pwm_motor 200

#define pin_servo 11
#define pin_strip 4
#define pin_motor1_cw 2
#define pin_motor1_ccw 3
#define pin_function_switch 22

#define num_strip 12

Servo servo1;
AntiChattering input(pin_function_switch);
Observer<bool> sequenceListener;
Adafruit_NeoPixel strip(num_strip, pin_strip, NEO_GRB + NEO_KHZ400);

enum sequence_name
{
  pause,
  launch,
  enumSize,
};

unsigned int sequence_number = 0;

void update_sequence();
void print_case(String);

void setup()
{
  Serial.begin(256000);
  setPwmFrequencyUNO(pin_motor1_cw, 1);
  setPwmFrequencyUNO(pin_motor1_ccw, 1);
  input.initialize();
  servo1.attach(pin_servo);
  strip.begin();
  strip.setBrightness(100);
  for (int i = 0; i < num_strip; i++)
  {
    strip.setPixelColor(i, strip.Color(150, 150, 150));
    delay(1);
    strip.show();
    delay(1);
  }
}

void loop()
{
  update_sequence();

  switch (sequence_number)
  {
  case pause:
    print_case("case:PAUSE");
    servo1.write(servo_angle_reset);
    analogWrite(pin_motor1_cw, 0);
    analogWrite(pin_motor1_ccw, 0);
    break;

  case launch:
    print_case("case:LAUNCH");
    servo1.write(servo_angle_launch);
    analogWrite(pin_motor1_cw, pwm_motor);
    analogWrite(pin_motor1_ccw, 0);
    break;

  default:
    sequence_number = pause;
    print_case("#exception");
    break;
  }
  delay(1);
}

void update_sequence()
{
  input.update();
  if (sequenceListener.isChanged(input.getState()) && input.getState() == HIGH)
    sequence_number++;
}

void print_case(String str_)
{
  Serial.println(str_);
}