/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-client-server-wi-fi/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebSrv.h"
#include "DHT.h"
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>

// Set your access point network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

DHT dht(DHTPIN, DHTTYPE);

/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

//Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

// Create AsyncWebServer object on port 80


AsyncWebServer server(80);
/*
String readTemp() {
  return String(bme.readTemperature());
  //return String(1.8 * bme.readTemperature() + 32);
}

String readHumi() {
  return String(bme.readHumidity());
}

String readPres() {
  return String(bme.readPressure() / 100.0F);
}
*/

String readTemp() {
  return String(dht.readTemperature());
  //return String(1.8 * bme.readTemperature() + 32);
}

String readHumi() {
  return String(dht.readHumidity());
}



void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  dht.begin();
/*
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTemp().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readHumi().c_str());
  });
  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readPres().c_str());
  });
  */

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTemp().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readHumi().c_str());
  });
  
  bool statusHumidity;
  bool statusTemperature;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  statusHumidity = dht.readHumidity();
  statusTemperature= dht.readTemperature();
  if (!(statusHumidity || statusTemperature)) {
    Serial.println("Could not find a valid DHT sensor, check wiring!");
    while (1);
  }
  
  // Start server
  server.begin();
}
 
void loop(){
  
}

void webpage(WiFiClient browser) { /* function webpage */
 	////Send webpage to browser
 	browser.println("HTTP/1.1 200 OK");
 	browser.println("Content-Type: text/html");
 	browser.println(""); // 	do not forget this one
 	browser.println("<!DOCTYPE HTML>");
 	browser.println("<html>");
 	browser.println("<head>");
 	browser.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
 	browser.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
 	browser.println("</head>");
 	browser.println("<body style = ' background-color:#000000; color:white;'>");
 	browser.println("<hr/><hr>");
 	browser.println("<h1><center> Esp32 Electrical Device Control </center></h1>");
 	browser.println("<hr/><hr>");
 	browser.println("<br><br>");
 	browser.println("<br><br>");
 	/*browser.println("<h2> Commands </h2>");
 	browser.println("<center>");
 	browser.println("Built-in LED");
 	browser.println("<a href='/light1on'><button>Turn On </button></a>");
 	browser.println("<a href='/light1off'><button>Turn Off </button></a><br />");
 	browser.println("</center>");
 	browser.println("<br><br>");
 	browser.println("<center>");
 	browser.println("Device 2");
 	browser.println("<a href='/light2on'><button>Turn On </button></a>");
 	browser.println("<a href='/light2off'><button>Turn Off </button></a><br />");
 	browser.println("</center>");
 */	browser.println("<br><br>");
 	browser.println("<br><br>");
 	browser.println("<h2> Data </h2>");
 	browser.println("<center>");
 	browser.println("<table border='5'>");
 	browser.println("<tr>");
 	if (digitalRead(LED))
 	{
 			browser.print("<td>LED is OFF</td>");
 	}
 	else
 	{
 			browser.print("<td>LED is ON</td>");
 	}
 	browser.println("<br />");
 	if (slaveState == "1") //(digitalRead(4))
 	{
 			browser.print("<td>Light 2 is OFF</td>");
 	}
 	else
 	{
 			browser.print("<td>Light 2 is ON</td>");
 	}
 	browser.println("</tr>");
 	browser.println("</table>");
 	browser.println("</center>");
 	browser.println("</body></html>");
 	delay(1);
}
