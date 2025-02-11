namespace Pins
{
    // Error Handler Manager Pins
    namespace ErrorHandler
    {
        inline constexpr int heartbeat { 2 };
    }
    
    // Enviro Readings Manager Pins
    namespace EnviroReadings
    {
        inline constexpr int chipSelect { 5 };
        inline constexpr int spiClock { 18 };
        inline constexpr int miso { 19 };   // Master Input, Slave Output
        inline constexpr int mosi { 23 };   // Master Output, Slave Input
    }
}