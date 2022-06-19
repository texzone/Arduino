#include <Arduino.h>

#ifndef MOTOR_H
#define MOTOR_H

class Motor {
private:
    int clockwise_pin;
    int counterc_pin;
    int en_pin;

public:
    Motor() { clockwise_pin = 0; counterc_pin = 0; en_pin = 0;};
    Motor(int in1pin, int in2pin, int enpin);
    void move(uint8_t direction[2], int speed = 0, bool immediate = false) const;
    bool operator==(const Motor &rhs) const;
    bool operator!=(const Motor &rhs) const;
};

/**
 * Constructor for Motor class.
 * @param in1pin                The pin that controls the clockwise movement when HIGH is written to it.
 * @param in2pin                The pin that controls the counter-clockwise movement when HIGH is written to it.
 * @param enpin                 No idea tbh.
 */
Motor::Motor(int in1pin, int in2pin, int enpin) {
    clockwise_pin = in1pin;
    counterc_pin = in2pin;
    en_pin = enpin;

    pinMode(clockwise_pin, OUTPUT);
    pinMode(counterc_pin, OUTPUT);
    pinMode(en_pin, OUTPUT);
}

bool Motor::operator==(const Motor &rhs) const {
    return clockwise_pin == rhs.clockwise_pin &&
           counterc_pin == rhs.counterc_pin &&
           en_pin == rhs.en_pin;
}

bool Motor::operator!=(const Motor &rhs) const {
    return !(rhs == *this);
}

/**
 * Function will move the motor in a given direction (clockwise or counter-clockwise).
 * @param direction             An array of size 2 with the values {HIGH, LOW}. The first array element
 *                              will be assigned to the clockwise pin; the second to the counter-clockwise
 *                              pin. If the motor should move clockwise, pass [HIGH, LOW]. If counterclockwise,
 *                              pass [LOW, HIGH].
 * @param speed                 An optional parameter to provide a maximum speed. Defaults at 0.
 * @param immediate             An optional parameter that will set the speed of the motor to the speed passed
 *                              instantly, rather than create a buildup to said speed. If an `immediate` flag is
 *                              passed but no speed is passed with it, it will stop the motor, since speed will be
 *                              set to zero.
 */
void Motor::move(uint8_t direction[2], int speed, bool immediate) const {
    digitalWrite(clockwise_pin, direction[0]); // control motor A spins clockwise
    digitalWrite(counterc_pin, direction[1]);  // control motor A spins clockwise

    // When stopping the motor, it should probably be an immediate stop, since it would be undesirable
    // for a collision. The composition of this ensures that any stops are immediate stops.
    if (immediate) {
        analogWrite(en_pin, speed);
    } else {
        for (speed = 0; speed <= 255; speed++) {
            analogWrite(en_pin, speed); // control the speed
            delay(10);
        }
    }
}

#endif
