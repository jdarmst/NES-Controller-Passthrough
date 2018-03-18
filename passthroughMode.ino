//===============================================================================
//  Passthrough Mode interrupt functions
//===============================================================================

void dataInit() {
  // Latch went high
  //   read first data bit into temp variable
  //   set counter to 1
  //   reset volitile state
  //   read temp variable into bit position 0

  int data = (bitRead(PIND, 4) == 0 ? LOW : HIGH);
  if (data == LOW) { bitClear(nesRegister, 0); }
    else bitSet(nesRegister, 0);

  btnCounter = 1;
}

void dataNext() {
  // Reading the next bit
  //   Read data value
  //   Increment counter variable
  //__asm__("nop\n\tnop\n\tnop\n\tnop\n\t");
  int data = (bitRead(PIND, 4) == 0 ? LOW : HIGH);
  if (data == LOW) { bitClear(nesRegister, btnCounter); }
    else bitSet(nesRegister, btnCounter);
  btnCounter++;
}
