#include <Arduino.h>

#include "constants.h"
#include "irsensor.h"
#include "motor.h"
#include "voltmeter.h"
#include "action.h"

/////////// IR SENSORS ///////////
IrSensor AT_REST_IR_SENSOR_1 = IrSensor(AT_REST_IR_SENSOR_1_PIN);
IrSensor MAX_UPWARD_IR_SENSOR_2 = IrSensor(MAX_UPWARD_IR_SENSOR_2_PIN);
IrSensor MAX_DOWNWARD_IR_SENSOR_3 = IrSensor(MAX_DOWNWARD_IR_SENSOR_3_PIN);
IrSensor AT_FIRST_SOLAR_PANEL_IR_SENSOR_4 = IrSensor(AT_FIRST_SOLAR_PANEL_IR_SENSOR_4_PIN);
IrSensor AT_SECOND_SOLAR_PANEL_IR_SENSOR_5 = IrSensor(AT_SECOND_SOLAR_PANEL_IR_SENSOR_5_PIN);

/////////// MOTORS ///////////
Motor BRUSH_MOVEMENT_MOTOR = Motor(BRUSH_MOVEMENT_IN_PIN_6,
                                   BRUSH_MOVEMENT_IN_PIN_5,
                                   BRUSH_MOVEMENT_EN_PIN_7);

Motor BRUSH_ROTATION_MOTOR = Motor(BRUSH_ROTATION_MOTOR_IN_PIN_2,
                                   BRUSH_ROTATION_MOTOR_IN_PIN_3,
                                   BRUSH_ROTATION_MOTOR_EN_PIN_4);

Motor FRAME_MOVEMENT_MOTOR = Motor(FRAME_MOVEMENT_IN_PIN_9,
                                   FRAME_MOVEMENT_IN_PIN_8,
                                   FRAME_MOVEMENT_EN_PIN_10);

/////////// VOLTMETER ///////////
VoltMeter SOLAR_PANEL_ONE_VOLTAGE = VoltMeter(VT_PIN1, AT_PIN1);
VoltMeter SOLAR_PANEL_TWO_VOLTAGE = VoltMeter(VT_PIN2, AT_PIN2);

/////////// ACTIONS ///////////

Action MOVE_FROM_BASE_TO_SP_ONE = Action(FRAME_MOVEMENT_MOTOR,
                                         AT_FIRST_SOLAR_PANEL_IR_SENSOR_4,
                                         COUNTER_CLOCKWISE_MOVEMENT);

Action MOVE_FROM_BASE_TO_SP_TWO = Action(FRAME_MOVEMENT_MOTOR,
                                         AT_SECOND_SOLAR_PANEL_IR_SENSOR_5,
                                         COUNTER_CLOCKWISE_MOVEMENT);

Action ROTATE_BRUSH_CLOCKWISE = Action(BRUSH_ROTATION_MOTOR,
                                       IrSensor(),  // no IRSensor needed here.
                                       CLOCKWISE_MOVEMENT);

Action STOP_BRUSH_ROTATION = Action(BRUSH_ROTATION_MOTOR,
                                    IrSensor(),
                                    STOP_MOVEMENT);

Action MOVE_UPWARDS_FROM_SP_ONE = Action(BRUSH_MOVEMENT_MOTOR,
                                         MAX_UPWARD_IR_SENSOR_2,
                                         CLOCKWISE_MOVEMENT);

Action MOVE_DOWNWARDS_TO_SP_ONE = Action(BRUSH_MOVEMENT_MOTOR,
                                         MAX_DOWNWARD_IR_SENSOR_3,
                                         COUNTER_CLOCKWISE_MOVEMENT);

Action MOVE_FROM_SP_ONE_TO_BASE = Action(BRUSH_MOVEMENT_MOTOR,
                                         AT_REST_IR_SENSOR_1,
                                         COUNTER_CLOCKWISE_MOVEMENT);

Action MOVE_FROM_SP_ONE_TO_SP_TWO = Action(FRAME_MOVEMENT_MOTOR,
                                           AT_SECOND_SOLAR_PANEL_IR_SENSOR_5,
                                           COUNTER_CLOCKWISE_MOVEMENT);

Action MOVE_UPWARDS_FROM_SP_TWO = Action(FRAME_MOVEMENT_MOTOR,
                                         MAX_UPWARD_IR_SENSOR_2,
                                         CLOCKWISE_MOVEMENT);

Action MOVE_DOWNWARDS_TO_SP_TWO = Action(FRAME_MOVEMENT_MOTOR,
                                         MAX_DOWNWARD_IR_SENSOR_3,
                                         COUNTER_CLOCKWISE_MOVEMENT);

Action MOVE_FROM_SP_TWO_TO_BASE = Action(FRAME_MOVEMENT_MOTOR,
                                         AT_REST_IR_SENSOR_1,
                                         CLOCKWISE_MOVEMENT);

Action EXECUTION_LIST_ALL [] = {MOVE_FROM_BASE_TO_SP_ONE, ROTATE_BRUSH_CLOCKWISE, MOVE_UPWARDS_FROM_SP_ONE,
                                MOVE_DOWNWARDS_TO_SP_ONE, STOP_BRUSH_ROTATION, MOVE_FROM_SP_ONE_TO_SP_TWO,
                                ROTATE_BRUSH_CLOCKWISE, MOVE_UPWARDS_FROM_SP_TWO, MOVE_DOWNWARDS_TO_SP_TWO,
                                STOP_BRUSH_ROTATION, MOVE_FROM_SP_TWO_TO_BASE};

Action EXECUTION_LIST_CLEAN_SP_ONE [] = {MOVE_FROM_BASE_TO_SP_ONE, ROTATE_BRUSH_CLOCKWISE,
                                         MOVE_UPWARDS_FROM_SP_ONE,MOVE_DOWNWARDS_TO_SP_ONE,
                                         MOVE_FROM_SP_ONE_TO_BASE};

Action EXECUTION_LIST_CLEAN_SP_TWO [] = {MOVE_FROM_BASE_TO_SP_TWO, ROTATE_BRUSH_CLOCKWISE,
                                         MOVE_UPWARDS_FROM_SP_TWO,MOVE_DOWNWARDS_TO_SP_TWO,
                                         MOVE_FROM_SP_TWO_TO_BASE};


template <unsigned n>
void executeList(Action (&actions)[n]) {
    for (auto &action: actions) {
        if (action == STOP_BRUSH_ROTATION) {
            action.execute(0, true, false);
        } else {
            action.execute(MAX_SPEED);
        }

        delay(500);
    }
}


void setup(){}

void loop() {
    double voltReadingSpOne = SOLAR_PANEL_ONE_VOLTAGE.getVoltReading();
    double voltReadingSpTwo = SOLAR_PANEL_TWO_VOLTAGE.getVoltReading();

    if (voltReadingSpOne < ARDUINO_WORK_VOLTAGE && voltReadingSpTwo < ARDUINO_WORK_VOLTAGE) {
        executeList(EXECUTION_LIST_ALL);
    } else if (voltReadingSpOne < ARDUINO_WORK_VOLTAGE) {
        executeList(EXECUTION_LIST_CLEAN_SP_ONE);
    } else if (voltReadingSpTwo < ARDUINO_WORK_VOLTAGE) {
        executeList(EXECUTION_LIST_CLEAN_SP_TWO);
    }
}




