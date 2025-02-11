// Manager for:
// Initializing error handling-related items
// Creating a task that deals with error handling and other related functionality, including:
    // ErrorHandler timer
    // Error logging (WIP)

#include <Arduino.h>
#include "constants.h"
#include "identifiers.h"
#include "pins.h"

using namespace Pins::ErrorHandler; // Using directive for manager-relevant pin access

void errorHandlerTaskCreate();

void errorHandlerInit()
{
    Serial.printf("ErrorHandler Manager Version %.2f\n", Identifiers::errorHandlerManagerVersion);

    errorHandlerTaskCreate();

    Serial.println("All Error Handler Manager Tasks created successfully!");
    Serial.println(Constants::separator);
}

void heartbeatTask(void *param);

// Create tasks relating to error handling (heartbeat, error logging (WIP), and more)
void errorHandlerTaskCreate()
{
    xTaskCreate(
        heartbeatTask,
        "Heartbeat Task",
        1024,
        nullptr,
        1,
        nullptr
    );

    Serial.println("Heartbeat Task created successfully!");

    /* Error logging to be created in future update
     xTaskCreate(
        errorLoggingTask,
        "Error Logging Task",
        1024,
        nullptr,
        1,
        nullptr
    ); 

    Serial.println("Error Logging Task created successfully!"); */
}

void heartbeatCallback(TimerHandle_t xTimer);

// Task for device heartbeat and other led-related features?!
void heartbeatTask(void *param)
{
    pinMode(heartbeat, OUTPUT);
    TimerHandle_t heartbeatTimer;

    heartbeatTimer = xTimerCreate(
        "Heartbeat Timer",
        Constants::heartbeatTime,
        pdTRUE,
        nullptr,
        heartbeatCallback

    );
    xTimerStart(heartbeatTimer, 0);

    while (true); // Loop forever while timer executes and calls the callback function
}

// Callback function to be called when the timer expires
void heartbeatCallback(TimerHandle_t xTimer)
{
    digitalRead(heartbeat) ? digitalWrite(heartbeat, LOW) : digitalWrite(heartbeat, HIGH);
}

// FUTURE PLANNED FEATURE/TASK... HTTP POST to Home Assistant?
void errorLoggingTask(void *param)
{

}