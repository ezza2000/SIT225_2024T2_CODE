#include <WiFiNINA.h>
#include "secrets.h"
#include <Wire.h>
#include "thingProperties.h"
#include <DHT.h>
#define DHTPIN 2  // digital pin number
#define DHTTYPE DHT11 // DHT type 11 or 22
DHT dht(DHTPIN, DHTTYPE);
#define SOIL_MOISTURE_PIN A0 

// WiFi Credentials from secrets.h
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient client;
String myStatus = "";

// IFTTT Settings
char HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME_TEMP = "/trigger/TemperatureChange/json/with/key/nkZi0do5cYUir1rOhQgJsUDE-pvqVATTkan8rgT40oc";
String QUERY_STRING_TEMP = "";
String PATH_NAME_SOIL = "/trigger/DrySoil/with/key/nkZi0do5cYUir1rOhQgJsUDE-pvqVATTkan8rgT40oc";
String QUERY_STRING_SOIL = "";
bool tempRequestMade = false;
bool soilRequestMade = false;

void setup() 
{
  // Initialize WiFi connection
  WiFi.begin(ssid, pass);
  
  // Initialize the I2C bus
  Wire.begin();
  
  Serial.begin(9600);
  delay(1500); 

  dht.begin();
  

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(0);
  ArduinoCloud.printDebugInfo();
}

void makeRequest(String path, String query) {
  if (client.connect(HOST_NAME, 80)) {
    Serial.println("Connected to server");
    
    String request = "GET " + path + query + " HTTP/1.1\r\n" + 
                     "Host: " + String(HOST_NAME) + "\r\n" + 
                     "Connection: close\r\n\r\n";
    
    Serial.println("Request Sent: ");
    Serial.println(request);  // Print the full request
    
    client.print(request);
    
    // Wait for the server response with a timeout of 5 seconds
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println("Timeout occurred while waiting for response");
        client.stop(); // Stop the client if timeout occurs
        return;
      }
    }
  } else {
    Serial.println("Connection to server failed");
    return;
  }

  // Read and print the response from the server
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
  }

  client.stop();
  Serial.println();
  Serial.println("Disconnected");
}


void loop() {
  ArduinoCloud.update();

  
  
  // Debugging: Print raw analog reading
  Hum = dht.readHumidity();
  Temp = dht.readTemperature();
  int SoilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  SoilMoistureValue = map(SoilMoistureValue, 63, 120, 0, 100);
  SoilMoisture = SoilMoistureValue;
  
  Serial.println("Temperature: " + String(Temp));
  Serial.println("Humidity: " + String(Hum));
  Serial.print(SoilMoisture);
  Serial.println(" %");
  if (Temp > 20 && !tempRequestMade) {
    QUERY_STRING_TEMP = "?value1=" + String(Temp) + "&value2=" + String(Hum) + "&value3=" + String(SoilMoisture);
    makeRequest(PATH_NAME_TEMP, QUERY_STRING_TEMP);
    tempRequestMade = true; // Avoid sending multiple requests in a row
    Serial.println("IFTTT Triggered: High Temperature");
  }
  if (SoilMoisture < 20 && !soilRequestMade) {
    QUERY_STRING_SOIL = "?value1=" + String(Temp) + "&value2=" + String(Hum) + "&value3=" + String(SoilMoisture);
    makeRequest(PATH_NAME_SOIL, QUERY_STRING_SOIL);
    soilRequestMade = true; // Avoid sending multiple requests in a row
    Serial.println("IFTTT Triggered:Dry Soil");
  }
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

void  onSoilMoistureChange() {
  Serial.println("--onSoilMoistureChange");
}

