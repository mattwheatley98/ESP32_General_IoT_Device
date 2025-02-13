// Namespace for MQTT topics

namespace Topics
{
    // BME280-related topics
    inline constexpr char* bme280Topic = { "homeassistant/sensors/bme280" };
    inline constexpr char* temperatureTopic = { "homeassistant/sensors/temperature" };
    inline constexpr char* humidityTopic = { "homeassistant/sensors/humidity" };
    inline constexpr char* pressureTopic = { "homeassistant/sensors/pressure" };

}