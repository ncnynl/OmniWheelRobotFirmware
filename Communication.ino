
void setup_communication() {
  Serial5.begin(19200);
  receiver.observe(joystickLx);
  receiver.observe(joystickLy);
  receiver.observe(joystickRx);
  receiver.observe(joystickRy);
  receiver.observe(potMeter);
  receiver.observe(encoderInteger);
}
