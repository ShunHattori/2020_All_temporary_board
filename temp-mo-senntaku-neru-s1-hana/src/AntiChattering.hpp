#pragma once
#include <Arduino.h>

/*
 *  Anti-chatter read for AVR controller
 *  ハードウェアコーディング用機能縮小版
 */

class AntiChattering
{
private:
  uint64_t sampled_time;
  uint16_t pin, detect_flag_number, sampling_period, button_press_count;
  bool button_state;
  void digitalProcess();
  void setStateFlag();

public:
  AntiChattering() = delete;
  AntiChattering(int);
  void initialize();
  void update();
  void setDetectCount(int);
  void setButtonState(bool);
  bool getState();

  virtual ~AntiChattering(){};
};

extern AntiChattering switch_1;
extern AntiChattering switch_2;
extern AntiChattering switch_3;
extern AntiChattering switch_4;
extern AntiChattering switch_5;
extern AntiChattering switch_6;
extern AntiChattering switch_7;
extern AntiChattering switch_8;
extern AntiChattering switch_9;
extern AntiChattering switch_10;

AntiChattering::AntiChattering(int pin_)
    : pin(pin_),
      detect_flag_number(3),
      sampling_period(5),
      button_state(0){};

void AntiChattering::initialize()
{
  sampled_time = millis();
  pinMode(pin, INPUT);
}

void AntiChattering::update()
{
  digitalProcess();
  setStateFlag();
  return;
}

void AntiChattering::digitalProcess()
{

  if (sampling_period < (millis() - sampled_time))
  {
    if (digitalRead(pin))
      button_press_count++;
    else
      button_press_count = 0;
    sampled_time = millis();
  }
}

void AntiChattering::setStateFlag()
{
  if (detect_flag_number < button_press_count)
    button_state = 1;
  else
    button_state = 0;
}

void AntiChattering::setDetectCount(int count)
{
  detect_flag_number = count;
}
void AntiChattering::setButtonState(bool state)
{
  button_state = state;
}

bool AntiChattering::getState()
{
  return button_state;
}
