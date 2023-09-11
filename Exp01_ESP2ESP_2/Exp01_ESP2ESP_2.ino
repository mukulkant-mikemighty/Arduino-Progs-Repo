/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/communication-between-two-esp32
 */

// ESP32 #2: TCP SERVER + AN LED
#include <SPI.h>
#include <Ethernet.h>
//#include <WiFi.h>
#define LED_PIN  7
#define SERVER_PORT 4

byte mac[] = {0xB8, 0xD6, 0x1A, 0x47, 0x63, 0x04};//WiFi.macAddress();B8:D6:1A:47:63:04//{0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};//B8:D6:1A:47:63:04 //B8:D6:1A:47:63:04
EthernetServer TCPserver(SERVER_PORT);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("ESP32 #2: TCP SERVER + AN LED");

  // Initialize Ethernet Shield:
  if (Ethernet.begin(mac) == 0)
    Serial.println("ESP32 #2: Failed to configure Ethernet using DHCP");

  // Print your local IP address:
  Serial.print("ESP32 #2: TCP Server IP address: ");
  Serial.println(Ethernet.localIP());
  Serial.println("ESP32 #2: -> Please update the serverAddress in ESP32 #1 code");

  // Listening for a TCP client (from ESP32 #1)
  TCPserver.begin();
}

void loop() {
  // Wait for a TCP client from ESP32 #1:
  EthernetClient client = TCPserver.available();

  if (client) {
    // Read the command from the TCP client:
    char command = client.read();
    Serial.print("ESP32 #2: - Received command: ");
    Serial.println(command);

    if (command == '1')
      digitalWrite(LED_PIN, HIGH); // Turn LED on
    else if (command == '0')
      digitalWrite(LED_PIN, LOW);  // Turn LED off

    Ethernet.maintain();
  }
}
