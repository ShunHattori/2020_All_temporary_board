/*
 *  低レイヤーでの初期設定の干渉問題：チェック済み
 */

#pragma once

#include "../lib/pinInitializer.hpp"
#include "../lib/MechanismTask.hpp"

class Robot
{
private:
    MechanismTask &m_task;

public:
    Robot() = delete;
    Robot(MechanismTask &);
    virtual ~Robot() {}

    void initialize();
    uint8_t work();
    static void debugPrint();
};

inline Robot::Robot(MechanismTask &m_task_) : m_task(m_task_){};

inline void Robot::initialize()
{
    Serial.begin(256000);
    Serial.println("boot");
    pin_initialize();
    m_task.initialize();
    return;
}

inline uint8_t Robot::work()
{
    m_task.work();
    return 0;
}

inline void Robot::debugPrint()
{
    Serial.print(switch_i1.getState());
    Serial.print(',');
    Serial.print(switch_i2.getState());
    Serial.print(',');
    Serial.print(switch_i3.getState());
    Serial.print(',');
    Serial.print(switch_i4.getState());
    Serial.print(',');
    Serial.print(switch_i5.getState());
    Serial.print(',');
    Serial.print(switch_i6.getState());
    Serial.print(',');
    Serial.print(switch_m1.getState());
    Serial.print(',');
    Serial.print(switch_m2.getState());
    Serial.print(',');
    Serial.print(switch_m3.getState());
    Serial.print(',');
    Serial.print(switch_m4.getState());
    Serial.print(',');
    Serial.print(switch_m5.getState());
    Serial.print(',');
    Serial.print(switch_m6.getState());
    Serial.print(',');
    Serial.print('\t');
    Serial.print(analog_in1.getValue());
    Serial.print('\t');
    Serial.print(analog_in2.getValue());
    Serial.print("\r\n");
}