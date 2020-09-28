/*
 *  低レイヤーでの初期設定の干渉問題：チェック済み
 */

#pragma once

#include <Arduino.h>
#include <Servo.h>
#include "../lib/ComponentPropaties.hpp"

class ServoDriver
{
private:
    Servo SERVO;
    ServoPropaties SERVO_PROPS;

public:
    ServoDriver() = delete;
    ServoDriver(ServoPropaties);
    virtual ~ServoDriver() {}

    void initialize();
    void setAngle(int16_t);
    int8_t getAngle();
};

inline ServoDriver::ServoDriver(ServoPropaties SERVO_PROPS_) : SERVO_PROPS(SERVO_PROPS_){};

inline void ServoDriver::initialize()
{
    SERVO.attach(SERVO_PROPS.pin);
}

inline void ServoDriver::setAngle(int16_t angle)
{
    SERVO.write(angle);
    return;
}

inline int8_t ServoDriver::getAngle()
{
    return SERVO.read();
}

extern ServoDriver servo1;
extern ServoDriver servo2;
extern ServoDriver servo3;
extern ServoDriver servo4;