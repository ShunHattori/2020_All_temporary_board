#include "../lib/MechanismTask.hpp"
#include "../lib/GeneralCalc.hpp"

MotorDriver motor1(MOTOR1_PROPS);
MotorDriver motor2(MOTOR2_PROPS);
MotorDriver motor3(MOTOR3_PROPS);
MotorDriver motor4(MOTOR4_PROPS);
ServoDriver servo1(SERVO1_PROPS);
ServoDriver servo2(SERVO2_PROPS);
ServoDriver servo3(SERVO3_PROPS);
ServoDriver servo4(SERVO4_PROPS);
AntiChattering switch_i1(SWITCH_ITFC1_PROPS);
AntiChattering switch_i2(SWITCH_ITFC2_PROPS);
AntiChattering switch_i3(SWITCH_ITFC3_PROPS);
AntiChattering switch_i4(SWITCH_ITFC4_PROPS);
AntiChattering switch_i5(SWITCH_ITFC5_PROPS);
AntiChattering switch_i6(SWITCH_ITFC6_PROPS);
AntiChattering switch_m1(SWITCH_MACH1_PROPS);
AntiChattering switch_m2(SWITCH_MACH2_PROPS);
AntiChattering switch_m3(SWITCH_MACH3_PROPS);
AntiChattering switch_m4(SWITCH_MACH4_PROPS);
AntiChattering switch_m5(SWITCH_MACH5_PROPS);
AntiChattering switch_m6(SWITCH_MACH6_PROPS);
AnalogIn analog_in1(ANALOGIN1_PROPS);
AnalogIn analog_in2(ANALOGIN2_PROPS);

void MechanismTask::work()
{
    updateSwitchInputs();

    /*----TASKS HERE----*/
    //ポテンショメーター　正面→980
    //サーボデフォ 90deg
    constexpr int16_t motor1_pwm = 250,
                      servo4_angle = 0,
                      pot_origin = 932,
                      pot_target = 860,
                      pot_acc_error = 8;

    converger1.update();

    switch (sequence_num)
    {
    case pause:
        // Serial.println("sequence -> pause : signal awaiting, initialize");

        if (waitMs(200))
        {
            Serial.print("target:");
            Serial.print(pot_origin);
            Serial.print('\t');
            Serial.print("current:");
            Serial.print(analog_in1.getValue());
            Serial.print('\t');
            Serial.print("error:");
            Serial.print(pot_acc_error);
            Serial.print('\t');
            Serial.print("output(conv):");
            Serial.println(converger1.getPwm());
        }

        servo4.setAngle(90);
        motor1.set_pwm(0);

        converger1.setTarget(pot_origin);
        converger1.setCurrent(analog_in1.getValue());
        converger1.update();
        motor3.set_pwm(converger1.getPwm());
        if (is_near_by(analog_in1.getValue(), pot_origin, pot_acc_error))
            motor3.set_pwm(0);
        break;

    case hand_cooking:
        Serial.print("sequence -> hand_cooking : set motor1 pwm to ");
        Serial.println(motor1_pwm);
        motor1.set_pwm(motor1_pwm);
        break;

    case stop_cooking_and_set_neck:
        // run motor3(neck) it goes next phase
        if (waitMs(500))
        {
            Serial.println("sequence -> stop_cooking : signal awaiting..");
        }

        if (switch_m1.getState())
        {
            Serial.print("sequence -> stop_cooking : switch signal interact, set motor1 pwm to 0");
            Serial.println(", activated conveger1");
            motor1.set_pwm(0);
            converger1.setTarget(pot_target);
            sequence_num = neck_conveting;
        }
        break;

    case neck_conveting:
        //stop the motor when pot is 1/4 rotated

        if (waitMs(200))
        {
            Serial.print("target:");
            Serial.print(pot_target);
            Serial.print('\t');
            Serial.print("current:");
            Serial.print(analog_in1.getValue());
            Serial.print('\t');
            Serial.print("error:");
            Serial.print(pot_acc_error);
            Serial.print('\t');
            Serial.print("output(conv):");
            Serial.println(converger1.getPwm());
        }

        converger1.setCurrent(analog_in1.getValue());
        motor3.set_pwm(converger1.getPwm());
        // if (is_near_by(analog_in1.getValue(), pot_target, pot_acc_error))
        // {
        //     motor3.set_pwm(0);
        //     sequence_num = shoot_eggs;
        // }
        break;

    case shoot_eggs:
        // shoot the egg
        Serial.println("sequence -> shoot eggs:running servo");
        servo4.setAngle(servo4_angle);
        delay(2000);
        sequence_num = initialize_for_next;
        break;

    case initialize_for_next:
        //initialize for next launch
        Serial.println("sequence -> initializing..");
        sequence_num = pause;
        break;
    default:
        sequence_num = pause;
        Serial.println("#exception");
        break;
    }

    /*----TASKS HERE----*/

    /*
     *  processing at the bottom of tasks
     */
    update_sequence();
    apply_emergency_state();
    apply_pwms();
}

void MechanismTask::update_sequence()
{
    if (sequence_num == stop_cooking_and_set_neck ||
        sequence_num == neck_conveting ||
        sequence_num == shoot_eggs ||
        sequence_num == initialize_for_next)
        return;

    switch_m2.update();
    if (obs1.isChanged(switch_m2.getState()) && switch_m2.getState() == HIGH)
        sequence_num++;
}
