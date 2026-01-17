# Satellite Project - Arduino & Sensor Code Collection

## Description

Development code written during competition preparation for a satellite project (Summer 2025). Intermediate/test codes for sensor integration, communication protocols, and error detection systems developed throughout the prototyping phase.

## Project Structure

```
mix/
├── ErrorCodeDetection/       # Error Code Detection System 
├── I2CAddressTest/           # I2C Address Scanner
├── PressureArduino/          # BMP280 Pressure Sensor Basic Test
├── TemperatureAndPressure/   # BMP280 Temperature & Pressure Test
├── xBee_BMP280_Data/        # BMP280 with xBee Data Transmission
└── xBee_Test/               # xBee Communication Test
```

## Components

### 1. Error Code Detection System (`ErrorCodeDetection`)
**File:** `ErrorCodeDetection/ErrorCodeDetection.cpp`  
**Description:** Monitors barometric altitude data and calculates average speed to detect errors based on predefined speed ranges.

**Features:**
- Barometric altitude reading
- Average speed calculation
- Error code generation for different speed ranges:
  - Error Code 1: Speed control (12-14 m/s)
  - Error Code 2: Payload speed control (6-8 m/s)
  - Error Code 3: Barometer connection status

**Usage:**
```bash
g++ ErrorCodeDetection.cpp -o ErrorCodeDetection
./ErrorCodeDetection
```

### 2. I2C Address Scanner (`I2CAddressTest`)
**File:** `I2CAddressTest/i2cScanner/i2cScanner.ino`
**Description:** Scans the I2C bus to detect connected devices and their addresses.

**Features:**
- Scans I2C addresses from 0x01 to 0x7E
- Displays found device addresses in hexadecimal format
- Error detection for unknown I2C errors

**Hardware Requirements:**
- Arduino board with I2C support
- I2C devices to scan

**Usage:**
1. Upload to Arduino
2. Open Serial Monitor at 9600 baud
3. Wait for scan results

### 3. BMP280 Pressure Sensor (`PressureArduino`)
**Description:** Basic pressure reading from BMP280 sensor via I2C.

**Features:**
- Reads pressure in Pascal
- I2C communication at address 0x77
- Serial output at 9600 baud

**Libraries Required:**
- `Wire.h`
- `Adafruit_Sensor.h`
- `Adafruit_BMP280.h`

**Hardware Requirements:**
- Arduino board
- BMP280 sensor
- I2C connections (SDA, SCL)

### 4. BMP280 Temperature & Pressure Test (`TemperatureAndPressure`)
**File:** `TemperatureAndPressure/bmp280_test.ino`  
**Description:** Extended BMP280 sensor test that reads both temperature and pressure.

**Features:**
- Temperature reading in Celsius
- Pressure reading in Pascal
- I2C communication at address 0x77
- 10-second update interval

**Libraries Required:**
- `Wire.h`
- `Adafruit_Sensor.h`
- `Adafruit_BMP280.h`

**Hardware Requirements:**
- Arduino board
- BMP280 sensor
- I2C connections (SDA, SCL)

### 5. BMP280 with xBee Data Transmission (`xBee_BMP280_Data`)
**File:** `xBee_BMP280_Data/bmp280_xbee_transmission/bmp280_xbee_transmission.ino`  
**Description:** Advanced implementation that reads BMP280 pressure data and transmits it via xBee module with CRC-32 error checking.

**Features:**
- Timer-based interrupt system (100ms intervals)
- Pressure data packetization
- CRC-32 checksum calculation for data integrity
- Serial transmission for xBee module
- Packet format: `[0xAA][4-byte pressure][4-byte CRC32][0x55]`

**Libraries Required:**
- `Wire.h`
- `SPI.h`
- `Adafruit_BMP280.h`
- `TimerOne.h`

**Hardware Requirements:**
- Arduino board
- BMP280 sensor (I2C address: 0x76)
- xBee module connected to Serial port

**Packet Structure:**
```
Byte 0:    0xAA (Start marker)
Bytes 1-4: Pressure value (float, 4 bytes)
Bytes 5-8: CRC32 checksum (uint32_t, 4 bytes)
Byte 9:    0x55 (End marker)
```

### 6. xBee Communication Test (`xBee_Test`)
**File:** `xBee_Test/xBeeTest/xBeeTest.ino`  
**Description:** Basic xBee module communication test using AT commands.

**Features:**
- SoftwareSerial communication with xBee
- Command mode entry (+++)
- AT command testing
- Serial monitor feedback

**Hardware Requirements:**
- Arduino board
- xBee module
- SoftwareSerial pins: RX=2, TX=3

**Usage:**
1. Connect xBee to pins 2 (RX) and 3 (TX)
2. Upload code to Arduino
3. Open Serial Monitor at 9600 baud
4. Observe AT command responses

## Installation & Setup

### Prerequisites
- Arduino IDE (for .ino files)
- C++ compiler (for .cpp files)
- Required Arduino libraries:
  - Adafruit BMP280 Library
  - Adafruit Unified Sensor
  - TimerOne Library

### Library Installation
1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries**
3. Search and install:
   - `Adafruit BMP280 Library`
   - `Adafruit Unified Sensor`
   - `TimerOne`

### Hardware Connections

#### BMP280 Sensor
```
BMP280    Arduino
VCC   →   3.3V or 5V
GND   →   GND
SDA   →   SDA (A4 on Uno)
SCL   →   SCL (A5 on Uno)
```

#### xBee Module
```
xBee     Arduino
VCC  →   3.3V
GND  →   GND
DIN  →   Pin 3 (TX)
DOUT →   Pin 2 (RX)
```

## Notes

- All code has been tested and is functional
- I2C addresses may vary depending on sensor configuration (0x76 or 0x77 for BMP280)
- Ensure proper voltage levels when connecting sensors (BMP280 typically uses 3.3V)

