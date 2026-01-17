#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!bmp.begin(0x77)) { // I2C address is correct
    Serial.println("BMP280 not found!");
    while (1);
  }

  Serial.println("BMP280 initialized.");
}

void loop() {
  float temperature = bmp.readTemperature();  // In Celsius
  float pressure = bmp.readPressure();       // In Pascal

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");

  delay(10000);
}
