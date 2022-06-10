#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <ESP8266WebServer.h>

extern ESP8266WebServer HTTP;
extern IPAddress apIP;
extern String _ssid;
extern String _password;
extern String _ssidAP;
extern String _passwordAP;
extern String SSDP_Name;
extern int timezone;
extern String jsonConfig;

#endif // MAIN_H