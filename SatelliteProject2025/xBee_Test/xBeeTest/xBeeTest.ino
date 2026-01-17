#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3); 

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);

  delay(2000); 

  Serial.println("Entering command mode...");
  xbee.print("+++");       // Enter command mode
  delay(1000);             // Wait 1 second
  // XBee returns "OK" if successful

  Serial.println("Sending AT command...");
  xbee.print("AT\r");      // Send AT command
}

void loop() {
  if (xbee.available()) {
    char c = xbee.read();
    Serial.print(c);
  }
}

