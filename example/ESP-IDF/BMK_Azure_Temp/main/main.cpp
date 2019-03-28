/*
 * 1. Open up the project properties
 * 2. Visit C/C++ General > Preprocessor Include Paths, Macros, etc
 * 3. Select the Providers tab
 * 4. Check the box for "CDT GCC Built-in Compiler Settings"
 * 5. Set the compiler spec command to "xtensa-esp32-elf-gcc ${FLAGS} -E -P -v -dD "${INPUTS}""
 * 6. Rebuild the index
*/

#include <esp_log.h>
#include "sdkconfig.h"
#include <Wire.h>
#include "Arduino.h"
#include "Esp32MQTTClient.h"
#include "Adafruit_MCP9808.h"
#include <WiFi.h>
#include <string>

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

// Please input the SSID and password of WiFi
const char* ssid     = "ssid";
const char* password = "password";
static const char* connectionString = "AZURE STRING HERE";
static bool hasIoTHub = false;



extern "C" {
	void app_main(void);
}



void setup()
{
	 Serial.begin(115200);
	  Wire.begin(33,32); //sda 33,scl 32
	  Serial.println("Starting connecting WiFi.");
	  delay(10);
	  WiFi.begin(ssid, password);
	  while (WiFi.status() != WL_CONNECTED) {
	    delay(500);
	    Serial.print(".");
	  }
	  Serial.println("WiFi connected");
	  Serial.println("IP address: ");
	  Serial.println(WiFi.localIP());

	  if (!Esp32MQTTClient_Init((const uint8_t*)connectionString))
	  {
	    hasIoTHub = false;
	    Serial.println("Initializing IoT hub failed.");
	    return;
	  }
	  hasIoTHub = true;

	  if (!tempsensor.begin())
	  {
	  Serial.println("Couldn't find MCP9808!");
	  while (1);
	  }
}



void app_main(void)
{
	initArduino();
	Serial.begin(115200);
	setup();

	//Serial.print("In main before loop ");
	while(1)
	{
		Serial.println("start sending events.");
		  if (hasIoTHub)
		  {
		    char buff[128];
		    //temporarily holds data from c temp conversion to Azure
		    char charTempC[10];
		    // Read and print out the temperature, then convert to *F
		    float c = tempsensor.readTempC();
		    float f = c * 9.0 / 5.0 + 32;
		    String temperature = String(c);
		    Serial.print("Temp: ");
		    Serial.print(c);
		    Serial.print(" C\t");
		    Serial.print(f);
		    Serial.println(" F");
		    //4 is mininum width, 2 is precision; float value is copied onto buff
		    dtostrf(c, 4, 2, charTempC);
		    // replace the following line with your data sent to Azure IoTHub
		    snprintf(buff, 128, charTempC);
		    delay(250);

		    tempsensor.shutdown_wake(1);
		    delay(2000);
		    tempsensor.shutdown_wake(0);

		    if (Esp32MQTTClient_SendEvent(buff))
		    {
		      Serial.println("Sending data succeed");

		    }
		    else
		    {
		      Serial.println("Failure...");
		    }
		    delay(3000);
		  }
	}
}

