// We have one interrupt handler for all encoders. This can be done by using a template
template<int interrupt_id>
void encoder_interrupt_handler() {
  if (digitalRead(encoder_dir_pins[interrupt_id]))
    encoder_positions[interrupt_id]++;
  else
    encoder_positions[interrupt_id]--;
}

void setup_encoders() {
  attachInterrupt(encoder_interrupt_pins[0], encoder_interrupt_handler<0>, RISING);
  attachInterrupt(encoder_interrupt_pins[1], encoder_interrupt_handler<1>, RISING);
  attachInterrupt(encoder_interrupt_pins[2], encoder_interrupt_handler<2>, RISING);
  attachInterrupt(encoder_interrupt_pins[3], encoder_interrupt_handler<3>, RISING);
}
