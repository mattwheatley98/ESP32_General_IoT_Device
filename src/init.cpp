// App-Wide Initializations
#include <Arduino.h>
#include "constants.h"
#include "enviro_readings_manager.h"
#include "error_handler_manager.h"
#include "mqtt_manager.h"
#include "wifi_manager.h"

void initDevice()
{
    Serial.begin(9600);
    Serial.printf("\n%s\n", Constants::separator);
    Serial.println("Initializing Tasks...");
    Serial.printf("%s\n", Constants::separator);

    errorHandlerInit(); // Initialize Error Handler Manager
    wiFiInit(); // Initialize WiFi Manager
    mqttInit(); // Initialize MQTT Manager
    enviroReadingsInit(); // Initialize Enviro Readings Manager
}