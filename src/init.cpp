// App-Wide Initializations
#include <Arduino.h>
#include "constants.h"
#include "enviro_readings_manager.h"
#include "error_handler_manager.h"
#include "wifi_manager.h"

void initDevice()
{
    Serial.begin(9600);
    Serial.printf("\n%s\n", Constants::separator);
    Serial.println("Initializing Tasks...");

    errorHandlerInit(); // Initialize Error Handler Manager
    wiFiInit(); // Initialize ErrorHandler Manager
    enviroReadingsInit(); // Initialize Enviro Readings Manager
}