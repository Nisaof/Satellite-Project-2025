#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <TimerOne.h>  // TimerOne library

#define MY_BMP280_ADDR 0x76

Adafruit_BMP280 bmp(&Wire);

// CRC-32 calculation function
uint32_t calculateCRC32(const byte *data, size_t length) {
  uint32_t crc = 0xFFFFFFFF;
  for (size_t i = 0; i < length; i++) {
    crc ^= data[i];
    for (int j = 0; j < 8; j++) {
      if (crc & 1)
        crc = (crc >> 1) ^ 0xEDB88320;
      else
        crc >>= 1;
    }
  }
  return ~crc;
}

// Only flag will be set in timer interrupt
volatile bool flag = false;

void sendPressurePacket() {
  flag = true;  // Only set flag in ISR
}

void setup() {
  Serial.begin(9600);
  delay(1000);

  if (!bmp.begin(MY_BMP280_ADDR)) {
    Serial.println("BMP280 not found!");
    while (1); // Stay here if sensor not found
  }

  // Sensor sampling settings
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);

  // Timer1 will create an interrupt every 100ms
  Timer1.initialize(100000);
  Timer1.attachInterrupt(sendPressurePacket);

  Serial.println("Ready.");
}

void loop() {
  if (flag) {
    noInterrupts();
    flag = false;  // Reset flag
    interrupts();

    // Read pressure from sensor (I2C should work at this line, outside ISR)
    float pressure = bmp.readPressure();

    // Create packet
    byte packet[10];
    packet[0] = 0xAA;
    memcpy(&packet[1], &pressure, 4);

    uint32_t crc = calculateCRC32(&packet[1], 4);
    memcpy(&packet[5], &crc, 4);

    packet[9] = 0x55;

    // Send packet via serial port
    for (int i = 0; i < 10; i++) {
      Serial.write(packet[i]);
    }

    // Print pressure and CRC in readable format
    Serial.print("Pressure (Pa): ");
    Serial.println(pressure, 2);
    Serial.print("CRC32: 0x");
    Serial.println(crc, HEX);
  }
}
