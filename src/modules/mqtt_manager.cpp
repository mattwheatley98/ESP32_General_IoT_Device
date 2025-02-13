// Manager for:
// Connecting to MQTT broker
// Creating a task that maintains the persistent client connection to the broker (WIP)

#include <Arduino.h>
#include <mqtt_client.h>
#include "constants.h"
#include "credentials.h"
#include "identifiers.h"

// Configure MQTT client
// Done in file scope for EXTERNING the handle to other files for publishing
esp_mqtt_client_config_t clientConfig = 
{
    .uri = Credentials::mqttBroker,
    .client_id = Identifiers::deviceName,
    .username = Credentials::mqttUsername,
    .password = Credentials::mqttPassword,
    .protocol_ver = esp_mqtt_protocol_ver_t::MQTT_PROTOCOL_V_3_1_1, // No MQTT 5.0 enum? Outdated component?
};

// Externed in other files
esp_mqtt_client_handle_t mqttClientHandle = esp_mqtt_client_init(&clientConfig);

void mqttTaskCreate();

void mqttInit()
{
    Serial.printf("MQTT Manager Version %.2f\n", Identifiers::mqttManagerVersion);

    // Connect to MQTT broker
    while (esp_mqtt_client_start(mqttClientHandle) != ESP_OK)
    {
        Serial.println("Connecting to MQTT broker...");
        delay(2000);
    }

    Serial.println("Connected to MQTT broker!");

    // mqttTaskCreate();

	// Serial.println("\nMQTT Task created successfully!");
	Serial.println(Constants::separator); 
}





// All of the below is a WIP for MQTT error handling... creating a dedicated task for that

void mqttTask(void *param);

void mqttTaskCreate()
{
    xTaskCreate(
        mqttTask,
        "MQTT Manager Task",
        1024,
        nullptr,
        1,
        nullptr
    );
}

void mqttEventHandler();

// Task for handling the MQTT connections and that alone?! MQTT publishing relegated to library
void mqttTask(esp_mqtt_client_handle_t mqttClientHandle, esp_mqtt_event_id_t eventType, esp_event_handler_t callback, esp_event_handler_t args)
{
    // Event handler
    //esp_mqtt_client_register_event(mqttClientHandle, eventType, callback, args);

    while (true)
    {
        /* code */
    }
    
}

void mqttEventHandler(void *handlerArgs, esp_event_base_t base, int32_t eventType, void *eventData)
{

}