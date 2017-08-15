DFRobot_Motor Library for Arduino
---------------------------------------------------------

This library is used to control dc motors and stepper motors

Including positive spin, reverse, speed adjustment, stop control

### Ready to start 
 
    void begin();
    
### Send multiple bytes to slave devices
   
    void Write_Motor(unsigned char Reg ,unsigned char *buf, unsigned char Num);

### Reads multiple bytes from the device
   
    uint8_t Read_Motor(unsigned char Reg ,unsigned char Num );
	
### Open dc motor and stepper motor drive hardware
   
    void start();
	
### Turn off dc motor and stepper motor drive hardware
   
    void shutdown();
	
### Motor stop rotation
   
    void stop();
	
### Dc motor rotation direction control
   
    void direction(uint8_t dir);
		
### Speed control of dc motor and stepper motor
   
    void speed(uint16_t val);

### Step motor rotation Angle, speed, direction control
   
    void rotate(float angle, uint16_t speed, uint8_t dir);

### Stepping motor accelerates and decelerates
   
    change_Speed(uint16_t count, uint16_t val1, uint16_t val2);  

 * @file DFRobot_Motor.ino
 * @brief DFRobot's Motor Drive
 * @n This example provides DC motor and stepper motor control drive
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2017
 * @copyright	GNU Lesser General Public License
 *
 * @author [Lixin]
 * @version  V1.0
 * @date  2017-7-31
 * @https://github.com/DFRobot/DFRobot_AT_Cmd