#include <PID_v1.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <VSync.h>
#include "Motors.h"

/// ENCODER VARIABLES
const int encoder_dir_pins[] = {4, 6, 8, 10};
const int encoder_interrupt_pins[] = {3, 5, 7, 9};
volatile long encoder_positions[] = {0, 0, 0, 0}; // The encoder positions get updated by the interrupts automagically

/// COMMUNICATION VARIABLES
ValueReceiver<6> receiver(Serial5);
int joystickLx, joystickLy, joystickRx, joystickRy, potMeter, encoderInteger;

/// MOTOR VARIABLES
Adafruit_MotorShield motorshield;

EncodedDC motors[] = {EncodedDC(motorshield.getMotor(1), &encoder_positions[0]),
                      EncodedDC(motorshield.getMotor(2), &encoder_positions[1]),
                      EncodedDC(motorshield.getMotor(3), &encoder_positions[2]),
                      EncodedDC(motorshield.getMotor(4), &encoder_positions[3]),
                     };

void setup() {
  setup_encoders();
  setup_communication();
  
  Wire.begin();
  delay(500);
  motorshield.begin(70);
}

void loop() {
  receiver.sync();

  // Tell X-axis motors where to go
  motors[0].target_pos = joystickLx;
  motors[2].target_pos = -joystickLx;

  // Tell Y-axis motors where to go
  motors[1].target_pos = joystickLy;
  motors[3].target_pos = -joystickLy;

  int maxSpeed = map(potMeter, 0, 1024, 0, 255);
  
  for(int i=0; i < 4; ++i) {
    motors[i].pid.SetOutputLimits(-maxSpeed, maxSpeed);
    motors[i].loop();
  }
  
}
