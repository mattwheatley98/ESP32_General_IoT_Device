// Custom library for MQTT publishing

#include <Arduino.h>
#include <mqtt_client.h>

// Publish a payload
void mqttPublish(const char* deviceName, esp_mqtt_client_handle_t clientHandle, const char* topic, const char* payload)
{
    // Define C-Style String then format/"concatenate" the topic with device name for a device-specific topic
    char topicDeviceConcat[256];
    snprintf(topicDeviceConcat, sizeof(topicDeviceConcat), "%s/%s", topic, deviceName);

    esp_mqtt_client_publish(
        clientHandle,
        topicDeviceConcat,
        payload,
        0, // Length of message (0 will calculate from payload automatically)
        0, // QoS of message
        false // Retain flag
    );
}