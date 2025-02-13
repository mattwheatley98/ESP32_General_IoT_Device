#pragma once
#include <mqtt_client.h> // ENCAPSULATE THIS TO THE HEADER FILE ONLY!!!

void mqttPublish(const char* deviceName, esp_mqtt_client_handle_t clientHandle, const char* topic, const char* payload);