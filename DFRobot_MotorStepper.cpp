/*!
 * @file DFRobot_MotorStepper.cpp
 * @brief DFRobot's Motor Drive
 * @details This example provides DC motor and stepper motor control drive
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT license (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2017-07-31
 * @https://github.com/DFRobot/DFRobot_MotorStepper
*/
 
#include <Wire.h>
#include"DFRobot_MotorStepper.h"

sMotorState_t localMotor;
uint8_t BeginA0 = 0;
uint8_t BeginA1 = 0;
uint8_t BeginA2 = 0;
uint8_t BeginA3 = 0;
DFRobot_MotorStepper::DFRobot_MotorStepper()
    :i2cAddr(IICADDR)
{}
DFRobot_MotorStepper::~DFRobot_MotorStepper()
{}

void DFRobot_MotorStepper::begin(unsigned char addr)
{
  uint8_t Str,Num=3;;
  unsigned char W_Data[3]={'o','k','0'};
  switch(addr){
  case A0: {
          if(BeginA0) return;
      else{
          BeginA0=1;
          Serial.println(""); // print the character
          Serial.println("----A0----");
      }
  }break;
  case A1: {
      if(BeginA1) return;
      else{
          BeginA1=1;
          Serial.println(""); // print the character
          Serial.println("----A1----");
      }
  }break;
  case A2: {
      if(BeginA2) return;
      else{
          BeginA2=1;
          Serial.println(""); // print the character
          Serial.println("----A2----");
      }
  }break;
  case A3: {
      if(BeginA3) return;
      else{
          BeginA3=1;
          Serial.println(""); // print the character
          Serial.println("----A3----");
      }
  }break;
  default:break;
  }
  delay(2000);
  Wire.beginTransmission(addr); // transmit to device #8
  Wire.write(0x00);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  Wire.requestFrom(addr, Num);
  Str = Wire.read();
  Serial.print("Product ID:"); // print the character
  Serial.print(Str,HEX); // print the characters
  Serial.println(""); // print the character
  Str = Wire.read();
  Serial.print("Version ID:"); // print the character
  Serial.print(Str,HEX); // print the character
  Serial.println(""); // print the character

  Write_Motor(addr,0x00, W_Data, 3);
  while(1){
      if(Read_Motor(addr, 0x00,1) == 0x10){
        Serial.println("OK!"); // print the character 
        return;
      }
      delay(20);
  }
}

void DFRobot_MotorStepper::Write_Motor(unsigned char addr, unsigned char Reg, unsigned char *buf, unsigned char Num)
{
   uint8_t num;
   Wire.beginTransmission(addr); // transmit to device #8
   Wire.write(Reg);              // sends one byte
   #if defined(ESP)
   num = Num;
   #else
   num = Num-1;
   #endif
   for(unsigned char i = 0; i  <num; i++)
   {
     Wire.write(buf[i]); 
   }
   Wire.endTransmission();    // stop transmitting
}

uint8_t DFRobot_MotorStepper::Read_Motor(unsigned char addr, unsigned char Reg ,unsigned char Num )
{
 uint8_t Str;
   delay(1);
   //Serial.print("-----"); // print the character
   Wire.beginTransmission(addr); // transmit to device #8
   Wire.write(Reg);              // sends one byte
   Wire.endTransmission();    // stop transmitting
   Wire.requestFrom(addr, Num);
   while (Wire.available())   // slave may send less than requested
  {
    Str = Wire.read();
   //Serial.print(Str,HEX); // print the character
   //Serial.write(' '); // print the character
  }
   //Serial.println("-----"); // print the character
    return Str;
}


DFRobot_Motor::DFRobot_Motor(uint8_t ID, uint8_t ADDR)
{
    id = ID;
    addr = ADDR;
}
DFRobot_Motor::~DFRobot_Motor()
{}


void DFRobot_Motor::init()
{
  begin(addr);
  unsigned char W_Data[2]={1,0};
  switch(id){
  case M1: Write_Motor(addr,0,W_Data,2); break;
  case M2: Write_Motor(addr,10,W_Data,2); break;
  case M3: Write_Motor(addr,16,W_Data,2); break;
  case M4: Write_Motor(addr,22,W_Data,2); break;
  default:break;
  }
}

