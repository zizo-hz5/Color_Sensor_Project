#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define color sensor pins
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// I2C LCD settings
const int LCD_ADDRESS = 0x27;
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Set Pulse Width scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Color Sensor");
  delay(1000);
}

void loop() {
  // Read Red Pulse Width
  redPW = getRedPW();
  delay(200);

  // Read Green Pulse Width
  greenPW = getGreenPW();
  delay(200);

  // Read Blue Pulse Width
  bluePW = getBluePW();
  delay(200);

  // Print output to the I2C LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R:");
  lcd.print(redPW);
  lcd.print(" G:");
  lcd.print(greenPW);
  lcd.setCursor(0, 1);
  lcd.print("B:");
  lcd.print(bluePW);
  delay(1000);
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
