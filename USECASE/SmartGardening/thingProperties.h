#include <ArduinoIoTCloud.h>  // LIBRARY NEEDS TO BE INSTALLED
#include <Arduino_ConnectionHandler.h>  // LIBRARY NEEDS TO BE INSTALLED
// Additional LIBRARY: ArduinoHttpClient
#include "arduino_secrets.h"

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)

void onTemperatureChange();
void onHumidityChange();
void onSoilMoistureChange();

float Temp;
float Hum;
float SoilMoisture;

void initProperties(){
  ArduinoCloud.addProperty(Temp, READWRITE, ON_CHANGE, onTemperatureChange);
  ArduinoCloud.addProperty(Hum, READWRITE, ON_CHANGE, onHumidityChange);
  ArduinoCloud.addProperty(SoilMoisture, READWRITE, ON_CHANGE, onSoilMoistureChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);