void DFRobot_Motor::shutdown()
{
  unsigned char W_Data[2]={1,0};
  switch(id){
  case M1: Write_Motor(addr,1,W_Data,2); break;
  case M2: Write_Motor(addr,11,W_Data,2); break;
  case M3: Write_Motor(addr,17,W_Data,2); break;
  case M4: Write_Motor(addr,23,W_Data,2); break;
  default:break;
  }
}

void DFRobot_Motor::stop()
{
  unsigned char W_Data[2]={1,0};
  switch(id){
  case M1: Write_Motor(addr,2,W_Data,2); break;
  case M2: Write_Motor(addr,12,W_Data,2); break;
  case M3: Write_Motor(addr,18,W_Data,2); break;
  case M4: Write_Motor(addr,24,W_Data,2); break;
  default:break;
  }
}


void DFRobot_Motor::start(uint8_t dir)
{
  unsigned char W_Data[2]={1,0};
  switch(id){
  case M1:{
      if(dir == CW) Write_Motor(addr,3,W_Data,2);
      else if(dir == CCW)  Write_Motor(addr,4,W_Data,2);
      localMotor.motor1 = dir;
  } break; 
  case M2: {
      if(dir == CW) Write_Motor(addr,13,W_Data,2);
      else if(dir == CCW)   Write_Motor(addr,14,W_Data,2);
      localMotor.motor2 = dir;
  } break; 
  case M3:{
      if(dir == CW) Write_Motor(addr,19,W_Data,2);
      else if(dir == CCW)  Write_Motor(addr,20,W_Data,2);
      localMotor.motor3 = dir;
  } break; 
  case M4: {
      if(dir == CW) Write_Motor(addr,25,W_Data,2);
      else if(dir == CCW)  Write_Motor(addr,26,W_Data,2);
      localMotor.motor4 = dir;
  } break;
  default:break;
  }
}
void DFRobot_Motor::speed(uint16_t val)
{
  val = 4096-val;
  unsigned char W_Data[3]={val>>8,val,0};
  switch(id){
  case M1: Write_Motor(addr,5,W_Data,3); break;
  case M2: Write_Motor(addr,15,W_Data,3); break;
  case M3: Write_Motor(addr,27,W_Data,3); break;
  case M4: Write_Motor(addr,21,W_Data,3); break;
  default:break;
  }
}

uint8_t DFRobot_Motor::getDir()
{
  uint8_t dir;
  switch(id){
  case M1: dir = localMotor.motor1; break;
  case M2: dir = localMotor.motor2; break;
  case M3: dir = localMotor.motor3; break;
  case M4: dir = localMotor.motor4; break;
  default:break;
  }
  return dir;
}





DFRobot_Stepper::DFRobot_Stepper(uint8_t ID, uint8_t ADDR)
{
    id = ID;
    addr = ADDR;
}
DFRobot_Stepper::~DFRobot_Stepper()
{}

void DFRobot_Stepper::init()
{
  begin(addr);
  unsigned char W_Data[2]={1,0};
  switch(id){
  case SA: Write_Motor(addr,0,W_Data,2); break; 
  case SB: Write_Motor(addr,16,W_Data,2); break;
  default:break;
  }
}

void DFRobot_Stepper::shutdown()
{
  unsigned char W_Data[2]={1,0};
  switch(id){
  case SA: Write_Motor(addr,1,W_Data,2); break; 
  case SB: Write_Motor(addr,17,W_Data,2); break;
  default:break;
  }
}

void DFRobot_Stepper::stop()
{
  unsigned char W_Data[2]={1,0};
  switch(id){
  case SA: Write_Motor(addr,32, W_Data, 2); break;
  case SB: Write_Motor(addr,33, W_Data, 2); break;
  default:break;
  }
}


