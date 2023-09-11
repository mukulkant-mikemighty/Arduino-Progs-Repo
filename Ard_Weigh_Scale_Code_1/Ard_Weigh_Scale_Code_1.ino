//Program code for digital weighing scale using Arduino and HX711 with load cell
#include <LiquidCrystal_I2C.h>
#include "HX711.h"
 
#define DEBUG_HX711
 
// calibration parameter from calibrating code with known values
#define CALIBRATION_FACTOR 13389//20780.0

// Create the lcd object address 0x3F and 16 columns x 2 rows 
LiquidCrystal_I2C lcd (0x3F, 16,2);
 
// data pin and clock pin
byte pinData = 3;
byte pinClk = 2;
 
// define HX711
HX711 scale;
 
void setup() {

  lcd.init();
  lcd.backlight();
  lcd.print( "WEIGHT SCALE" );
 
#ifdef DEBUG_HX711
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("[HX7] Sensor start HX711");
#endif
 
  //Initializing sensor
  scale.begin(pinData, pinClk);
  // apply the calibration value
  scale.set_scale(CALIBRATION_FACTOR);
  // Initialize the tare
  //Assuming there is no weight on the scale at start up, reset the scale to 0
  scale.tare();
}
 
void loop() {
#ifdef DEBUG_HX711
  Serial.print("[HX7] Reading: ");
  Serial.print(scale.get_units(), 2);
  Serial.print(" Kgs");
  Serial.println();
#endif
lcd.setCursor (0, 1);
lcd.print( "Reading:" );
lcd.print(scale.get_units(), 2);
lcd.print(" Kgs");
}