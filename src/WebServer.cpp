#include <WebServer.h>
#include <main.h>
#include <FileConfig.h>

void handle_ConfigJson()
{
    String json = "{";
    json += "\"SSDP\":\"";
    json += SSDP_Name;
    // Имя сети
    json += "\",\"ssid\":\"";
    json += _ssid;
    // Пароль сети
    json += "\",\"password\":\"";
    json += _password;
    // Имя точки доступа
    json += "\",\"ssidAP\":\"";
    json += _ssidAP;
    // Пароль точки доступа
    json += "\",\"passwordAP\":\"";
    json += _passwordAP;
    // Времянная зона
    json += "\",\"timezone\":\"";
    json += timezone;
    // IP устройства
    json += "\",\"ip\":\"";
    json += WiFi.localIP().toString();
    json += "\"}";
    HTTP.send(200, "text/json", json);
}

void handle_Set_Ssdp()
{
    SSDP_Name = HTTP.arg("ssdp");
    saveConfig();
    HTTP.send(200, "text/plain", "OK");
}

void handle_Set_Ssid()
{
    _ssid = HTTP.arg("ssid");
    _password = HTTP.arg("password");
    saveConfig();
    HTTP.send(200, "text/plain", "OK");
}

void handle_Set_Ssidap()
{
    _ssidAP = HTTP.arg("ssidAP");
    _passwordAP = HTTP.arg("passwordAP");
    saveConfig();
    HTTP.send(200, "text/plain", "OK");
}

void handle_time_zone()
{

    timezone = HTTP.arg("timezone").toInt();
    saveConfig();
    HTTP.send(200, "text/plain", "OK");
}

void handleRestart()
{
    String restart = HTTP.arg("device");
    if (restart == "ok")
        ESP.restart();
    HTTP.send(200, "text/plain", "OK");
}

void HTTP_init(void)
{

    HTTP.on("/configs.json", handle_ConfigJson);
    HTTP.on("/ssdp", handle_Set_Ssdp);
    HTTP.on("/TimeZone", handle_time_zone);
    HTTP.on("/ssid", handle_Set_Ssid);
    HTTP.on("/ssidap", handle_Set_Ssidap);
    HTTP.on("/restart", handleRestart);

    HTTP.begin();
}
