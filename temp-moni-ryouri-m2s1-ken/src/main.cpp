#include <Arduino.h>

#include "../lib/MechanismTask.hpp"
#include "../lib/RobotFlagList.hpp"
#include "../lib/Robot.hpp"
#include "../lib/AntiChattering.hpp"
#include "../lib/ComponentPropaties.hpp"
#include "../lib/AnalogIn.hpp"
#include "../lib/MotorDriver.hpp"
#include "../lib/ServoDriver.hpp"
#include "../lib/pinInitializer.hpp"
#include "../lib/Adafruit_NeoPixel.h"

FlagSet robot_flags;
MechanismTask robot_mechanism(robot_flags);
Robot obasan_1_gouki(robot_mechanism);

void setup()
{
  obasan_1_gouki.initialize();
}

void loop()
{
  obasan_1_gouki.work();
  //Robot::debugPrint();
}