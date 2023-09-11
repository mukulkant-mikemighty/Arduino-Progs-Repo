#include "ThingSpeak.h"
#include <WiFi.h>    //#include "DHT.h"
#define SECRET_SSID "BITS-IAE-LAB"    // replace MySSID with your WiFi network name
#define SECRET_PASS "bits@123"  // replace MyPassword with your WiFi password
#define SECRET_CH_ID 2034234     // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "4LVL13NPVEWKOSKC"   // replace XYZ with your channel write API Key

char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;
//char thingSpeakAddress[] = "api.thingspeak.com";
WiFiClient client;
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
//const int updateThingSpeakInterval = 20 * 1000;
const int ledPin1 = 13;
const int ldrPin1 = 4;




void setup() {
  Serial.begin(115200);  //Initialize serial
  //Serial.println(F("ldrStatus test!"));
  pinMode(ledPin1, OUTPUT);
  pinMode(ldrPin1, INPUT);
//  WiFi.mode(WIFI_STA);  
//  ThingSpeak.begin(client);  // Initialize ThingSpeak
}
void loop() {  // Connect or reconnect to WiFi

/*  if(WiFi.status() != WL_CONNECTED){

    Serial.print("Attempting to connect to SSID: ");

    Serial.println(SECRET_SSID);

    while(WiFi.status() != WL_CONNECTED){

      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network

      Serial.print(".");

      delay(5000);    

    }

    Serial.println("\nConnected.");

  }
*/
  int ldrStatus1 = analogRead(ldrPin1);//gpio_input_get()//analogRead(ldrPin1);
  if (ldrStatus1 >= 200) {
    digitalWrite(ledPin1, LOW);
    Serial.printf("Its BRIGHT, Turn off the LED : %d \n",ldrStatus1);
  } 
  else {
    digitalWrite(ledPin1, HIGH);
    Serial.printf("Its DARK, Turn on the LED : %d \n",ldrStatus1);
  }
  delay(2000);

}