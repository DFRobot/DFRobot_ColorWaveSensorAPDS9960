/****************************************************************
*!
 * @file ColorSensor.ino
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
DFRobot_ColorWaveSensorAPDS9960 apds = DFRobot_ColorWaveSensorAPDS9960();
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;

void setup() {
  Serial.begin(9600);
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( !apds.init() ) 
  {
		Serial.println(F("init fail"));
  } 
  // Start running the APDS-9960 light sensor (no interrupts)
  if ( !apds.enableLightSensor(false) ) 
  {
		Serial.println(F("enable light sensor fail"));
  } 
  // Wait for initialization and calibration to finish
  delay(500);
}

void loop() {
  
  // Read the light levels (ambient, red, green, blue)
  if (  !apds.readAmbientLight(ambient_light) ||
        !apds.readRedLight(red_light) ||
        !apds.readGreenLight(green_light) ||
        !apds.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    Serial.print("Ambient: ");
    Serial.print(ambient_light);
    Serial.print(" Red: ");
    Serial.print(red_light);
    Serial.print(" Green: ");
    Serial.print(green_light);
    Serial.print(" Blue: ");
    Serial.println(blue_light);
  }
  delay(1000);
}
