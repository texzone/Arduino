#include <Arduino.h>

#ifndef IRSENSOR_H
#define IRSENSOR_H

class IrSensor {
private:
    int ir_pin;

public:
    IrSensor() { ir_pin = 0; }
    explicit IrSensor(int pin);
    int getState() const;
};

IrSensor::IrSensor(int pin) {
    ir_pin = pin;
    pinMode(ir_pin, INPUT);
}

int IrSensor::getState() const {
    return digitalRead(ir_pin);
}


#endif