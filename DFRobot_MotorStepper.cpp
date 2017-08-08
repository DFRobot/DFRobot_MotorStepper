/*!
 * @file DFRobot_MotorStepper.cpp
 * @brief DFRobot's Motor Drive
 * @n This example provides DC motor and stepper motor control drive

 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 
 * @author [LiXin]
 * @version  V1.0
 * @date  2017-7-31
 * @https://github.com/DFRobot/DFRobot_MotorStepper
 */

#include <Wire.h>
#include"DFRobot_MotorStepper.h"

motorState_t localMotor;
uint8_t Begin = 0;

MotorStepper::MotorStepper()
	:_I2C_ddr_(IICADDR)
{}
MotorStepper::~MotorStepper()
{}

void MotorStepper::begin()
{
  uint8_t Str,Num=3;;
  unsigned char W_Data[3]={'o','k','0'};
  
  Begin = 1;
  delay(2000);
  
  Wire.beginTransmission(_I2C_ddr_); // transmit to device #8
  Wire.write(0x00);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  Wire.requestFrom(_I2C_ddr_, Num);
  
  Str = Wire.read();
  Str = Wire.read();
  Serial.print("Product ID:"); // print the character
  Serial.print(Str,HEX); // print the characters
  Serial.println(""); // print the character
  Str = Wire.read();
  Serial.print("Version ID:"); // print the character
  Serial.print(Str,HEX); // print the character
  Serial.println(""); // print the character

  Write_Motor(0x00, W_Data, 3);
  while(1){
	  if(Read_Motor(0x00,1) == 0x01);
	  {
	    Serial.println("OK!"); // print the character 
	    return;
	  }
	  delay(20);
  }
}

void MotorStepper::Write_Motor(unsigned char Reg ,unsigned char *buf, unsigned char Num)
{
   uint8_t num;
   Wire.beginTransmission(_I2C_ddr_); // transmit to device #8
   Wire.write(Reg);              // sends one byte
   #if defined(ESP)
   num = Num;
   #else
   num = Num-1;
   #endif
   for(unsigned char i=0;i<num;i++)
   {
     Wire.write(buf[i]); 
   }
   Wire.endTransmission();    // stop transmitting
}

uint8_t MotorStepper::Read_Motor(unsigned char Reg ,unsigned char Num )
{
 uint8_t Str;
   delay(1);
   //Serial.print("-----"); // print the character
   Wire.beginTransmission(_I2C_ddr_); // transmit to device #8
   Wire.write(Reg);              // sends one byte
   Wire.endTransmission();    // stop transmitting
   Wire.requestFrom(_I2C_ddr_, Num);
   while (Wire.available())   // slave may send less than requested
  {
    Str = Wire.read();
   //Serial.print(Str,HEX); // print the character
   //Serial.write(' '); // print the character
  }
   //Serial.println("-----"); // print the character
    return Str;
}


DFRobot_Motor::DFRobot_Motor(uint8_t ID)
{
	id = ID;
}
DFRobot_Motor::~DFRobot_Motor()
{}


void DFRobot_Motor::init()
{
  if(!Begin) begin();
  unsigned char W_Data[2]={1,0};
  switch(id)
  {
	  case M1: Write_Motor(0,W_Data,2); break;
	  case M2: Write_Motor(10,W_Data,2); break;
	  case M3: Write_Motor(16,W_Data,2); break;
	  case M4: Write_Motor(22,W_Data,2); break;
  }
}

void DFRobot_Motor::shutdown()
{
  unsigned char W_Data[2]={1,0};
  switch(id)
  {
	  case M1: Write_Motor(1,W_Data,2); break;
	  case M2: Write_Motor(11,W_Data,2); break;
	  case M3: Write_Motor(17,W_Data,2); break;
	  case M4: Write_Motor(23,W_Data,2); break;
  }
}

void DFRobot_Motor::stop()
{
  unsigned char W_Data[2]={1,0};
  switch(id)
  {
	  case M1: Write_Motor(2,W_Data,2); break;
	  case M2: Write_Motor(12,W_Data,2); break;
	  case M3: Write_Motor(18,W_Data,2); break;
	  case M4: Write_Motor(24,W_Data,2); break; 
  }
}


