#include <ESP8266WiFi.h> // Include the ESP8266 WiFi library to enable Wi-Fi functionality

// Define pin numbers for the LEDs
int red = D4;
int green = D2;
int yellow = D3;

void setup() {
  // Set the pin modes for the LEDs to OUTPUT
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  
  Serial.begin(115200); // Initialize serial communication at a baud rate of 115200 for debugging
  
  // Set WiFi mode to station mode (client mode)
  WiFi.mode(WIFI_STA);
  
  // Disconnect from any previously connected Wi-Fi network
  WiFi.disconnect();
  
  // Add a delay to give the Wi-Fi module some time to reset
  delay(1000);
}

void loop() {
  // Print a message to the serial monitor indicating that a scan for available networks is starting
  Serial.println("Scanning for available networks...");
  
  // Turn the red LED on to indicate that scanning is in progress
  digitalWrite(red, HIGH);
  
  // Turn the green LED off while scanning
  digitalWrite(green, LOW);

  // Scan for available Wi-Fi networks and store the number of networks found in 'n'
  int n = WiFi.scanNetworks();
  
  // Check if any networks were found
  if (n > 0) {
    // If networks are found, turn the green LED on and the red LED off
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    
    // Print the number of networks found to the serial monitor
    Serial.print(n); Serial.println(" network(s) found");
    
    // Loop through each found network and print its details
    for (int i = 0; i < n; ++i) {
      // Print the network number
      Serial.print("Network "); Serial.print(i + 1); Serial.print(": ");
      
      // Print the SSID (name) of the network
      Serial.print(WiFi.SSID(i));
      
      // Print the signal strength (RSSI) of the network in dBm
      Serial.print(" ("); Serial.print(WiFi.RSSI(i)); Serial.print(" dBm)");
      
      // Print whether the network is open or secured
      Serial.print((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " open" : " secured");
      
      // Print a newline character to move to the next line in the serial monitor
      Serial.println();
      
      // Add a small delay to avoid overwhelming the serial monitor
      delay(50);
    }
  } else {
    // If no networks are found, print a message to the serial monitor
    Serial.println("No available networks found");
    
    // Turn the red LED off and the green LED on to indicate that no networks were found
    digitalWrite(red, 1);
    digitalWrite(green, 0);
  }
  
  // Print a separator line to the serial monitor for better readability
  Serial.println("---------------------------------------------------------------");
  
  // Add a delay of 5000 milliseconds (5 seconds) before running the loop again
  delay(5000);
}
