/****************************************************************
*!
 * @file GestureTest.ino
 * @brief DFRobot's Color Wave Sensor,DFRobot's Color Wave Sensor，this is the SparkFun RGB and Gesture Sensor, a small breakout board with a 
	built in APDS-9960 sensor that offers ambient light and color measuring, proximity detection, 
	and touchless gesture sensing. With this RGB and Gesture Sensor you will be able to control a computer,
	microcontroller, robot, and more with a simple swipe of your hand!
 * @n [Get the module here](http://www.dfrobot.com.cn/goods-1191.html)
 * @n This example get the four lightest positions of the IR sources.
 * @n [Connection and Diagram](http://wiki.dfrobot.com.cn/index.php?title=(SKU:SEN0187)%E9%A2%9C%E8%89%B2%E8%AF%86%E5%88%AB%E6%8C%A5%E6%89%8B%E4%BC%A0%E6%84%9F%E5%99%A8%E6%A8%A1%E5%9D%97)
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 *
 * @author [Carl](Carl.xu@dfrobot.com)
 * @version  V1.0
 * @date  2016-07-12

Hardware Connections:

IMPORTANT: The APDS-9960 can only accept 3.3V!
 
 Arduino Pin  APDS-9960 Board  Function
 
3.3V-5V      VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock
 2            INT              Interrupt
 13           -                LED
****************************************************************/

#include <Wire.h>
#include <DFRobot_ColorWaveSensorAPDS9960.h>

// Pins
#define APDS9960_INT    2 // Needs to be an interrupt pin

// Global Variables
DFRobot_ColorWaveSensorAPDS9960 apds = DFRobot_ColorWaveSensorAPDS9960();
int isr_flag = 0;

void setup() {
  Serial.begin(9600);
  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);
  if (apds.init()) 
  {
		Serial.println(F("init successful"));
  } 
  else 
  {
		Serial.println(F("init fail"));
  }
  if (apds.enableGestureSensor(true)) 
  {
		Serial.println(F("enable gesture sensor successful"));
  } 
  else 
  {
		Serial.println(F("enable gesture sensor fail"));
  }
}

void loop() {
  if(isr_flag == 1) 
  {
    handleGesture();
    if(digitalRead(APDS9960_INT) == 0)
	{
      apds.init();
      apds.enableGestureSensor(true);
    }
    isr_flag = 0;
  }
}

void interruptRoutine() 
{
  isr_flag = 1;
}

void handleGesture() 
{
    if ( apds.isGestureAvailable() ) 
	{
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
}
