const int ledPin1 = 13;
const int ldrPin1 = 2;


void setup() {
  Serial.begin(115200);  //Initialize serial
  //Serial.println(F("ldrStatus test!"));
  pinMode(ledPin1, OUTPUT);
  pinMode(ldrPin1, INPUT);
  // put your setup code here, to run once:

}

void loop() {
  int ldrStatus1 = analogRead(ldrPin1);
if (ldrStatus1 <= 200) {
digitalWrite(ledPin1, LOW);
Serial.print("Its BRIGHT, Turn off the LED : ");
Serial.println(ldrStatus1);
} 
else {

digitalWrite(ledPin1, HIGH);
Serial.print("Its DARK, Turn on the LED : ");
Serial.println(ldrStatus1);
}
delay(2000);
// put your main code here, to run repeatedly:

}
