/*!
 * @file stepper.ino
 * @brief DFRobot's Motor Drive
 * @details The example demonstrates how two stepper motors (Group A and Group B) work together at the same time. 
 * @n including operations such as precision control of rotation angles, rotation 
 * @n directions etc.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT license (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2017-07-31
 * @https://github.com/DFRobot/DFRobot_MotorStepper
*/
#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_MotorStepper.h"

/*****************Keywords instruction*****************/
//SA--->Stepper_Group_A--->[M1A(A+),M1B(A-),M2A(B+),M2B(B-)]
//SB--->Stepper_Group_B--->[M3A(A+),M3B(A-),M4A(B+),M4B(B-)]
//CW: rotate in forward direction
//CCW: rotate in reverse direction
//A0: Chip Selection Address 1
//A1: Chip Selection Address 2
//A2: Chip Selection Address 3
//A3: Chip Selection Address 4
/*****************Function Instruction*****************/
//void start(float angle, uint16_t speed, uint8_t dir)
  //*This function can be used to start the motor
  //*angle: Set the Angle       Min:0°(If the Angle is equal to 0°, the motor will not stop spinning)
  //*speed: Set the speed       Min:8
  //*dir: Set Orientation       CW or CCW
//void getDir()
  //*This function can get the current rotation direction of the motor

DFRobot_Stepper stepperA(SA,A0);
DFRobot_Stepper stepperB(SB,A0);


void reverse_SA()
{
  stepperA.start(0, 1023, !stepperA.getDir());
}

void setup() {
  //initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  //Join i2c bus (address optional for master)
  Wire.begin(); 
  //Initialize drive chips of stepper motors (Group A and Group B) 
  stepperA.init();
  stepperB.init();
  //Setting stepper motor Group A rotate in forward direction
  stepperA.start(0, 1023, CW);
}

void loop() 
{
  static int i=0;
  //Set Group B stepper motor rotation angle to 6.3 °, speed to 1000RPM
  stepperB.start(6.3, 1000, CW);
  //Stepper motor Group A rotate in reverse in every 2 seconds
  if((++i%2) == 0){
    reverse_SA();
    i=0;
  }
  delay(1000); 
}
