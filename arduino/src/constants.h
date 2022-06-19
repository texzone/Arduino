#include <Arduino.h>

/////////////// VOLTAGE METER SENSOR SETEUP ///////////////

#define VT_PIN1 A0 // connect VT
#define AT_PIN1 A1 // connect AT
#define VT_PIN2 A2 // connect VT
#define AT_PIN2 A3 // connect AT

#define ARDUINO_WORK_VOLTAGE 5.0

/////////////// IR SENSOR SETEUP ///////////////

const int AT_REST_IR_SENSOR_1_PIN = 22; // connect ir sensor to arduino pin 3
const int MAX_UPWARD_IR_SENSOR_2_PIN = 24; // connect ir sensor to arduino pin 3
const int MAX_DOWNWARD_IR_SENSOR_3_PIN = 26; // connect ir sensor to arduino pin 3
const int AT_FIRST_SOLAR_PANEL_IR_SENSOR_4_PIN = 28; // connect ir sensor to arduino pin 3
const int AT_SECOND_SOLAR_PANEL_IR_SENSOR_5_PIN = 30; // connect ir sensor to arduino pin 3

/////////////// LEFT AND RIGHT MOTORS ///////////////
const int FRAME_MOVEMENT_EN_PIN_10 = 10; // the Arduino pin connected to the EN1 pin L298N
const int FRAME_MOVEMENT_IN_PIN_9 = 9; // the Arduino pin connected to the IN1 pin L298N (HIGH)
const int FRAME_MOVEMENT_IN_PIN_8 = 8; // the Arduino pin connected to the IN2 pin L298N (LOW)

/////////////// BRUSH ROTATION MOTORS ///////////////
const int BRUSH_ROTATION_MOTOR_EN_PIN_4 = 4; // the Arduino pin connected to the EN1 pin L298N
const int BRUSH_ROTATION_MOTOR_IN_PIN_3 = 3; // the Arduino pin connected to the IN1 pin L298N (LOW)
const int BRUSH_ROTATION_MOTOR_IN_PIN_2 = 2; // the Arduino pin connected to the IN2 pin L298N (HIGH)

/////////////// UP AND DOWN MOTORS ///////////////
const int BRUSH_MOVEMENT_EN_PIN_7 = 7; // the Arduino pin connected to the EN1 pin L298N
const int BRUSH_MOVEMENT_IN_PIN_6 = 6; // the Arduino pin connected to the IN1 pin L298N (HIGH)
const int BRUSH_MOVEMENT_IN_PIN_5 = 5; // the Arduino pin connected to the IN2 pin L298N (LOW)

/////////////// SPEEDS ///////////////
const int MAX_SPEED = 255;
const int STOP = 0;

/////////////// MOVEMENT DEFINITIONS ///////////////
const int IR_SENSOR_REACHED = 0, IR_SENSOR_KEEP_MOVING = 1;

// counter clock-wise movement is any counter-clockwise rotation (brush rotation motor),
// left movement (frame rotation motor), or downward movement (brush movement motor).
uint8_t COUNTER_CLOCKWISE_MOVEMENT [2] = {LOW, HIGH};\

// clock-wise movement is any clock-wise rotation (brush rotation motor), right movement (frame movement motor), or
// upward movement (brush movement motor).
uint8_t CLOCKWISE_MOVEMENT [2] = {HIGH, LOW};

uint8_t STOP_MOVEMENT [2] = {LOW, LOW};