# Smart Parking Lot

An arduino project on improving parking lot efficiency.

**Features**
1. Password input via 4x4 matrix keypad
2. RFID card authentication
3. Parking space counting using ultrasonic and IR obstacle detection sensor
4. LCD display screen for available parking space
5. RGB LED for indicating general status

## Component

1. Arduino MEGA2560
2. MG995 servo motor
3. Ultrasonic sensor HC-SR04
4. IR obstacle tracker KY-032
5. LCD display LCD1602 module
6. RGB LED + 3x 220 Ohm resistor
7. 4x4 Matrix keypad module
8. RFID RC522 module

## Installation

Required libraries for arduino code
1. Keypad.h by Mark Stanley, Alexander Brevig (search in library manager)
2. [LiquidCrystal_I2C.h](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library) by fdebrabander
3. [MFRC5222.h](https://github.com/miguelbalboa/rfid) by miguelbalboa

## Usage

Compile and upload [the code](https://github.com/Mlapn0t/smart_parkinglot/blob/main/smart_parkinglot.ino) into arduino board and connect pins according to the [Schematic Diagram](https://drive.google.com/file/d/14_AJm1lmFuwVgnuVntWDBJ6vR0WxtUfo/view?usp=sharing)

## Credit

Tutorial followed

[4x4 Matrix Keypad](https://www.allnewstep.com/article/235/35-arduino-%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B9%83%E0%B8%8A%E0%B9%89%E0%B8%87%E0%B8%B2%E0%B8%99-arduino-matrix-keypad-44-%E0%B8%A3%E0%B8%B1%E0%B8%9A%E0%B8%84%E0%B9%88%E0%B8%B2%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B8%81%E0%B8%94%E0%B8%9B%E0%B8%B8%E0%B9%88%E0%B8%A1)

[MG995 servo](https://www.cybertice.com/article/266/%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B9%83%E0%B8%8A%E0%B9%89%E0%B8%87%E0%B8%B2%E0%B8%99-arduino-mg995-servo-%E0%B8%AB%E0%B8%A1%E0%B8%B8%E0%B8%99%E0%B9%81%E0%B8%9A%E0%B8%9A-0-180-%E0%B8%AD%E0%B8%87%E0%B8%A8%E0%B8%B2?gad_source=1&gclid=Cj0KCQjwiYOxBhC5ARIsAIvdH520SqaUwfmmewbOCsU7PtDwDe6YLN_fHDfORcx5H_3NqOEWDQC06fcaAn42EALw_wcB)

[RFID module](https://github.com/miguelbalboa/rfid)

[LCD display](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)

[Ultrasonic sensor](https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/)

[IR obstacle tracking sensor](https://robotsiam.blogspot.com/2016/10/ir-infrared-obstacle-avoidance-sensor.html)

[RGB LED](https://www.allnewstep.com/article/224/24-arduino-%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B9%83%E0%B8%8A%E0%B9%89%E0%B8%87%E0%B8%B2%E0%B8%99-arduino-%E0%B8%9C%E0%B8%AA%E0%B8%A1%E0%B8%AA%E0%B8%B5%E0%B8%AB%E0%B8%A5%E0%B8%AD%E0%B8%94%E0%B9%84%E0%B8%9F-rgb-led)