void DFRobot_Motor::start(uint8_t dir)
{
  unsigned char W_Data[2]={1,0};
  switch(id)
  {
	  case M1:
	  {
		  if(dir == CW) Write_Motor(3,W_Data,2);
          else if(dir == CCW)  Write_Motor(4,W_Data,2);
		  localMotor.motor1 = dir;
	  } break; 
	  case M2: 
	  {
		  if(dir == CW) Write_Motor(13,W_Data,2);
          else if(dir == CCW)   Write_Motor(14,W_Data,2);
		  localMotor.motor2 = dir;
	  } break; 
	  case M3:
	  {
		  if(dir == CW) Write_Motor(19,W_Data,2);
          else if(dir == CCW)  Write_Motor(20,W_Data,2);
		  localMotor.motor3 = dir;
	  } break; 
	  case M4: 
	  {
		  if(dir == CW) Write_Motor(25,W_Data,2);
          else if(dir == CCW)  Write_Motor(26,W_Data,2);
		  localMotor.motor4 = dir;
	  } break; 
  }	
}
void DFRobot_Motor::speed(uint16_t val)
{
  val = 4096-val;
  unsigned char W_Data[3]={val>>8,val,0};
  switch(id)
  {
	  case M1: Write_Motor(5,W_Data,3); break;
	  case M2: Write_Motor(15,W_Data,3); break;
	  case M3: Write_Motor(27,W_Data,3); break;
	  case M4: Write_Motor(21,W_Data,3); break; 
  }
}

uint8_t DFRobot_Motor::getDir()
{
	uint8_t dir;
	switch(id)
	{
		case M1: dir = localMotor.motor1; break;
		case M2: dir = localMotor.motor2; break;
		case M3: dir = localMotor.motor3; break;
		case M4: dir = localMotor.motor4; break;
	}
	return dir;
}





DFRobot_Stepper::DFRobot_Stepper(uint8_t ID)
{
	id = ID;
}
DFRobot_Stepper::~DFRobot_Stepper()
{}

void DFRobot_Stepper::init()
{
  if(!Begin) begin(); 
  unsigned char W_Data[2]={1,0};
  switch(id)
  {
  	case SA: Write_Motor(0,W_Data,2); break; 
  	case SB: Write_Motor(16,W_Data,2); break;
  }
}

void DFRobot_Stepper::shutdown()
{
  unsigned char W_Data[2]={1,0};
  switch(id)
  {
	  case SA: Write_Motor(1,W_Data,2); break; 
	  case SB: Write_Motor(17,W_Data,2); break;
  }	  
}

void DFRobot_Stepper::stop()
{
  unsigned char W_Data[2]={1,0};
  switch(id)
  {
     case SA: Write_Motor(32, W_Data, 2); break;
	 case SB: Write_Motor(33, W_Data, 2); break;	
  }	 
}


void DFRobot_Stepper::speed(uint16_t val)
{
  unsigned char W_Data[3]={val>>8, val,0};
  switch(id)
  {
     case SA: Write_Motor(34, W_Data, 3); break;
	 case SB: Write_Motor(35, W_Data, 3); break;	
  }	 
}


void DFRobot_Stepper::start(float angle, uint16_t speed, uint8_t dir)
{
  unsigned char W_Data[5]={0};
  uint16_t count, _angle = angle*10; 
  if(speed<8) speed=8;
	if(_angle*10%9<=_angle*10%18)
	{
		count=_angle/9;
		W_Data[0] = count>>8;  W_Data[1] = count;
        W_Data[2] = speed>>8;  W_Data[3] = speed;
		switch(id)
		{
			case SA:  
			{
				if(dir == CW)  Write_Motor(8, W_Data, 5);
				else if(dir == CCW) Write_Motor(9, W_Data, 5);
				localMotor.stepperA = dir;
			}break;
			case SB:
			{
				if(dir == CW) Write_Motor(30, W_Data, 5);
				else if(dir == CCW) Write_Motor(31, W_Data, 5);
				localMotor.stepperB = dir;
			}break;	
		  }
	}else
	{
		count=angle/1.8;
		speed = speed*2-1;
		W_Data[0] = count>>8;  W_Data[1] = count;
        W_Data[2] = speed>>8;  W_Data[3] = speed; 
		switch(id)
		{
			case SA: 
			{
				if(dir == CW)  Write_Motor(6, W_Data, 5); 
			    else if(dir == CCW)  Write_Motor(7, W_Data, 5);
				localMotor.stepperA = dir;
			}break;
			case SB: 
			{
				if(dir == CW)  Write_Motor(28, W_Data, 5);
			    else if(dir == CCW)  Write_Motor(29, W_Data, 5); 
				localMotor.stepperB = dir;
			}break;
		}
	}
}


uint8_t DFRobot_Stepper::getDir()
{
	uint8_t dir;
	switch(id)
	{
		case SA: dir = localMotor.stepperA; break;
		case SB: dir = localMotor.stepperB; break;
	}
	return dir;
}


