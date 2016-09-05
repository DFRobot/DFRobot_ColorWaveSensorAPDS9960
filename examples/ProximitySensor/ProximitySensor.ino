/****************************************************************
/*!
 * @file ProximitySensor.ino
 * @brief DFRobot's Color Wave Sensor,DFRobot's Color Wave Sensor，this is the SparkFun RGB and Gesture Sensor, a small breakout board with a 
 *	built in APDS-9960 sensor that offers ambient light and color measuring, proximity detection, 
 *	and touchless gesture sensing. With this RGB and Gesture Sensor you will be able to control a computer,
 *	microcontroller, robot, and more with a simple swipe of your hand!
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

// Global Variables
DFRobot_ColorWaveSensorAPDS9960 colwave = DFRobot_ColorWaveSensorAPDS9960();
uint8_t proximity_data = 0;

void setup() {
  
  // Initialize Serial port
  Serial.begin(9600);
  Serial.println("color wave sensor boot........");
  
  // Initialize ColorWaveSensor (configure I2C and initial values)
  if ( colwave.init() ) 
  {
		Serial.println(F("ColorWaveSensor initialization complete"));
  } 
  else 
  {
		Serial.println(F("Something went wrong during ColorWaveSensor init!"));
  }
  
  // Adjust the Proximity sensor gain
  if ( !colwave.setProximityGain(PGAIN_2X) ) 
  {
		Serial.println(F("Something went wrong trying to set PGAIN"));
  }
  
  // Start running the ColorWaveSensor proximity sensor (no interrupts)
  if ( colwave.enableProximitySensor(false) ) 
  {
		Serial.println(F("Proximity sensor is now running"));
  } 
  else 
  {
		Serial.println(F("Something went wrong during sensor init!"));
  }
}

void loop() {
  
  // Read the proximity value
  if ( !colwave.readProximity(proximity_data) ) 
  {
		Serial.println("Error reading proximity value");
  } 
  else 
  {
		Serial.print("Proximity: ");
		Serial.println(proximity_data);
  }
  
  // Wait 250 ms before next reading
  delay(250);
}