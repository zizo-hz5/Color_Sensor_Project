#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define LCD parameters
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define RGB led & Button pins
#define redpin 9
#define greenpin 10
#define bluepin 11
#define button 8

// Define color sensor pins
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

// Calibration Values
int redMin = 19, redMax = 180;
int greenMin = 19, greenMax = 170;
int blueMin = 16, blueMax = 139;

// Variables for Color Pulse Width Measurements
int redPW = 0, greenPW = 0, bluePW = 0;

// Variables for final Color values
int redValue, greenValue, blueValue;

// Gamma table for correction
byte gammatable[256];

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("Color Picker");
  lcd.setCursor(0, 1);
  lcd.print("Ready");
  delay(750);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  digitalWrite(redpin, HIGH);
  digitalWrite(greenpin, HIGH);
  digitalWrite(bluepin, HIGH);

  pinMode(sensorOut, INPUT);
  pinMode(button, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  for (int i = 0; i < 256; i++) {
    float x = i / 255.0;
    x = pow(x, 2.2);
    gammatable[i] = x * 255;
  }
}

void loop() {
  if (digitalRead(button) == LOW) {
    delay(200);
    redPW = getRedPW();
    greenPW = getGreenPW();
    bluePW = getBluePW();

    redValue = map(redPW, redMin, redMax, 255, 0);
    greenValue = map(greenPW, greenMin, greenMax, 255, 0);
    blueValue = map(bluePW, blueMin, blueMax, 255, 0);

    redValue = gammatable[redValue];
    greenValue = gammatable[greenValue];
    blueValue = gammatable[blueValue];

    int maxVal = max(redValue, max(greenValue, blueValue));
    if (maxVal > 0) {
      redValue = map(redValue, 0, maxVal, 0, 255);
      greenValue = map(greenValue, 0, maxVal, 0, 255);
      blueValue = map(blueValue, 0, maxVal, 0, 255);
    }

    redValue = constrain(redValue, 0, 255);
    greenValue = constrain(greenValue, 0, 255);
    blueValue = constrain(blueValue, 0, 255);

    analogWrite(redpin, 255 - redValue);
    analogWrite(greenpin, 255 - greenValue);
    analogWrite(bluepin, 255 - blueValue);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("R:");
    lcd.print(redValue);
    lcd.print(" G:");
    lcd.print(greenValue);
    lcd.setCursor(0, 1);
    lcd.print("B:");
    lcd.print(blueValue);

    while (digitalRead(button) == LOW);
    delay(200);
  }
}

int getRedPW() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  return pulseIn(sensorOut, LOW);
}

int getGreenPW() {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  return pulseIn(sensorOut, LOW);
}

int getBluePW() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  return pulseIn(sensorOut, LOW);
}
