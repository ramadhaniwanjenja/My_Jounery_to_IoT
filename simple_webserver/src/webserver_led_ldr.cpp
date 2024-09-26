#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "esp8266_shafii";
const char* password = "12345678";

int green = D2;
int ldrPin = A0; // Analog pin A0 for LDR
int ldrValue = 0;

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);
bool LEDStatus = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(green, OUTPUT);
  
  // Set up Wi-Fi Access Point
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(1000);

  // Define routes
  server.on("/", handle_OnConnect);
  server.on("/toggle", handle_toggleLED);
  server.on("/ldr", handle_LDR);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  if (LEDStatus) {
    digitalWrite(green, HIGH);
  } else {
    digitalWrite(green, LOW);
  }
}

String getHTML() {
  String htmlCode = "<!DOCTYPE html>\n";
  htmlCode += "<html>\n";
  htmlCode += "<head>\n";
  htmlCode += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />\n";
  htmlCode += "<title>ESP8266 Control Panel</title>\n";
  htmlCode += "<style>\n";
  htmlCode += "body { background-color: #282C34; color: white; font-family: Arial, sans-serif; text-align: center; padding: 50px; }\n";
  htmlCode += "h1 { color: #61DAFB; }\n";
  htmlCode += ".button { padding: 15px 30px; font-size: 18px; border: none; cursor: pointer; margin: 10px; }\n";
  htmlCode += ".button.on { background-color: #4CAF50; color: white; }\n";
  htmlCode += ".button.off { background-color: #F44336; color: white; }\n";
  htmlCode += ".container { max-width: 600px; margin: auto; border-radius: 15px; box-shadow: 0px 0px 15px rgba(0, 0, 0, 0.5); padding: 20px; background-color: #3A3F44; }\n";
  htmlCode += ".ldr-display { font-size: 24px; margin-top: 20px; color: #FFD700; }\n";
  htmlCode += "</style>\n";
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
  htmlCode += "function getLDRValue() { \n";
  htmlCode += "  var xhttp = new XMLHttpRequest();\n";
  htmlCode += "  xhttp.onreadystatechange = function() { \n";
  htmlCode += "    if (this.readyState == 4 && this.status == 200) { \n";
  htmlCode += "      document.getElementById(\"ldrValue\").innerText = this.responseText;\n";
  htmlCode += "    }\n";
  htmlCode += "  };\n";
  htmlCode += "  xhttp.open(\"GET\", \"/ldr\", true);\n";
  htmlCode += "  xhttp.send();\n";
  htmlCode += "}\n";
  htmlCode += "setInterval(getLDRValue, 1000);\n"; // Refresh LDR value every second
  htmlCode += "</script>\n";
  htmlCode += "</head>\n";
  htmlCode += "<body>\n";
  htmlCode += "<div class=\"container\">\n";
  htmlCode += "<h1>ESP8266 Control Panel</h1>\n";
  htmlCode += "<h3>Simple demo using Access Point (AP) Mode</h3>\n";
  htmlCode += "<button id=\"ledButton\" class=\"button " + String(LEDStatus ? "on" : "off") + "\" onclick=\"toggleLED()\">" + String(LEDStatus ? "Turn Off" : "Turn On") + "</button>\n";
  htmlCode += "<div class=\"ldr-display\">LDR Value: <span id=\"ldrValue\">Loading...</span></div>\n";
  htmlCode += "</div>\n";
  htmlCode += "</body>\n";
  htmlCode += "</html>\n";
  return htmlCode;
}


void handle_OnConnect() {
  server.send(200, "text/html", getHTML());
}

void handle_toggleLED() {
  LEDStatus = !LEDStatus;
  server.send(200, "text/plain", String(LEDStatus ? "button on" : "button off"));
}

void handle_LDR() {
  ldrValue = analogRead(ldrPin);
  server.send(200, "text/plain", String(ldrValue));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not Found");
}