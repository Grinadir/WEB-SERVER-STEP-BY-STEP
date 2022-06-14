#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

void HTTP_init(void);
String GetTime();
String GetDate();


#endif // WEBSERVER_H