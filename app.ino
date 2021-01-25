//Create a simple web server using ESP8266 and the WiFiEsp library to control a single led.
//#include "Config.hpp"
#include "WebHandler.hpp"
#include "Config.hpp"
#include "WiFiEsp.h"
#define LEDPIN 2

//#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial SerialESP(9, 8); // TX, RX of ESP connected to these Uno Pins
//#endif

Config config;
int wifistatus = WL_IDLE_STATUS;
int serverstatus = 0;
WiFiEspServer server(80); //Web server at port 80
WebHandler webHandler;
//int ledStatus = LOW;
//RingBuffer buf(8);
void setup()
{
  pinMode(LEDPIN, OUTPUT);

  Serial.begin(115200);  // initialize serial for debugging
  SerialESP.begin(9600); // initialize serial for ESP module

  //Read config file from SD card
  config.init();

  WiFi.init(&SerialESP); // initialize ESP module and use this serial connection
  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present!");
    // don't continue
    while (true);
  }
  // attempt to connect to WiFi network
  while (wifistatus != WL_CONNECTED)
  {
    Serial.print("Connecting to WPA SSID: ");
    Serial.println(config.getSSID());
    //Serial.println(config.getPass());
    // Connect to WPA/WPA2 network
    wifistatus = WiFi.begin(config.getSSID(), config.getPass());
  }
  Serial.print("Connected! Local IP: ");
  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  // start the web server on port 80
  server.begin();
  serverstatus = 1;
}

void loop()
{
  webHandler.handleLoop(server);
}
