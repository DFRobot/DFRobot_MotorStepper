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


DFRobot_Motor motor1(M1);
DFRobot_Motor motor2(M2);
DFRobot_Motor motor3(M3);
DFRobot_Motor motor4(M4);

#define  EN  13
uint8_t beg=0;
 
void setup() {
  //initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  //join i2c bus (address optional for master)
  Wire.begin(); 
  //Initialize motor drive chip of stepping motor (Group A) and ¾ group of D.C motor
  pinMode(EN, OUTPUT);
  delay(2000);
 
}

void loop() 
{
  Serial.println("-------TEST START-------");
  digitalWrite(EN, LOW); Serial.println("电源断开，LED熄灭");
  delay(3000);
  digitalWrite(EN, HIGH); Serial.println("电源接通，LED闪动");
  init(M1);
  init(M2);
  init(M3);
  init(M4); 
  Serial.println("LED常亮");
  delay(3000);
  
  Serial.println("正转（顺时针）");
  motor1.start(CW);
  motor2.start(CW);
  motor3.start(CW);
  motor4.start(CW);
  delay(3000);

  Serial.println("反转（逆时针）");
  motor1.start(CCW);
  motor2.start(CCW);
  motor3.start(CCW);
  motor4.start(CCW);
  delay(3000);

  Serial.println("停止");
  motor1.stop();
  motor2.stop();
  motor3.stop();
  motor4.stop(); 
  Serial.println("-----TEST STOP-----");
  Serial.println(""); 
  beg=0;
  delay(3000);
}






void begin()
{
  uint8_t Str,Num=3;
  unsigned char W_Data[3]={'o','k','0'};
  delay(3000);
  beg = 1;
  Wire.beginTransmission(IICADDR); // transmit to device #8
  Wire.write(0x00);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  Wire.requestFrom(IICADDR, Num);
  
  Str = Wire.read();
  Serial.print("Product ID:"); // print the character
  Serial.println(Str,HEX); // print the characters
  Str = Wire.read();
  Serial.print("Version ID:"); // print the character
  Serial.println(Str,HEX); // print the character
 
  Write_Motor(0x00, W_Data, 3);
  while(1){
    if(Read_Motor(0x00,1) == 0x10)
    {
      Serial.println("OK!"); // print the character 
      return;
    }
    delay(20);
  }
}

uint8_t Read_Motor(unsigned char Reg ,unsigned char Num )
{
   uint8_t Str;
   delay(1);
   //Serial.print("-----"); // print the character
   Wire.beginTransmission(IICADDR); // transmit to device #8
   Wire.write(Reg);              // sends one byte
   Wire.endTransmission();    // stop transmitting
   Wire.requestFrom(IICADDR, Num);
   while (Wire.available())   // slave may send less than requested
  {
    Str = Wire.read();
  }
    return Str;
}

void Write_Motor(unsigned char Reg ,unsigned char *buf, unsigned char Num)
{
   Wire.beginTransmission(IICADDR); // transmit to device #8
   Wire.write(Reg);              // sends one byte
   for(unsigned char i=0;i<Num;i++)
   {
     Wire.write(buf[i]); 
   }
   Wire.endTransmission();    // stop transmitting
}

void init(uint8_t id)
{
  if(beg==0) begin();
  unsigned char W_Data[2]={1,0};
  switch(id)
  {
    case M1: Write_Motor(0,W_Data,2); break;
    case M2: Write_Motor(10,W_Data,2); break;
    case M3: Write_Motor(16,W_Data,2); break;
    case M4: Write_Motor(22,W_Data,2); break;
  }
}

