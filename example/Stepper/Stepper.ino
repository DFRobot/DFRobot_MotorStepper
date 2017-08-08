/*!
 * @file Stepper.ino
 * @brief DFRobot's Motor Drive
 * @n The example demonstrates two groups of stepping motors (Group A and Group B) work together 
      at the same time, including operations such as precision control of rotation angles, rotation 
	  directions etc.

 * @copyright  [DFRobot](http://www.dfrobot.com), 2016
 * @copyright GNU Lesser General Public License
 
 * @author [LiXin]
 * @version  V1.0
 * @date  2017-7-31
 * @https://github.com/DFRobot/DFRobot_MotorStepper
 */
#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_MotorStepper.h"

DFRobot_Stepper stepperA(SA);
DFRobot_Stepper stepperB(SB);


void reverse_SA()
{
  stepperA.start(0, 20, !stepperA.getDir());
}

void setup() {
  //initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  //join i2c bus (address optional for master)
  Wire.begin(); 
  //Initialize drive chips of stepping motors (Group A and Group B) 
  stepperA.init();
  stepperB.init();
  //Setting stepping motor Group A rotate in positive direction
  stepperA.start(0, 20, CW);
}

void loop() 
{
  static int i=0;
  //Group B stepper motor every 1 s rotational 6.3 °
  stepperB.start(6.3, 15, CW);
  //Stepping motor (Group A) rotate in reverse in every 2 seconds
  if((++i%2) == 0){
    reverse_SA();
    i=0;
  }
  delay(1000); 
}