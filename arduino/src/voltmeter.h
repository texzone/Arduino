#ifndef VOLTMETER_H
#define VOLTMETER_H

class VoltMeter {
private:
    int volt_pin;
    int amp_pin;
    int arduino_work_voltage;

public:
    VoltMeter(int vp, int ap, int awv = ARDUINO_WORK_VOLTAGE);
    double getVoltReading() const;
    double getAmpReading() const;
};

VoltMeter::VoltMeter(int vp, int ap, int awv) {
    this->volt_pin = vp;
    this->amp_pin = ap;
    this->arduino_work_voltage = awv;
}

double VoltMeter::getVoltReading() const {
    return analogRead(this->volt_pin) * (this->arduino_work_voltage / 1023.0) * 4;
}

double VoltMeter::getAmpReading() const {
    return analogRead(this->amp_pin) * (this->arduino_work_voltage / 1023.0);
}

#endif
