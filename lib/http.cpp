// Custom library for HTTP GET and POST requests to Home Assistant server
// Decided to NOT be use HTTP for this project, in favor of MQQT for faster communciation and better Home Assistant support

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "api.h"
#include "credentials.h"
#include "identifiers.h"

static HTTPClient httpEspClient;

void httpGet()
{
    httpEspClient.begin(Credentials::getDestination);
    int httpStatusCode = httpEspClient.GET();

    if (httpStatusCode > 0)
    {
        Serial.printf("HTTP Status Code: %d\n", httpStatusCode);
        String getResponse = httpEspClient.getString();
        Serial.println(getResponse);
    } 
    else
    {
        Serial.printf("GET request failed with Status Code: %d\n", httpStatusCode);
    }

    httpEspClient.end();
}

void httpPostEnviron(const char* postDest, String state, String unitOfMeasurement, String friendlyName)
{
    httpEspClient.begin(postDest);
    String bearerToken = "Bearer " + String(Api::homeAssistantApiKey);
    httpEspClient.addHeader("Authorization", bearerToken);
    httpEspClient.addHeader("Content-Type", "application/json");

    // Prepare the JSON payload to POST
    StaticJsonDocument<200> jsonPayload;
    jsonPayload["state"] = state;
    jsonPayload["attributes"]["unit_of_measurement"] = unitOfMeasurement;
    jsonPayload["attributes"]["friendly_name"] = friendlyName;

    String jsonString;
    serializeJson(jsonPayload, jsonString); // Serialize as a String to be posted

    int httpStatusCode = httpEspClient.POST(jsonString); // Post JSON to destination as serialized String

    if (httpStatusCode > 0)
    {
        Serial.printf("HTTP Status Code: %d\n", httpStatusCode);
        String response = httpEspClient.getString();
        Serial.println(response);
    }
    else
    {
        Serial.printf("POST request failed with Status Code: %d\n", httpStatusCode);
    }
    httpEspClient.end();
}