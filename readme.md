DFRobot_Motor Library for Arduino
---------------------------------------------------------

The library is used for controlling D.C motor and stepper motor, contains operations such as rotation, speed adjustment, brakes and so on.
    
### The function is used for sending multible bytes
   
    void Write_Motor(unsigned char Reg ,unsigned char *buf, unsigned char Num);

### The function is used for reading multible bytes
   
    uint8_t Read_Motor(unsigned char Reg ,unsigned char Num );
	
### Ready to start 
 
    void init();
	
### Turn off drive chip of D.C motor or stepper motor 
   
    void shutdown();
	
### Stop rotating
   
    void stop();
	
### Speed regulation of D.C motor or stepper motor 
   
    void speed(uint16_t val);
	val: Speed value(Stepper:8~65536 Motor:0~4096).
	
### D.C motor starts to work
   
    void start(uint8_t dir);
	dir: Direction is set(CW:positive CCW:reverse)
	
### Stepper motor starts to work
   
    void start(float angle, uint16_t speed, uint8_t dir);
	angle：Rotation angle(0~65536).
	speed: Setting initial velocity(8~65536)
	dir: Direction is set(CW:positive CCW:reverse)

###	Get current direction of the motor

	uint8_t getDir();
	
	
	
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
 * @https://github.com/DFRobot/DFRobot_MotorStepper