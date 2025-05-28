# 
# WiFi-Controlled ESP8266 RC Car with Distance, Temperature & Humidity Monitoring

This project allows you to control an RC car wirelessly over WiFi using an ESP8266 NodeMCU board. It also measures and displays the distance using an ultrasonic sensor and monitors temperature and humidity using a DHT11 sensor on a single web interface.

## 🔧 Features

- WiFi-based control (no need for Bluetooth or RF remotes)
- Real-time distance measurement via ultrasonic sensor
- Real-time temperature and humidity display via DHT11
- Built-in LED and horn control
- OTA update support

---

## 🧰 Hardware Requirements

| Component                 | Quantity |
|--------------------------|----------|
| ESP8266 NodeMCU (ESP-12E)| 1        |
| L298N Motor Driver       | 1        |
| DC Motors                | 4        |
| Ultrasonic Sensor (HC-SR04) | 1     |
| DHT11 Sensor             | 1        |
| Buzzer                   | 1        |
| LED                      | 1        |
| Jumper Wires             | -        |
| Power Supply (6V–12V)    | 1        |
| Chassis + Wheels         | 1 set    |

---

## 🔌 Pin Connections

| ESP8266 Pin | Component             | Description          |
|-------------|-----------------------|----------------------|
| D0          | Buzzer                | Beep horn            |
| D1          | LED                   | Headlight            |
| D2          | WiFi status LED       | WiFi indicator       |
| D3          | HC-SR04 Trig          | Ultrasonic sensor    |
| D4          | HC-SR04 Echo          | Ultrasonic sensor    |
| D5          | L298N IN1             | Rear Right motor     |
| D6          | L298N IN2             | Front Right motor    |
| D7          | L298N IN3             | Rear Left motor      |
| D8          | L298N IN4             | Front Left motor     |
| D9 / GPIO9  | DHT11 Data (via resistor) | Temperature/Humidity |
| VIN / 5V    | VCC for sensors       | Power supply         |
| GND         | Common Ground         |                      |

> Note: Connect DHT11 to a free digital GPIO (e.g., GPIO9 if D1-D8 are used).

---

## 💻 Software Installation

1. Install the latest version of the Arduino IDE from https://www.arduino.cc/en/software.
2. Go to File → Preferences → Add this board URL in "Additional Board Manager URLs":
   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
3. Go to Tools → Board → Board Manager → Search for "esp8266" and install.
4. Install the following libraries:
   - ESP8266WiFi
   - ESP8266WebServer
   - ArduinoOTA
   - DHT sensor library by Adafruit
   - Adafruit Unified Sensor
   - (Optional) NewPing (if using advanced ultrasonic features)

---

## 📡 Uploading the Code

1. Open the Arduino IDE and select:
   - Board: “NodeMCU 1.0 (ESP-12E Module)”
   - Port: COMx (your device)
2. Upload the provided code to your ESP8266.
3. Open Serial Monitor (baud: 115200) to see the IP address.
4. Connect your smartphone or laptop to the same network.
5. Open a browser and enter the IP address to access the control panel.

---

## 🌐 Web Interface

- Displays:
  - Distance (in cm)
  - Temperature (in °C)
  - Humidity (in %)
- Controls:
  - Forward, Backward, Left, Right
  - Diagonal movement
  - Light ON/OFF
  - Horn Beep
- Live data is updated dynamically.

---

## 🚗 Commands Overview

| Button Pressed | Action              |
|----------------|---------------------|
| F              | Forward              |
| B              | Backward             |
| L              | Turn Left            |
| R              | Turn Right           |
| G              | Forward Left         |
| H              | Backward Left        |
| I              | Forward Right        |
| J              | Backward Right       |
| S              | Stop                 |
| V              | Horn (Beep)          |
| W / w          | Light ON / OFF       |

---

## ☁️ OTA Support

Once the ESP8266 is connected to WiFi, you can upload code over-the-air via Arduino IDE:
- Go to Tools → Port → Select network port (ESP8266)
- Upload normally

---


## 🏁 Final Output

- Wireless RC car controllable via browser
- Real-time sensor data display
- Easy to modify and extend
