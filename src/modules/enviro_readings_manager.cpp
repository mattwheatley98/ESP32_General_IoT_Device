// Manager for:
// Initializing a BME280 sensor to be used with SPI 
// Creating a task that handles temperature, humidity, and atmospheric pressure readings, as well as MQTT publishings

#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <SPI.h>
#include "constants.h"
#include "identifiers.h"
#include "pins.h"
#include "mqtt_lib.h" // Exposes the entire mqtt_client library... encapsulate it
#include "topics.h"

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
    // Create task to continually read and publish BME280 sensor data
    xTaskCreate(
        enviroReadingsTask,
        "Enviro Readings Task",
        4096, // Larger stack size needed for readings and MQTT
        nullptr,
        1,
        nullptr
    );
}

// Task for reading temperature, humidity, and pressure from BME280 and publishing it
void enviroReadingsTask(void *param)
{
	extern esp_mqtt_client_handle_t mqttClientHandle;

	// Converting sensor readings from Floats to Strings, then to C-Style Strings for MQTT publishing (will polish with eventual Serial reading removal)
	float temperatureF; String temperatureFString; 
	float humidity; 	String humidityString;
	float pressure; 	String pressureString;

	while (1)
	{
		temperatureF = (sensor.readTemperature() * 9.0 / 5.0) + 32;  // Convert celsius reading to fahrenheit
		temperatureFString = temperatureF; 
		Serial.print("Temp in °F: ");
		Serial.println(temperatureF);
		mqttPublish(Identifiers::deviceName, mqttClientHandle, Topics::temperatureTopic, temperatureFString.c_str()); // Convert String to C-style String

		humidity = sensor.readHumidity();
		humidityString = humidity;
		Serial.print("Humidity: ");
		Serial.print(humidity);
		Serial.println(" %");
		mqttPublish(Identifiers::deviceName, mqttClientHandle, Topics::humidityTopic, humidityString.c_str());

		pressure = sensor.readPressure() / 100.0F; // Convert Pa to hPa
		pressureString = pressure;
		Serial.print("Pressure: ");
		Serial.print(pressure); 
		Serial.println(" hPa\n");
		mqttPublish(Identifiers::deviceName, mqttClientHandle, Topics::pressureTopic, pressureString.c_str());

		delay(2000); // Read and publish every 2 seconds
	}
}