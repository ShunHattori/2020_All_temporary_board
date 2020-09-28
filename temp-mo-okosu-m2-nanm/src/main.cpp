/*  
 *　9/28動作確認済み
 *　なんみん-用　起こすロボット
 */

#include <Arduino.h>
#include "AntiChattering.hpp"
#include "Adafruit_NeoPixel.h"
#include "UNO_PWM_frequency.h"

#define motor_pwm_launch 128

#define pin_motor_cw 5
#define pin_strip 6
#define pin_function_switch 3
#define num_strip 16

AntiChattering input(pin_function_switch);
Adafruit_NeoPixel strip(num_strip, pin_strip, NEO_GRB + NEO_KHZ400);

enum sequence_name
{
  pause,
  launch,
  enumSize,
};

unsigned int running_state = 0;

void update_sequence();
void print_case(String);

void setup()
{
  Serial.begin(256000);
  setPwmFrequencyUNO(pin_motor_cw, 1);
  input.initialize();
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
  update_sequence();

  switch (running_state)
  {
  case pause:
    print_case("case:PAUSE");
    analogWrite(pin_motor_cw, 0);
    break;

  case launch:
    print_case("case:LAUNCH");
    analogWrite(pin_motor_cw, motor_pwm_launch);
    break;

  default:
    print_case("#exception");
    break;
  }
  delay(1);
}

void update_sequence()
{
  input.update();
  running_state = input.getState();
}

void print_case(String str_)
{
  Serial.println(str_);
}