void DFRobot_Stepper::speed(uint16_t val)
{
  if(val>1023||val<=0) return;
  val=(1024-val)*3+5;
  unsigned char W_Data[3]={val>>8, val,0};
  switch(id){
  case SA: Write_Motor(addr,34, W_Data, 3); break;
  case SB: Write_Motor(addr,35, W_Data, 3); break;
  default:break;
  }
}


void DFRobot_Stepper::start(float angle, uint16_t speed, uint8_t dir)
{
  unsigned char W_Data[5]={0};
  uint16_t count, _angle = angle*10;
  if(speed>1023||speed<=0) return;
  speed=(1024-speed)*3+5;
    if(_angle%9<=_angle%18){
        count=_angle/9;
        W_Data[0] = count>>8;  W_Data[1] = count;
        W_Data[2] = speed>>8;  W_Data[3] = speed;
        switch(id){
        case SA:  {
            if(dir == CW)  Write_Motor(addr,8, W_Data, 5);
            else if(dir == CCW) Write_Motor(addr,9, W_Data, 5);
            localMotor.stepperA = dir;
        }break;
        case SB:{
            if(dir == CW) Write_Motor(addr,30, W_Data, 5);
            else if(dir == CCW) Write_Motor(addr,31, W_Data, 5);
            localMotor.stepperB = dir;
        }break;
        default:break;
        }
    }else{
        count=angle/1.8;
        speed = speed*2-1;
        W_Data[0] = count>>8;  W_Data[1] = count;
        W_Data[2] = speed>>8;  W_Data[3] = speed; 
        switch(id){
        case SA: {
            if(dir == CW)  Write_Motor(addr,6, W_Data, 5); 
            else if(dir == CCW)  Write_Motor(addr,7, W_Data, 5);
            localMotor.stepperA = dir;
        }break;
        case SB: {
            if(dir == CW)  Write_Motor(addr,28, W_Data, 5);
            else if(dir == CCW)  Write_Motor(addr,29, W_Data, 5); 
            localMotor.stepperB = dir;
        }break;
        default:break;
        }
    }
}


uint8_t DFRobot_Stepper::getDir()
{
  uint8_t dir;
  switch(id){
  case SA: dir = localMotor.stepperA; break;
  case SB: dir = localMotor.stepperB; break;
  default:break;
  }
  return dir;
}




void DFRobot_Stepper::changeSpeed(uint16_t count, uint16_t val1, uint16_t val2)
{
  int i;
  double freq,freqMax,freqMin;
  unsigned char W_Data[3]={0};
  if(val1>val2){
    freqMax = 10000/val2;
    freqMin = 10000/val1;
    count=count/2;
    
    for(i = 0; i < count*2; i++)
      {
        if(i<count){
          freq=freqMin+(double)(freqMax-freqMin)/(1+(double)exp((double)4*(count-i)/count));  
        }else{
          freq=freqMin+(double)(freqMax-freqMin)/(1+(double)exp(-(double)4*(i-count)/count));  
        }
        freq=(100/freq)*100;
        W_Data[0] = (uint16_t)freq<<8;
        W_Data[1] = (uint16_t)freq;
        switch(id){
        case SA: Write_Motor(addr,34, W_Data, 3); break;
        case SB: Write_Motor(addr,35, W_Data, 3); break;
        default:break;
        }
        delayMicroseconds(freq*100);
      }
  }else{
    freqMax = 10000/val1;
    freqMin = 10000/val2; 
    count=count/2;
    
    for(i = count*2-1; i >= 0; i--)
      {
        if(i>=count){
          freq=freqMin+(double)(freqMax-freqMin)/(1+(double)exp(-(double)4*(i-count)/count));
        }else{
          freq=freqMin+(double)(freqMax-freqMin)/(1+(double)exp((double)4*(count-i)/count));
        }
        
        freq=(100/freq)*100; 
        W_Data[0] = (uint16_t)freq<<8;
        W_Data[1] = (uint16_t)freq;
        switch(id){
        case SA: Write_Motor(addr,34, W_Data, 3); break;
        case SB: Write_Motor(addr,35, W_Data, 3); break;
        default:break;
        }
        delayMicroseconds(freq*100);
      }
  }
}
