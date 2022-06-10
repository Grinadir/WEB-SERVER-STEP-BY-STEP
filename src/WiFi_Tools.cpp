#include <WiFi_Tools.h>
#include <main.h>

extern String _ssid;
extern String _password;
extern String _ssidAP;
extern String _passwordAP;


bool StartAPMode()
{
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
    return true;

}

void WIFIinit() {
    WiFi.mode(WIFI_STA);
    byte tries=11;
    WiFi.begin(_ssid.c_str(), _password.c_str());
    while (--tries&&WiFi.status()!=WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    if (WiFi.status()!=WL_CONNECTED){
        Serial.println("");
        Serial.println("WiFI up AP");
        StartAPMode();
    }
    else{
        Serial.println("");
        Serial.println("WiFI connected");
        Serial.print("IP address: https://");
        Serial.println(WiFi.localIP());
    }




}

