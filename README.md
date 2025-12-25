# ESP Watch

> "ESP Watch" — Smartwatch on ESP8266 with time synchronization via NTP and access point mode for WiFi setup.

---

## Content

- [Description](#description)
- [Requirements](#requirements)
- [Installation](#installation)
- [Connecting_pins](#Connecting_pins)


---

## Description

Smartwatch on ESP with comfortable setting up throught web interface in 3-rd version. First setup with AP mode and then with STA mode. 


---

## Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- ESP8266 (NodeMCU, Wemos D1 Mini и др.)
- Libs are included in rar file 
- LCD Display 1602 with I2C

---

## Installation

- Install last release
- Open esp_watch.ino file in arduino IDE 
- Add libs to IDE 
- Flash

## Connecting_pins

- Display pins VCC - VIN or VBUS, GND - GND, SCL - D1 (GPIO5 - ESP8266), SDA -  D2 (GPIO4 - ESP8266).
- Power to ESP 8266 trught VIN (+) and GND (-).
- Strongly recomend to use PSU from phone or other 5 Volts and 2 Ampers.
