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

#define _REG_ADDR_ 0x01
#define IICADDR 0x30>>1
#define M1   1
#define M2   2
#define M3   3
#define M4   4
#define SA   5
#define SB   6
#define A0   0x30>>1
#define A1   0x38>>1
#define A2   0x3C>>1
#define A3   0x3E>>1
#define CW   0
#define CCW  1

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


class DFRobot_MotorStepper
{
public:
  DFRobot_MotorStepper();
  DFRobot_MotorStepper(uint8_t ddr);
  virtual ~DFRobot_MotorStepper();
  virtual void begin(unsigned char addr);
  virtual void Write_Motor(unsigned char addr, unsigned char Reg ,unsigned char *buf, unsigned char Num);
  virtual uint8_t Read_Motor(unsigned char addr, unsigned char Reg ,unsigned char Num );
private:
  uint8_t i2cAddr;
};

class DFRobot_Motor:public DFRobot_MotorStepper
{
  public:
    DFRobot_Motor(uint8_t ID, uint8_t ADDR);
    ~DFRobot_Motor();
    virtual void init();
    virtual void shutdown();
    virtual void stop();
    void start(uint8_t dir);
    void speed(uint16_t val);
    uint8_t getDir();
  private:
    uint8_t id;
    uint8_t addr;
};

class DFRobot_Stepper:public DFRobot_MotorStepper
{
  public:
    DFRobot_Stepper(uint8_t ID, uint8_t ADDR);
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
    uint8_t addr;
};



#endif



 