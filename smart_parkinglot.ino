#include <Keypad.h> // for Matrix keypad module
#include <Servo.h> // for MG995 servo
#include <LiquidCrystal_I2C.h> // for LCD display
#include <Wire.h> // for LCD display
#include <SPI.h> // for RFID reader module
#include <MFRC522.h> // for RFID reader module
#define RST_PIN 5 // Configurable, see typical pin layout above
#define SS_PIN 53 // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

String pwdcreate = "";  // initiate input password
const int builtinLED = 13; // for debugging
String password = "3210"; // set password to 3210
int servoState = 0; // initiate servo position to 0 degree
Servo myservo;  // Create Servo instance
LiquidCrystal_I2C lcd(0x27, 16, 2);

// mapping 16 keys in keypad into hexadecimals 
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {34, 33, 32, 31}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {38, 37, 36, 35}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

const int trigPin = 6;  // Ultrasonic Trig pin
const int echoPin = 7; // Ultarsonic Echo pin
const int irObsPin=  4; // IR obstacle Out pin
const int R = 44; // Red channel LED
const int G = 45; // Green channel LED
const int B = 46; // Blue channel LED

// defines variables for ultrasonic sensor
long duration;
int distance;

void setup() {
  lcd.begin(); // Init LCD display
  Wire.begin(); // Init I2C communication for LCD display

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode (builtinLED, OUTPUT); // built-in LED pin set to output
  pinMode (irObsPin, INPUT); // module signal output connected to Arduino pin 8

  pinMode(R, OUTPUT); // Sets Red channel of RGB LED as an Output
  pinMode(G, OUTPUT); // Sets Green channel of RGB LED as an Output
  pinMode(B, OUTPUT); // Sets Blue channel of RGB LED as an Output

  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:")); //shows in serial that it is ready to read

  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("PASS: ");
  // ---------- keypad + servo stuffs ----------
  char customKey = customKeypad.getKey();
  if (customKey){
    //Serial.println(customKey);
    pwdcreate = pwdcreate + customKey;
    Serial.println(pwdcreate);
    lcd.setCursor(6,0);
    lcd.print(pwdcreate);
    if (pwdcreate.length() == password.length()) {  // input password length is equal to set password
      Serial.print("Entered password: ");
      Serial.print(pwdcreate);
      if (password == pwdcreate) { // input password is correct
        Serial.print("\nStatus: Correct\n");
        // digitalWrite(builtinLED, HIGH);
        analogWrite(R, 0);
        analogWrite(G, 255);
        analogWrite(B, 0);
        delay(1000);
        analogWrite(R, 0);
        analogWrite(G, 0);
        analogWrite(B, 255);
        delay(100);

        if (servoState == 0) {  // open gate
          myservo.attach(3);
          myservo.write(90);
          delay(1000);
          myservo.detach();
          servoState = 1;
        }
        else { // close gate
          myservo.attach(3);
          myservo.write(20);
          delay(1000);
          myservo.detach();
          servoState = 0;
        }

        pwdcreate = ""; // clear input password
        lcd.setCursor(6,0);
        lcd.print("    ");
      }
      else { // input password is incorrect
        Serial.print("\nStatus: Wrong\n");
        // digitalWrite(builtinLED, LOW);
        analogWrite(R, 255);
        analogWrite(G, 0);
        analogWrite(B, 0);
        delay(1000);
        analogWrite(R, 0);
        analogWrite(G, 0);
        analogWrite(B, 255);
        delay(100);

        pwdcreate = ""; // clear input password
        lcd.setCursor(6,0);
        lcd.print("    ");
      }
    }
  }
  else { // input password length is not equal to set password
      analogWrite(R, 0);
      analogWrite(G, 0);
      analogWrite(B, 255);
      delay(100);
  }

  // ---------- Ultrasonic stuffs ----------
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  // ---------- Counting Empty lots  ----------
  if (digitalRead(irObsPin) == LOW && distance <= 5) { // 2 cars detected
  lcd.setCursor(0,1);
  lcd.print("EMPTY LOT: 0");
  }
  else if (digitalRead(irObsPin) == LOW || distance <= 5) { // 1 car detected
    lcd.setCursor(0,1);
    lcd.print("EMPTY LOT: 1");
  }
  else { // no car detected
    lcd.setCursor(0,1);
    lcd.print("EMPTY LOT: 2");
  }

  // ---------- RFID stuffs ----------
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;
  }
  Serial.println(F("**Card Detected:**"));
  if (servoState == 0) { // open gate
          myservo.attach(3);
          myservo.write(90);
          delay(1000);
          myservo.detach();
          servoState = 1;
        }
  else { // close gate
          myservo.attach(3);
          myservo.write(20);
          delay(1000);
          myservo.detach();
          servoState = 0;
  }

  // ---------- debug ----------
  // -- Ultrasonic sensor
  // Prints the distance on the Serial Monitor
  // Serial.print("Distance: ");
  // Serial.println(distance);

  // -- IR obstacle tracking
  // if (digitalRead(irObsPin) == LOW) { // if module detects an obstacle,
  // Serial.println("Obstacle Detected"); // show message on serial monitor and
  // digitalWrite (builtinLED, HIGH); // switch-On built-in LED
  // }
  // else {
  // Serial.println("No Obstacle");
  // digitalWrite (builtinLED, LOW);
  // }
}
