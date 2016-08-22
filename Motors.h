
class EncodedDC {
    // An encoded DC is a DC motor with an encoder which is controlled by a PID to drive to target positions
  public:
    EncodedDC(Adafruit_DCMotor* motor_handler, volatile long* encoder) :
      motor_handler(motor_handler),
      encoder(encoder),
      pid(&pos, &setspeed, &target_pos, 119 / 100., 0, 7 / 100., DIRECT) {
      pid.SetMode(AUTOMATIC);
      pid.SetOutputLimits(-255, 255);
      pid.SetSampleTime(20);
    }

    void loop() {
      // Fetch the int position from the encoder and store it in our pos double variable
      pos = *encoder; //TODO: maybe convert from encoder ticks to mm here

      // Run the PID controller
      pid.Compute();

      // Take the PID output and transfer it to the motor
      if (setspeed > 0) {
        motor_handler->run(FORWARD);
        motor_handler->setSpeed(setspeed);
      } else {
        motor_handler->run(BACKWARD);
        motor_handler->setSpeed(-setspeed);
      }

      // Disable the motor if we are close enough to the target position
      if (abs(pos - target_pos) < 2) //TODO: make the cutoff threshold configurable
        motor_handler->run(RELEASE);
    }

    double target_pos; // The position we want the motor to move to
    volatile long* encoder; // Pointer to the variable controlled by the encoder interrupts
    PID pid; // The PID controller for this motor
  private:
    Adafruit_DCMotor* motor_handler; // The handler to control this motor
    double pos; // The current position of this motor (updated in every loop from the encoder)
    double setspeed; // The target speed of this motor as set by the PID controller
};
