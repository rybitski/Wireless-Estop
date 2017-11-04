#include <ESP8266WiFi.h>
#include<WiFiClient.h> 
#include<ESP8266WebServer.h>`

const char *ssid = "esp8266";
const char *password = "password";

ESP8266WebServer server(80);

void handle_led1(){
  digitalWrite(2, 1);
  server.send(200, "text/plain", String("LED ENCENDICO ")); 
}

void handle_led0(){
  digitalWrite(2, 0);
  server.send(200, "text/plain", String("LED APAGADO ")); 
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);

  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("HTTP server started");
  server.on("/led1",handle_led1);
  server.on("/led0",handle_led0);
}

void loop() {
  server.handleClient();
}
