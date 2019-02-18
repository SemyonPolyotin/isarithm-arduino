# Isarithm Arduino
ESP32 based arduino mockup project

## Clion
### Project
```bash
    $ git clone https://github.com/matthewpoletin/isarithm-arduino.git 
    $ # (Optional)
    $ platformio init --ide clion --board esp32dev
```
### Additional libraries
```bash
    $ platformio lib install "ESP32Servo"
```

## Debug
To debug use this commands.
```bash
    $ pio device monitor -p /dev/ttyS3 
```

## Appliance
### Devices
- ESP32 development module
- SG90 servo motor
- MPU6050 accelerometer-gyroscope
### Wiring
| Device 1 | Port | Device 2 | Port |
|---|---|---|---|
| MPU6050 | SCL | ESP32 | D22 |
| MPU6050 | SDA | ESP32 | D21 |
| SG90 | Sig | ESP32 | D21 |

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
