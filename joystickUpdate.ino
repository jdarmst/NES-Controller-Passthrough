//===============================================================================
//  Joystick update
//===============================================================================

void joystickUpdate() {
  byte currentData = nesRegister;

  //Serial.print(currentData, BIN);

  for (int index = 0; index < 8; index++) {
    bool debug = false;
    int currentButtonState = bitRead(currentData, index);
    
    if (currentButtonState == 1) currentButtonState = 0;
      else currentButtonState = 1;

    if (currentButtonState != lastButtonState[index]) {
      // We need to update this button
      // A,B,Sel,Sta,Up,Dwn,Lft,Rit
      switch (index) {
        case 0: // A
          Joystick.setButton(0, currentButtonState);
          if (debug) Serial.print("Changed A\n");
          break;
        case 1: // B
          Joystick.setButton(1, currentButtonState);
          if (debug) Serial.print("Changed B\n");
          break;
        case 2: // Select
          Joystick.setButton(3, currentButtonState);
          if (debug) Serial.print("Changed Select\n");
          break;
        case 3: // Start
          Joystick.setButton(2, currentButtonState);
          if (debug) Serial.print("Changed Start\n");
          break;
        case 4: // Up
          if (currentButtonState == 1) {
            Joystick.setYAxis(-1);
          } else {
            Joystick.setYAxis(0);
          }
          if (debug) Serial.print("Changed Up\n");
          break;
        case 5: // Down
          if (currentButtonState == 1) {
            Joystick.setYAxis(1);
          } else {
            Joystick.setYAxis(0);
          }
          if (debug) Serial.print("Changed Down\n");
          break;
        case 6: // Left
          if (currentButtonState == 1) {
            Joystick.setXAxis(-1);
          } else {
            Joystick.setXAxis(0);
          }
          if (debug) Serial.print("Changed Left\n");
          break;
        case 7: // Right
          if (currentButtonState == 1) {
            Joystick.setXAxis(1);
          } else {
            Joystick.setXAxis(0);
          }
          if (debug) Serial.print("Changed Right\n");
          break;
      }
      lastButtonState[index] = currentButtonState;
    }
  }
}
