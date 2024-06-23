#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Use `const char*` for the SSID and password strings
const char* ssid = "esp8266_ap";
const char* password = "12345678";

int green = D2; // Define pin D2 for the green LED

// Set the static IP address
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80); // Create an ESP8266WebServer instance listening on port 80
bool LEDStatus = LOW; // Initialize LED status as LOW (off)

void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging

  pinMode(green, OUTPUT); // Set green LED pin as output

  // Initialize WiFi access point with specified SSID, password, IP configuration
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(1000); // Delay to ensure WiFi AP initialization

  // Set up HTTP routes
  server.on("/", handle_OnConnect); // Handler for main page
  server.on("/toggle", handle_toggleLED); // Handler for toggling LED
  server.onNotFound(handle_NotFound); // Handler for 404 Not Found

  server.begin(); // Start the HTTP server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); // Handle incoming client requests

  // Toggle the green LED based on LEDStatus
  if (LEDStatus) {
    digitalWrite(green, HIGH); // Turn on green LED
  } else {
    digitalWrite(green, LOW); // Turn off green LED
  }
}

// Function to generate HTML page content
String getHTML() {
  String htmlCode = "<!DOCTYPE html>\n";
  htmlCode += "<html>\n";
  htmlCode += "<head>\n";
  htmlCode += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />\n";
  htmlCode += "<title>VibeRhythm Fiesta</title>\n";
  
  // CSS styles for the HTML page
  htmlCode += "<style>\n";
  htmlCode += "body { font-family: Arial; text-align: center; }\n";
  htmlCode += ".button { padding: 10px 20px; font-size: 20px; border: none; cursor: pointer; }\n";
  htmlCode += ".button.on { background-color: green; color: white; }\n";
  htmlCode += ".button.off { background-color: red; color: white; }\n";
  htmlCode += "</style>\n";
  
  // JavaScript for handling button click to toggle LED
  htmlCode += "<script>\n";
  htmlCode += "function toggleLED() { \n";
  htmlCode += "  var xhttp = new XMLHttpRequest();\n";
  htmlCode += "  xhttp.onreadystatechange = function() { \n";
  htmlCode += "    if (this.readyState == 4 && this.status == 200) { \n";
  htmlCode += "      document.getElementById(\"ledButton\").className = this.responseText;\n";
  htmlCode += "      document.getElementById(\"ledButton\").innerText = (this.responseText === 'button on') ? 'Turn Off' : 'Turn On';\n";
  htmlCode += "    }\n";
  htmlCode += "  };\n";
  htmlCode += "  xhttp.open(\"GET\", \"/toggle\", true);\n";
  htmlCode += "  xhttp.send();\n";
  htmlCode += "}\n";
  htmlCode += "</script>\n";
  
  htmlCode += "</head>\n";
  htmlCode += "<body>\n";
  htmlCode += "<h1>ESP8266 WEB SERVER</h1>\n";
  htmlCode += "<h3>Simple demo using Access Point (AP) Mode</h3>\n";
  
  // Button element to toggle LED, with dynamic class and text based on LEDStatus
  htmlCode += "<button id=\"ledButton\" class=\"button " + String(LEDStatus ? "on" : "off") + "\" onclick=\"toggleLED()\">" + String(LEDStatus ? "Turn Off" : "Turn On") + "</button>\n";
  
  htmlCode += "</body>\n";
  htmlCode += "</html>\n";
  
  return htmlCode;
}

// Handler for root endpoint "/"
void handle_OnConnect() {
  server.send(200, "text/html", getHTML()); // Send HTML page response
}

// Handler for "/toggle" endpoint to toggle LED status
void handle_toggleLED() {
  LEDStatus = !LEDStatus; // Toggle LEDStatus
  server.send(200, "text/plain", String(LEDStatus ? "button on" : "button off")); // Send response with current button state
}

// Handler for 404 Not Found errors
void handle_NotFound() {
  server.send(404, "text/plain", "Not Found"); // Send 404 response for unrecognized endpoints
}
