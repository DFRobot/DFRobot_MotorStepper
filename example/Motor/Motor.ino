/*!
 * @file Motor.ino
 * @brief DFRobot's Motor Drive
 * @n The example demonstrates four groups D.C motors work together 
	  at the same time, contains operations such as rotation, speed 
	  adjustment, brakes and so on.

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

DFRobot_Motor motor1(M1);
DFRobot_Motor motor2(M2);
DFRobot_Motor motor3(M3);
DFRobot_Motor motor4(M4);


void setup() {
  //initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  //join i2c bus (address optional for master)
  Wire.begin();
  //Initialize D.C motor drive chip (Group1-4)
  motor1.init();
  motor2.init();
  motor3.init();
  motor4.init();
}

void loop() 
{
  //Setting initial velocity
  motor1.speed(4096);
  motor2.speed(4096);
  motor3.speed(4096);
  motor4.speed(4096);
  //Motor1 and motor3 rotate in positive direction; motor2 and motor4 rotate in reverse
  motor1.start(CW);
  motor2.start(CCW);
  motor3.start(CW);
  motor4.start(CCW);
  delay(2000);

  //Change velocity in 2 seconds
  motor1.speed(1000);
  motor2.speed(1000);
  motor3.speed(1000);
  motor4.speed(1000);
  //All motors rotate in reverse
  motor1.start(CCW);
  motor2.start(CW);
  motor3.start(CCW);
  motor4.start(CW);
  delay(2000);
  
  //All motors brake and stop rotating
  motor1.stop();
  motor2.stop();
  motor3.stop();
  motor4.stop();
  delay(2000);
}
