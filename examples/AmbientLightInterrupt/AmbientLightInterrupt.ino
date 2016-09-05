/****************************************************************
*!
 * @file AmbientLightInterrupt.ino
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
 
 3.3V-5V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock
 2            INT              Interrupt
****************************************************************/

#include <Wire.h>
#include <DFRobot_ColorWaveSensorAPDS9960.h>

// Pins
#define APDS9960_INT    2  // Needs to be an interrupt pin
#define LED_PIN         13 // LED for showing interrupt

// Constants
#define LIGHT_INT_HIGH  1000 // High light level for interrupt
#define LIGHT_INT_LOW   10   // Low light level for interrupt

// Global variables
DFRobot_ColorWaveSensorAPDS9960 apds = DFRobot_ColorWaveSensorAPDS9960();
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;
int isr_flag = 0;
uint16_t threshold = 0;

void setup() {
  
  // Set LED as output
  Serial.println("color wave sensor boot......");
  pinMode(LED_PIN, OUTPUT);
  pinMode(APDS9960_INT, INPUT);
  Serial.begin(9600);
  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);
  // Initialize APDS-9960 (configure I2C and initial values)
  if (!apds.init()) 
  {
		Serial.println(F("init fail"));
  } 
  // Set high and low interrupt thresholds
  if (!apds.setLightIntLowThreshold(LIGHT_INT_LOW)) 
  {
		Serial.println(F("write low threshold error"));
  }
  if (!apds.setLightIntHighThreshold(LIGHT_INT_HIGH)) 
  {
		Serial.println(F("write high threshold error"));
  }
  // Start running the APDS-9960 light sensor (no interrupts)
  if (!apds.enableLightSensor(false)) 
  {
		Serial.println(F("enable light sensor fail"));
  } 
  // Read high and low interrupt thresholds
  if ( !apds.getLightIntLowThreshold(threshold)) 
  {
		Serial.println(F("read low threshold error"));
  } 
  if ( !apds.getLightIntHighThreshold(threshold) ) 
  {
		Serial.println(F("read high threshold error"));
  } 
  // Enable interrupts
  if (!apds.setAmbientLightIntEnable(1)) 
  {
		Serial.println(F("enable interrupts "));
  }
  delay(500);
}

void loop() {
  
  // If interrupt occurs, print out the light levels
  if ( isr_flag == 1 ) {
    
    // Read the light levels (ambient, red, green, blue) and print
    if (  !apds.readAmbientLight(ambient_light) ||
          !apds.readRedLight(red_light) ||
          !apds.readGreenLight(green_light) ||
          !apds.readBlueLight(blue_light) ) {
      Serial.println("Error reading light values");
    } else {
      Serial.print("Interrupt! Ambient: ");
      Serial.print(ambient_light);
      Serial.print(" R: ");
      Serial.print(red_light);
      Serial.print(" G: ");
      Serial.print(green_light);
      Serial.print(" B: ");
      Serial.println(blue_light);
    }
    
    // Turn on LED for a half a second
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    
    // Reset flag and clear APDS-9960 interrupt (IMPORTANT!)
    isr_flag = 0;
    if ( !apds.clearAmbientLightInt() ) 
	{
		Serial.println("Error clearing interrupt");
    }
    
  }
}

void interruptRoutine() {
  isr_flag = 1;
}
