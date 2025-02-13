// Manager for:
// Connecting to WiFi
// Creating a task that maintains the connection to WiFi

#include <WiFi.h>
#include "constants.h"
#include "credentials.h"
#include "identifiers.h"

void wiFiTaskCreate();

void wiFiInit()
{
    Serial.printf("WiFi Manager Version %.2f\n", Identifiers::wifiManagerVersion);

    // Set hostname and mode
    WiFi.setHostname(Identifiers::deviceName);
    WiFi.mode(WIFI_STA);

    // Start connecting to WiFi
    WiFi.begin(Credentials::ssid, Credentials::password);
    Serial.println("Connecting to WiFi...");

    // Wait for successful connection
    while (WiFi.status() != WL_CONNECTED) 
    {     
        Serial.println("Connecting...");
        delay(500);
    }

    Serial.println("Connected to WiFi!\n");
    Serial.printf("Network name: %s\n", WiFi.SSID());
    Serial.print("Assigned IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.printf("Acknowledged host name: %s\n", WiFi.getHostname());

    wiFiTaskCreate();

	Serial.println("\nWiFi Task created successfully!");
	Serial.println(Constants::separator);
}

void wiFiTask(void *param);

void wiFiTaskCreate()
{
    // Create task to maintain WiFi connection (reconnect if disconnected)
    xTaskCreate(
        wiFiTask,
        "WiFi Task",
        2048, // Larger stack size
        nullptr,
        1,
        nullptr
    );
}

// Task for maintaining WiFi connection and reconnecting if disconnected
void wiFiTask(void *param) 
{  
    while (true)
    {
        // Attempt to reconnect to WiFi
        if (WiFi.status() != WL_CONNECTED) 
        {
            Serial.println("Disconnected from WiFi! Reconnecting...");
            WiFi.reconnect();
            if (WiFi.status() == WL_CONNECTED)
            {
                Serial.println("Connection reestablished!\n");
            }
        }
    delay(5000);  // Attempt reconnection every 5 seconds
    }
}