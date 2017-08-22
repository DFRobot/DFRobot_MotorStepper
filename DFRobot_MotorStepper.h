/*!
 * @file DFRobot_MotorStepper.h
 * @brief DFRobot's Motor Drive
 * @n This example provides DC motor and stepper motor control drive

 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 
 * @author [LiXin]
 * @version  V1.0
 * @date  2017-7-31
 * @https://github.com/DFRobot/DFRobot_MotorStepper
 */

#ifndef __DFRobot_Motor_H
#define __DFRobot_Motor_H

#include <Arduino.h>
#include <Wire.h>

#define _Reg_Addr_ 0x01
#define IICADDR 0x30>>1
#define M1 1
#define M2 2
#define M3 3
#define M4 4
#define SA 5
#define SB 6

#define CW   0
#define CCW   1

#define ESP


typedef struct motorState{
	uint8_t motor1;
	uint8_t motor2;
    uint8_t motor3;
    uint8_t motor4;
	uint8_t stepperA;
    uint8_t stepperB;
}motorState_t;
extern motorState_t localMotor;


class MotorStepper
{
public:
  MotorStepper();
  MotorStepper(uint8_t ddr);
  virtual ~MotorStepper();
  virtual void begin();
  virtual void Write_Motor(unsigned char Reg ,unsigned char *buf, unsigned char Num);
  virtual uint8_t Read_Motor(unsigned char Reg ,unsigned char Num );
private:
  uint8_t _I2C_ddr_;
};

class DFRobot_Motor:public MotorStepper
{
public:
  DFRobot_Motor(uint8_t ID);
  ~DFRobot_Motor();
  virtual void init();
  virtual void shutdown();
  virtual void stop();
  void start(uint8_t dir);
  void speed(uint16_t val);
  uint8_t getDir();
private:
  uint8_t id;
};

class DFRobot_Stepper:public MotorStepper
{
public:
  DFRobot_Stepper(uint8_t ID);
  ~DFRobot_Stepper();
  virtual void init();
  virtual void shutdown();
  virtual void stop();
  virtual void speed(uint16_t val);
  void start(float angle, uint16_t speed, uint8_t dir);
  void changeSpeed(uint16_t count, uint16_t val1, uint16_t val2);
  uint8_t getDir();
private:
  uint8_t id;
};



#endif



 