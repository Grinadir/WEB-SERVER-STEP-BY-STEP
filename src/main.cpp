#include <Arduino.h>
#include <WiFi_Tools.h>
#include <main.h>
#include <WebServer.h>
#include <SSDP.h>
#include <FS_FILE_SYSTEM.h>
#include <FileConfig.h>


ESP8266WebServer HTTP(80);
IPAddress apIP(192, 168, 4, 1);

String _ssid ="SAURES_R123223";
String _password="14002661401";
String _ssidAP="ESP8266_testing";
String _passwordAP="";
String SSDP_Name="SSDP-test";
int timezone=3;
String jsonConfig = "{}";


void setup() {
  Serial.begin(74880);
  Serial.println("");
  Serial.println("Start File System");
  FS_init();
  Serial.println("load File Config");
  loadConfig();

  Serial.println("Start WIFI");
  WIFIinit();
  Serial.println("Start SSDP");
  SSDP_init();
  Serial.println("Start Web Server");
  HTTP_init();
}

void loop() {
  HTTP.handleClient();
  delay(1);
  // put your main code here, to run repeatedly:
}