 # Arduino Color Sensor Project 🎨

This project uses the **TCS3200 Color Sensor** with an **LCD display** and an **RGB LED** to detect and display colors in real-time.

---

## 📘 Project Overview
The project consists of two main codes:
1. **Calibration Code:**  
   Used to measure the raw RGB values for different colors and determine the min/max calibration range.

2. **Color Picker Code:**  
   Uses the calibrated values to detect colors, display their RGB values on the LCD, and light up the RGB LED with the same color.

---

## 🧩 Components Used
- Arduino Uno  
- TCS3200 Color Sensor  
- 16x2 I2C LCD  
- RGB LED  
- Push Button  
- Jumper wires  

---

## ⚙️ Pin Configuration
| Component | Arduino Pins |
|------------|--------------|
| TCS3200 | S0=2, S1=3, S2=4, S3=5, OUT=6 |
| RGB LED | R=9, G=10, B=11 |
| Button | 8 |
| LCD | I2C (SDA=A4, SCL=A5) |

---

## 🖼️ Circuit Overview
![Circuit Diagram](images/circuit.png)

---

## 🧠 How It Works
1. The calibration code reads pulse width for red, green, and blue filters.  
2. Based on calibration results, the color picker maps measured pulse widths to RGB values (0–255).  
3. The color is displayed on the LCD and shown on the RGB LED.

---

## 🚀 How to Run
1. Upload `Calibration.ino` to your Arduino.
2. Note down the min and max values for red, green, and blue.
3. Update those values in `Color_Picker.ino`.
4. Upload `Color_Picker.ino` and press the button to detect colors.

---

## 📷 Example Output

R: 120 G: 90
B: 45

---

## 👨‍💻 Author
Developed by **Abdelaziz Hassan**

**Tags:** Arduino, TCS3200, Color Sensor, RGB LED, LCD, Embedded Systems


