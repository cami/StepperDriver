/*
 * Multi-motor control (experimental)
 *
 * Move two or three motors at the same time.
 * This module is still work in progress and may not work well or at all.
 *
 * Copyright (C)2017 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>
#include "pin_config.h"
#include "motor_commands.h"
#include "../../TureLibrary/src/utils.h"

#include "BasicStepperDriver.h"
#include "MultiDriver.h"
#include "SyncDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// Target RPM for X axis motor
// #define MOTOR_X_RPM MAX_RPM
#define MOTOR_X_RPM 120

// Target RPM for Y axis motor
// #define MOTOR_Y_RPM MAX_RPM
#define MOTOR_Y_RPM 120

// // Target RPM for Z axis motor
// #define MOTOR_Z_RPM MAX_RPM

// X motor
#define DIR_X       PIN_3_DIR
#define STEP_X      PIN_3_STEP

// Y motor
#define DIR_Y       PIN_5_DIR
#define STEP_Y      PIN_5_STEP

// // Z motor
// #define DIR_Z       PIN_2_DIR
// #define STEP_Z      PIN_2_STEP

// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// 2-wire basic config, microstepping is hardwired on the driver
// Other drivers can be mixed and matched but must be configured individually
BasicStepperDriver stepperX(MOTOR_STEPS, DIR_X, STEP_X);
BasicStepperDriver stepperY(MOTOR_STEPS, DIR_Y, STEP_Y);
// BasicStepperDriver stepperZ(MOTOR_STEPS, DIR_Z, STEP_Z);

// Pick one of the two controllers below
// each motor moves independently, trajectory is a hockey stick
MultiDriver controller(stepperX, stepperY);
// MultiDriver controller(stepperX, stepperY, stepperZ);
// OR
// synchronized move, trajectory is a straight line
// SyncDriver controller(stepperX, stepperY);
// SyncDriver controller(stepperX, stepperY, stepperZ);


void setup() {
    Serial.begin(115200);
    delay(4000);

    /*
     * Set target motors RPM.
     */
    stepperX.begin(MOTOR_X_RPM, MICROSTEPS);
    stepperY.begin(MOTOR_Y_RPM, MICROSTEPS);
    // stepperZ.begin(MOTOR_Z_RPM, MICROSTEPS);

    // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next two lines
    // stepperX.setEnableActiveState(LOW);
    // stepperY.setEnableActiveState(LOW);
    // stepperZ.setEnableActiveState(LOW);
}

void loop() {
    controller.rotate(convertToSubDegree(double(MOTOR_0_MOVE_DISTANCE_CMD)), convertToSubDegree(double(MOTOR_1_MOVE_DISTANCE_CMD)));
    delay(15000);
}
