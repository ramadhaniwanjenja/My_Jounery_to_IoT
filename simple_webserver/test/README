# ESP8266 WiFi Network Scanner

![ESP8266 WiFi Network Scanner](https://media.geeksforgeeks.org/wp-content/uploads/20190927155217/webserver.png)

This project implements an ESP8266-based WiFi network scanner using the Arduino framework. It allows scanning for available WiFi networks, displaying their SSIDs, signal strengths, and encryption types via the serial monitor. LEDs are used to indicate the scanning process and current network status.

## Table of Contents

- [Hardware Required](#hardware-required)
- [Circuit Diagram](#circuit-diagram)
- [Software Required](#software-required)
- [Setup and Installation](#setup-and-installation)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Hardware Required

- ESP8266 Board (e.g., NodeMCU, Wemos D1 Mini)
- 3 LEDs (Red, Green, Yellow)
- 3 Resistors (220 ohm)
- Breadboard and Jumper Wires

## Circuit Diagram

| Pin  | Component    |
|------|--------------|
| D2   | Green LED    |
| D3   | Yellow LED   |
| D4   | Red LED      |

Connect the anodes of the LEDs to the respective pins (D2, D3, D4) through a 220 ohm resistor. Connect the cathodes of the LEDs to the ground.

## Software Required

- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO IDE](https://platformio.org/platformio-ide)
- [ESP8266 Board Package](https://platformio.org/platforms/espressif8266)

## Setup and Installation

1. **Install PlatformIO in VSCode:**
   - Open VSCode.
   - Go to the Extensions view by clicking on the Extensions icon in the Activity Bar.
   - Search for `PlatformIO IDE` and install it.

2. **Create a New PlatformIO Project:**
   - Open the PlatformIO Home screen by clicking on the PlatformIO icon in the Activity Bar.
   - Click on "New Project."
   - Enter a name for your project.
   - Select `Espressif 8266` as the board.
   - Choose `Arduino` as the framework.
   - Click "Finish."

3. **Upload the Code:**
   - Replace the default `src/main.cpp` content with the provided code in this repository.
   - Save your code.
   - Connect your ESP8266 board to your computer via USB.
   - In the PlatformIO toolbar, click the "Upload" button (right arrow icon) to compile and upload the code to your ESP8266 board.

4. **Monitor Serial Output:**
   - Click the "Serial Monitor" button (plug icon) in the PlatformIO toolbar to open the serial monitor.
   - Set the baud rate to `115200` to match the `Serial.begin(115200);` statement in your code.
   - You should see the ESP8266 scanning for available WiFi networks and displaying the results.

## Usage

Once the code is uploaded and the serial monitor is open, the ESP8266 will continuously scan for available WiFi networks. The LEDs will indicate the scanning process and network status:
- **Green LED:** Indicates scanning process.
- **Red LED:** Indicates no networks found.
- **Yellow LED:** Indicates networks found.

## Troubleshooting

- **Driver Issues:** Ensure you have the correct drivers installed for your ESP8266 board.
- **Board Selection:** Verify that the board selected in `platformio.ini` matches your actual hardware.
- **Serial Communication:** Double-check the baud rate and COM port settings in the serial monitor.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Inspired by examples from the Arduino and ESP8266 communities.
