# Smart Accident Detection and Emergency Alert System

An Arduino-based system that detects a vehicle accident and automatically
sends an SMS with the vehicle's GPS location to family members.

## How it works
1. The LCD continuously displays the vehicle's latitude and longitude from the GPS module.
2. When the vibration sensor detects an impact, the system treats it as a possible accident.
3. A "Time Left" alert timer starts on the LCD (about 15 seconds).
4. If it was a false detection, the driver presses the push button to stop the timer and cancel the SMS.
5. If the button is not pressed before the timer ends, the buzzer sounds and the GSM module
   sends an emergency SMS with the vehicle number and a Google Maps location link
   to the saved family numbers.

## Hardware
See [hardware/components_list.md](hardware/components_list.md) for the full list.

## Pin connections
| Module | Module Pin | Arduino Pin |
|---|---|---|
| GPS | TX | D2 (SoftwareSerial RX) |
| GPS | RX | D3 (SoftwareSerial TX) |
| GSM | TX | D0 (RX) |
| GSM | RX | D1 (TX) |
| Vibration sensor | OUT | A1 |
| Push button | One side | A0 (other side to GND) |
| Buzzer | + | D11 |
| LCD (I2C, address 0x27) | SDA / SCL | A4 / A5 |

All modules must share a common GND. Power the GSM module from a separate supply
that can deliver enough current (SIM800L needs about 2A peaks).

## Libraries required
- TinyGPSPlus
- LiquidCrystal_I2C
- SoftwareSerial (built in)

## Setup
1. Install the libraries above from the Arduino IDE Library Manager.
2. Open `src/accident_detection/accident_detection.ino` in the Arduino IDE.
3. Replace the placeholder phone numbers in the `Alert_sms1()` and `Alert_sms2()` calls
   with your family members' numbers (with country code, e.g. +91XXXXXXXXXX).
4. Replace the vehicle number in the SMS text with your own.
5. Disconnect the GSM module's TX/RX wires from D0/D1 while uploading, then reconnect them.
6. Select your board and port, then upload.

## Sample SMS
```
Accident Occurred!!!
TN 99 EC 3815
http://maps.google.com/maps?q=loc:LAT,LNG
ASSISTANCE REQUIRED
```

## Notes
- The GPS module needs a clear view of the sky and may take a few minutes for its first fix.
- The GSM module needs an active SIM card with SMS balance and network coverage.

## Future improvements
- Accelerometer (MPU6050) for more accurate crash detection
- Non-blocking timer using millis() instead of delay()
- Support for more emergency contacts
- Ambulance and police alert integration

## License
This project is for educational purposes.

Owner
Devanand P C
Electronics and Communication Engineering Student
