/**
	* Name: EE_D1_TempHumidDisplay.ino
	* Version: 1.0.0
	* Creation Date:07/08/2021
	* Author: Danishvir Singh (dan)
	* Description:
	* This sketch use Wemos D1 Mini(ESP8266), BME280 Temperature Humidity Pressure Sensor to read 
	* the temperature, pressure, humidity and altitude and display the readings on a 0.96 inch OLED Display.
	* The sketch was developed for Sheridan College Electronic Enabling Club.
*/

// Libraries required for the BME280 Temperature Humidity Pressure Sensor
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Libraries required for the 0.96 inch OLED Display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SEALEVELPRESSURE (1013.25) // Defines seal level pressure in millibars
#define SCREEN_WIDTH 128 // Defines OLED display width, in pixels
#define SCREEN_HEIGHT 64 // Defines OLED display height, in pixels

// Declaration for BME280 connected to I2C
Adafruit_BME280 bme;
// Declaration for SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long delayTime; // Define delay time

// Function to return temperature reading
String readBME280Temperature() {
	float t = bme.readTemperature();
	if (isnan(t)) {    
		Serial.println("Failed to read from BME28 sensor");
		return "--";
	}
	else {
		Serial.print("Temperature = ");
		Serial.print(t);
		return String(t);
	}
}
// Function to return humidity reading
String readBME280Humidity() {
	float h = bme.readHumidity();
	if (isnan(h)) {    
		Serial.println("Failed to read from BME28 sensor");
		return "--";
	}
	else {
		Serial.print("Humidity = ");
		Serial.print(h);
		return String(h);
	}
}
// Function to return pressure reading
String readBME280Pressure() {
	float p = bme.readPressure() / 100.0F;
	if (isnan(p)) {    
		Serial.println("Failed to read from BME28 sensor");
		return "--";
	}
	else {
		Serial.print("Pressure = ");
		Serial.print(p);
		return String(p);
	}
}
// Function to return approximate altitude reading
String readBME280Altitude() {
	float a = bme.readAltitude(SEALEVELPRESSURE);
	if (isnan(a)) {    
		Serial.println("Failed to read from BME28 sensor");
		return "--";
	}
	else {
		Serial.print("Approx. Altitude = ");
		Serial.print(a);
		return String(a);
	}
}

// Function to display title and readings
void displayInfo(String title, String reading) {
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
	display.println(title);
	display.setTextSize(2);
	display.setCursor(0, 32);
	display.println(reading);
	display.display();
	display.clearDisplay();
}

void setup() {
	Serial.begin(115200);
	
	unsigned status;
	status = bme.begin(0x76); // I2C address of BME280
	if (!status) {
		Serial.println("BME280 sensor not found.");
		while (1);
	}
	
	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // I2C address for SSD1306 display
		Serial.println(F("SSD1306 allocation failed"));
		for(;;);
	}
	
	// Clear the buffer
	display.clearDisplay();
	
	// Boot message
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
	display.println("Welcome to");
	display.println("Electronic");
	display.println("Enabling");
	display.println("Club");
	display.display();
	delay(10000);	
	display.clearDisplay();
	
	// Set delay time (15000 = 15 sec)
	delayTime = 15000;	
}

void loop() {
	
	// Read temperature, humidity and pressure for display
	String temperatureReading = readBME280Temperature() + + " " + char(247) + "C";
	String humidityReading = readBME280Humidity()  + " %";
	String pressureReading = readBME280Pressure() + " hPa";
	String altitudeReading = readBME280Altitude()  + " m";
	
	// Passing values to display function and delay.
	displayInfo("Temp", temperatureReading);
	delay(delayTime);
	displayInfo("Humidity", humidityReading);
	delay(delayTime);
	displayInfo("Pressure", pressureReading);
	delay(delayTime);
	displayInfo("Altitude", altitudeReading);
	delay(delayTime);
}
