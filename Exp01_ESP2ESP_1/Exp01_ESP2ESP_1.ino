/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/communication-between-two-esp32
 */

// ESP32 #1: TCP CLIENT + A BUTTON/SWITCH
#include <ezButton.h>
#include <SPI.h>
#include <Ethernet.h>

#define BUTTON_PIN  7
#define SERVER_PORT  4080

ezButton button(BUTTON_PIN);  // create ezButton that attach to pin 7;

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x03};
IPAddress serverAddress(0, 0, 0, 0);
EthernetClient TCPclient;

void setup() {
  Serial.begin(115200);
  button.setDebounceTime(50); // set debounce time to 50 milliseconds

  Serial.println("ESP32 #1: TCP CLIENT + A BUTTON/SWITCH");

  // Initialize Ethernet Shield:
  if (Ethernet.begin(mac) == 0)
    Serial.println("ESP32 #1: Failed to configure Ethernet using DHCP");

  // connect to TCP server (ESP32 #2 )
  if (TCPclient.connect(serverAddress, SERVER_PORT))
    Serial.println("ESP32 #1: Connected to TCP server");
  else
    Serial.println("ESP32 #1: Failed to connect to TCP server");
}

void loop() {
  button.loop(); // MUST call the loop() function first

  if (!TCPclient.connected()) {
    Serial.println("ESP32 #1: Connection is disconnected");
    TCPclient.stop();

    // reconnect to TCP server (ESP32 #2)
    if (TCPclient.connect(serverAddress, SERVER_PORT))
      Serial.println("ESP32 #1: Reconnected to TCP server");
    else
      Serial.println("ESP32 #1: Failed to reconnect to TCP server");
  }

  if (button.isPressed()) {
    TCPclient.write('1');
    TCPclient.flush();
    Serial.println("ESP32 #1: - The button is pressed,  sent command: 1");
  }

  if (button.isReleased()) {
    TCPclient.write('0');
    TCPclient.flush();
    Serial.println("ESP32 #1: - The button is released, sent command: 0");
  }
}
