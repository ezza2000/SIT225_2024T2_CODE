#include <ArduinoIoTCloud.h>  // LIBRARY NEEDS TO BE INSTALLED
#include <Arduino_ConnectionHandler.h>  // LIBRARY NEEDS TO BE INSTALLED
// Additional LIBRARY: ArduinoHttpClient
#include "arduino_secrets.h"

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)

void onTemperatureChange();
void onHumidityChange();

float Temp;
float Hum;

void initProperties(){
  ArduinoCloud.addProperty(Temp, READWRITE, ON_CHANGE, onTemperatureChange);
  ArduinoCloud.addProperty(Hum, READWRITE, ON_CHANGE, onHumidityChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);