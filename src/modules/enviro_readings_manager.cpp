// Manager for:
// Initializing a BME280 sensor to be used with SPI 
// Creating a task that handles temperature, humidity, and atmospheric pressure readings

#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <SPI.h>
#include "constants.h"
#include "identifiers.h"
#include "pins.h"

using namespace Pins::EnviroReadings; // Using directive for manager-relevant pin access

Adafruit_BME280 sensor(chipSelect, mosi, miso, spiClock);

void enviroReadingsTaskCreate();

void enviroReadingsInit()
{
	Serial.printf("Enviro Readings Manager (SPI) Version %.2f\n", Identifiers::environReadingsVersion);

	Serial.println("Utilizing the following pins for readings: \n");
	Serial.printf("Chip Select: %d\n", chipSelect);
	Serial.printf("SPI Clock: %d\n", spiClock);
	Serial.printf("MISO: %d\n", miso);
	Serial.printf("MOSI: %d\n\n", mosi); // Intentional skipping of two lines

	// Initialize BME280 sensor for SPI
	digitalWrite(chipSelect, LOW);
	if (!sensor.begin())
	{
		Serial.println("Could not find a valid BME280 sensor...");
		while (1); // Stop execution if sensor is not found
	}

	enviroReadingsTaskCreate();

	Serial.println("Enviro Readings Task created successfully!");
	Serial.println(Constants::separator);
}

void enviroReadingsTask(void *param);

void enviroReadingsTaskCreate()
{
    // Create task to continually read BME280 sensor data
    xTaskCreate(
        enviroReadingsTask,
        "Enviro Readings Task",
        2048, // Larger stack size
        nullptr,
        1,
        nullptr
    );
}

// Task for reading temperature, humidity, and pressure from BME280
void enviroReadingsTask(void *param)
{
	float temperatureF;
	float humidity;
	float pressure;

	while (1)
	{
		// Would use printf, but the Arudino libraries seems to not like the floating points here and string conversions would be awk :(
		temperatureF = (sensor.readTemperature() * 9.0 / 5.0) + 32;  // Convert celsius reading to fahrenheit
		Serial.print("Temp in °F: ");
		Serial.println(temperatureF);

		humidity = sensor.readHumidity();
		Serial.print("Humidity: ");
		Serial.print(humidity);
		Serial.println(" %");

		pressure = sensor.readPressure() / 100.0F; // Convert Pa to hPa
		Serial.print("Pressure: ");
		Serial.print(pressure); 
		Serial.println(" hPa\n");

		delay(2000); // Read every 2 seconds
	}
}