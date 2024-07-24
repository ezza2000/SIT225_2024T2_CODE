#include "thingProperties.h"
#include <DHT.h>
#define DHTPIN 2  // digital pin number
#define DHTTYPE DHT11 // DHT type 11 or 22
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(1500); 

  dht.begin();
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(0);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  Hum = dht.readHumidity();
  Temp = dht.readTemperature();
  // Your code here 
  
  Serial.println("Temperature: " + String(Temp));
  Serial.println("Humidity: " + String(Hum));
  delay(5000);
}

/*
  Since Temperature is READ_WRITE variable, onRandomTemperatureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTemperatureChange()  {
  // Add your code here to act upon Temperature change
  Serial.println("--onTemperatureChange");
}
void onHumidityChange()  {
  // Add your code here to act upon Temperature change
  Serial.println("--onHumidityChange");
}
