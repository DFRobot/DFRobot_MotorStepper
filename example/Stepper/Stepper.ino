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

/*****************Keywords instruction*****************/
//SA--->Stepper_Group_A--->[M1A(A+),M1B(A-),M2A(B+),M2B(B-)]
//SB--->Stepper_Group_B--->[M3A(A+),M3B(A-),M4A(B+),M4B(B-)]
//CW: rotate in positive direction
//CCW: rotate in reverse
//A0: Chip Selection Address 1
//A1: Chip Selection Address 2
//A2: Chip Selection Address 3
//A3: Chip Selection Address 4
/*****************Function instruction*****************/
//void start(float angle, uint16_t speed, uint8_t dir)
  //*This function can be used to start the motor
  //*angle: Set the Angle       Min:0°(If the Angle is equal to 0°,The motor will not stop spinning)
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
  //join i2c bus (address optional for master)
  Wire.begin(); 
  //Initialize drive chips of stepping motors (Group A and Group B) 
  stepperA.init();
  stepperB.init();
  //Setting stepping motor Group A rotate in positive direction
  stepperA.start(0, 1023, CW);
}

void loop() 
{
  static int i=0;
  //Group B stepper motor every 1 s rotational 6.3 °
  stepperB.start(6.3, 1000, CW);
  //Stepping motor (Group A) rotate in reverse in every 2 seconds
  if((++i%2) == 0){
    reverse_SA();
    i=0;
  }
  delay(1000); 
}