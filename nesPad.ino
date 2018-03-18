//===============================================================================
//  Libraries
//===============================================================================

#include <Joystick.h>

//===============================================================================
//  Constants
//===============================================================================

// Input bits
const int A_BUTTON         = 0;
const int B_BUTTON         = 1;
const int SELECT_BUTTON    = 2;
const int START_BUTTON     = 3;
const int UP_BUTTON        = 4;
const int DOWN_BUTTON      = 5;
const int LEFT_BUTTON      = 6;
const int RIGHT_BUTTON     = 7;

//===============================================================================
//  Variables
//===============================================================================

// controller data
byte nesRegister  = 255;    // We will use this to hold current button states
int btnCounter = 0;       // We will use this to hold which button we're checking for

// Mode Data
byte modeHost     = 0;

// Last state of the buttons (joystick)
// A,B,Sel,Sta,Up,Dwn,Lft,Rit
int lastButtonState[8] = {0,0,0,0,0,0,0,0};

//===============================================================================
//  Pin Declarations
//===============================================================================

int nesPower      = 7;    // The power pin for the NES controller (read hi for nes on)
int nesClock      = 2;    // The clock pin for the NES controller (pulse/read for next button)
int nesLatch      = 3;    // The latch pin for the NES controller (pulse/read for begin read)
int nesData       = 4;    // The data pin for the NES controller (read low for press)

int portData      = 25;   // The microcontroller port where the data resides

//===============================================================================
//  Joystick Setup
//===============================================================================

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  4, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

//===============================================================================
//  Initialization
//===============================================================================

void setup() {

  // Debug console setup
  Serial.begin(57600);
  
  // set power to input
  pinMode(nesPower, INPUT);

  // Set data to input
  pinMode(nesData, INPUT);

  // Set initial mode
  if (digitalRead(nesPower) == HIGH) passthroughMode();
    else hostMode();

  // Watch NES power for high state 
  attachInterrupt(digitalPinToInterrupt(nesPower), modeSelect, CHANGE);

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
}

//===============================================================================
//  Primary loop
//===============================================================================

void loop() {
  // put your main code here, to run repeatedly:
  if (modeHost) {
    // Call nes read function
    nesRegister = readNesController();
    
  }
  joystickUpdate();
  //delay(50);
}
