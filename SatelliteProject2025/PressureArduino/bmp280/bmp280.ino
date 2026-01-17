#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600); //BAUD Rate
  while (!Serial);

  if (!bmp.begin(0x77)) { // Address of sensor(0x77)
    Serial.println("BMP280 does not exist!");
    while (1);
  }

  Serial.println("BMP280 started.");
}

void loop() {
  Serial.print("Pressure: ");
  Serial.print(bmp.readPressure()); // Pascal 
  Serial.println(" Pa");

  delay(5000);
}
