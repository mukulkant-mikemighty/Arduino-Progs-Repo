#define BLYNK_TEMPLATE_ID "TMPLHJt95W9j"
#define BLYNK_TEMPLATE_NAME "PPT"
#define BLYNK_AUTH_TOKEN "aErKtjCwjn0kJdiSQBecZYv9tr7PqDxd"
const int ledPin = 23;
const int ldrPin = 34;

#include "DHT.h"
#define DHTPIN 5     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Vennishmuthu";
char pass[] = "Muthu123";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes

// LED Control
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
 // Blynk.virtualWrite(V1, value);
  if (value == 1)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
     digitalWrite(ledPin, LOW);
  }
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}



void setup()
{
  
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  dht.begin();
}

void loop()
{
    int ldrStatus = analogRead(ldrPin);
     Serial.println(ldrStatus);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
/*
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  */
  Blynk.virtualWrite(V1, ldrStatus);
  Blynk.virtualWrite(V2, t);
   Blynk.virtualWrite(V3, h);
Serial.println(t);

if (ldrStatus < 35)
{
   Blynk.logEvent("emergency");
   delay(500);
}

delay(300);
  Blynk.run();
  timer.run();
 
}