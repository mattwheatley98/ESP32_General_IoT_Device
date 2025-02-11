// Entry point for setting up ESP32s for various uses with Home Assistant
// Next feature to implement is MQQT as a much-needed replacement for HTTP... 
	// Learned that HTTP is not ideal for IoT and it lacks a lot of Home Assistant support

void initDevice();

void setup() 
{
	initDevice();
}

void loop() {
	; // Intentionally left blank
}