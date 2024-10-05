# esp32_blespoof_gui
Easy to use ESP32 BLE Spoofer with Tkinter GUI

# BLE Spoofing Script with ESP32 and Python GUI

This project is based on [ESP32-Sour-Apple by RapierXbox](https://github.com/RapierXbox/ESP32-Sour-Apple/tree/main) and allows you to perform **BLE spoofing** to simulate various Apple and non-Apple devices (such as AirPods, Apple TV, Samsung Galaxy Buds, and more) using an **ESP32** microcontroller. A simple **Python GUI** is provided to control which device you want to spoof and to start or stop the spoofing process.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Devices Supported](#devices-supported)
- [Credits](#credits)

## Features
- Spoof various BLE devices such as AirPods, Apple TV, Galaxy Buds, and more.
- Simple Python GUI to select devices and control spoofing.
- Built using the **ESP32-Sour-Apple** project by **RapierXbox**.
- Configurable to add more devices by extending the code.

## Requirements
- **ESP32** microcontroller (configured with BLE support).
- Python 3.x with the following libraries:
  - `tkinter` (for the GUI)
  - `pyserial` (for communication with ESP32)

## Installation

### 1. Install RapierXbox's [SourApple](https://github.com/RapierXbox/ESP32-Sour-Apple/tree/main)
2. Inside esp32_ble_spoof_gui.py, change the port variable to your desired serial port
3. Run the script using `python3 esp32_ble_spoof_gui.py`

## 🚫 Warning / Disclaimer
Only use this on devices you own or when you have permisson to use it.
This project is made for educational purposes ONLY and is NOT made to break laws and/or
for personal gain. Everything is provided as-is and has no warranty so if your break any of your devices.
