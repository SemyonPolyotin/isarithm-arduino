# Isarithm Arduino
ESP32 based arduino Isarithm project

## Clion
### Project
```bash
    $ git clone https://github.com/semyonpolyotin/isarithm-arduino.git
    $ cd isarithm-arduino
    $ # (Optional)
    $ platformio init --ide clion --board esp32dev
```
### Additional libraries
```bash
    $ platformio lib install "ESP32Servo"
    $ platformio lib install "I2Cdevlib-MPU6050"
```

## Debug
To debug use this commands.
```bash
    $ pio device monitor -p /dev/ttyS3
    $ pio device monitor -p /dev/ttyS3 | grep Accelerometer
```

## Appliance
### Devices
- ESP32 development module
- SG90 servo motor
- MPU6050 accelerometer-gyroscope
### Wiring
| Device 1 | Port | Device 2 | Port |
|---|---|---|---|
| MPU6050 | VCC | ESP32 | 3V3 |
| MPU6050 | GND | ESP32 | Gnd |
| MPU6050 | SCL | ESP32 | D22 |
| MPU6050 | SDA | ESP32 | D21 |
| SG90 | SIG | ESP32 | D13 |
| SG90 | VCC | ESP32 | VIN |
| SG90 | GND | ESP32 | GND |

## Setup
For detailed information reefer to [PlatformIO installation documentation](http://docs.platformio.org/en/latest/installation.html).
### Linux
```bash
    $ sudo apt install python
    $ pip install platformio
```
### OS X
```bash
    $ brew install platformio
```
