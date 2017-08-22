/*!
 * @file Motor_Stepper.ino
 * @brief DFRobot's Motor Drive
 * @n The example demonstrates one group of stepping motor and 2 groups 
	  of D.C motors work together at the same time, contains direction control 
	  of D.C motors and stepping motor.

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
//M3--->motor_Group_3--->[M3A(+),M3B(-)]
//M4--->motor_Group_4--->[M4A(+),M4B(-)]
//SA--->Stepper_Group_A--->[M1A(A+),M1B(A-),M2A(B+),M2B(B-)]
//CW: rotate in positive direction
//CCW: rotate in reverse
/*****************Function instruction*****************/
//void start(float angle, uint16_t speed, uint8_t dir)
  //*This function can be used to start the motor
  //*angle: Set the Angle       Min:0°(If the Angle is equal to 0°,The motor will not stop spinning)
  //*speed: Set the speed       Min:8
  //*dir: Set Orientation       CW or CCW
//void getDir()
  //*This function can get the current rotation direction of the motor

DFRobot_Motor motor3(M3);
DFRobot_Motor motor4(M4);
DFRobot_Stepper stepperA(SA);


void reverse3_4()
{
  motor3.start(!motor3.getDir());
  motor4.start(!motor4.getDir());
}

void reverse_SA()
{
  stepperA.start(0, 10, !stepperA.getDir());
}

void setup() {
  //initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  //join i2c bus (address optional for master)
  Wire.begin(); 
  //Initialize motor drive chip of stepping motor (Group A) and ¾ group of D.C motor
  stepperA.init();
  motor3.init();
  motor4.init();
  //Set the initial direction
  motor3.start(CCW);
  motor4.start(CW);
  stepperA.start(0, 10, CW);
  delay(1500);
}

void loop() 
{
  static int i=0;
  //Motor3 and motor4 reverse in every 1.5 seconds
  reverse3_4();
  //Stepping motor (Group A) reverse in every 3 seconds
  if((++i%2) == 0) {
    reverse_SA();
    i=0;
  }
  delay(1500);
}