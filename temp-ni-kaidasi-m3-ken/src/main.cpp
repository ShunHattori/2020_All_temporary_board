/*  
 *　9/28動作確認済み
 *　けん-用　買い出しロボット
 */

#include <Arduino.h>
#include "AntiChattering.hpp"
#include "Adafruit_NeoPixel.h"
#include "UNO_PWM_frequency.h"

#define motor1_pwm_launch 128
#define motor2_pwm_launch 128

#define pin1_motor_cw 5
#define pin2_motor_cw 6
#define pin_strip 3
#define pin_function_switch1 2
#define pin_function_switch2 12
#define num_strip 16

AntiChattering input1(pin_function_switch1);
AntiChattering input2(pin_function_switch2);

Adafruit_NeoPixel strip(num_strip, pin_strip, NEO_GRB + NEO_KHZ400);

enum sequence_name
{
  pause,
  launch,
  enumSize,
};

unsigned int walking_state = 0, swording_state = 0;

void update_sequence();
void print_case(String);

void setup()
{
  Serial.begin(256000);
  setPwmFrequencyUNO(pin1_motor_cw, 1);
  setPwmFrequencyUNO(pin2_motor_cw, 1);
  input1.initialize();
  input2.initialize();
  strip.begin();
  strip.setBrightness(255);
  delay(1);
  for (int i = 0; i < num_strip; i++)
  {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
    delay(1);
    strip.show();
    delay(1);
  }
}

void loop()
{
  Serial.println();
  update_sequence();

  switch (walking_state)
  {
  case pause:
    print_case("case:PAUSE");
    analogWrite(pin1_motor_cw, 0);
    break;

  case launch:
    print_case("case:LAUNCH");
    analogWrite(pin1_motor_cw, motor1_pwm_launch);
    break;

  default:
    print_case("#exception");
    break;
  }

  switch (swording_state)
  {
  case pause:
    print_case("case:PAUSE");
    analogWrite(pin2_motor_cw, 0);
    break;

  case launch:
    print_case("case:LAUNCH");
    analogWrite(pin2_motor_cw, motor2_pwm_launch);
    break;

  default:
    print_case("#exception");
    break;
  }
  delay(1);
}

void update_sequence()
{
  input1.update();
  input2.update();
  walking_state = input1.getState();
  swording_state = input2.getState();
}

void print_case(String str_)
{
  Serial.println(str_);
}