//===============================================================================
//  Setup for different modes
//===============================================================================

void modeSelect() {
  if(digitalRead(nesPower) == HIGH) passthroughMode();
  else hostMode();
}

void passthroughMode() {
  modeHost = 0;
  Serial.write("Passthrough mode activated.\n");
  // set clock and latch to input pins
  pinMode(nesClock, INPUT);
  pinMode(nesLatch, INPUT);

  // Add interrupts to latch and clock
  attachInterrupt(digitalPinToInterrupt(nesLatch), dataInit, RISING);
  attachInterrupt(digitalPinToInterrupt(nesClock), dataNext, FALLING);
}

void hostMode() {
  Serial.write("Host Mode activated.\n");
  // Detatch interrupts
  detachInterrupt(digitalPinToInterrupt(nesLatch));
  detachInterrupt(digitalPinToInterrupt(nesClock));
  
  // set clock and latch to output pins
  pinMode(nesClock, OUTPUT);
  pinMode(nesLatch, OUTPUT);

  // Set mode to host
  modeHost = 1;
}
