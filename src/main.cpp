#include <Arduino.h>
#include <WiFi_Tools.h>
#include <main.h>
#include <WebServer.h>
#include <SSDP.h>

ESP8266WebServer HTTP(80);
IPAddress apIP(192, 168, 4, 1);

String _ssid ="SAURES_R1";
String _password="1400266140k";
String _ssidAP="ESP8266_testing";
String _passwordAP="";
String SSDP_Name="SSDP-test";


void setup() {
  Serial.begin(74880);
  Serial.println("");
  Serial.println("Start WIFI");
  WIFIinit();
  Serial.println("Start SSDP");
  SSDP_init();
  Serial.println("Start WebServer");
  HTTP_init();
}

void loop() {
  HTTP.handleClient();
  delay(1);
  // put your main code here, to run repeatedly:
}