#include "motor.h"
#include "irsensor.h"
#include <Arduino.h>

#ifndef ACTION_H
#define ACTION_H

class Action {
private:
    Motor motorToBeMoved;
    IrSensor limitor;
    uint8_t *direction;

public:
    Action(Motor m, IrSensor l, uint8_t direction[2]);
    void execute(int speed = 0, bool immediate = false, bool movement = true);
    bool operator==(const Action &rhs) const;
    bool operator!=(const Action &rhs) const;
};

bool Action::operator==(const Action &rhs) const {
    return motorToBeMoved == rhs.motorToBeMoved &&
           limitor == rhs.limitor &&
           direction == rhs.direction;
}

bool Action::operator!=(const Action &rhs) const {
    return !(rhs == *this);
}

Action::Action(Motor m, IrSensor l, uint8_t dir[2])
{
    this->motorToBeMoved = m;
    this->limitor = l;
    this->direction = dir;
}

void Action::execute(int speed, bool immediate, bool movement) {
    this->motorToBeMoved.move(this->direction, speed, immediate);

    if (movement && this->limitor.getState() == IR_SENSOR_REACHED) {
        this->motorToBeMoved.move(this->direction, STOP, true);
    }
}

#endif
