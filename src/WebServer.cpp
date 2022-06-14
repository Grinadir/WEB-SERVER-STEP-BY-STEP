#include <WebServer.h>
#include <main.h>
#include <FileConfig.h>
#include <ESP8266HTTPUpdateServer.h>
#include <time.h>
#include <ArduinoJson.h>

ESP8266HTTPUpdateServer httpUpdater;

void timeSynch(int zone)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        configTime(zone * 3600, 0, "pool.ntp.org", "ru.pool.ntp.org");
        int i = 0;
        Serial.println("\nWaiting for time");
        while (!time(nullptr) && i < 10)
        {
            Serial.println(".");
            i++;
            delay(1000);
        }
        Serial.println("");
        Serial.println("ITime Ready!");
        Serial.println(GetTime());
        Serial.println(GetDate());
    }
}
void handle_ConfigJson()
{
  String root = "{}";  // Формировать строку для отправки в браузер json формат
  //{"SSDP":"SSDP-test","ssid":"home","password":"i12345678","ssidAP":"WiFi","passwordAP":"","ip":"192.168.0.101"}
  // Резервируем память для json обекта буфер может рости по мере необходимти, предпочтительно для ESP8266
  DynamicJsonBuffer jsonBuffer;
  //  вызовите парсер JSON через экземпляр jsonBuffer
  JsonObject& json = jsonBuffer.parseObject(root);
  // Заполняем поля json
  json["SSDP"] = SSDP_Name;
  json["ssidAP"] = _ssidAP;
  json["passwordAP"] = _passwordAP;
  json["ssid"] = _ssid;
  json["password"] = _password;
  json["timezone"] = timezone;
  json["ip"] = WiFi.localIP().toString();
  json["time"] = GetTime();
  json["date"] = GetDate();
  // Помещаем созданный json в переменную root
  root = "";
  json.printTo(root);
  HTTP.send(200, "text/json", root);
}

void handle_Time()
{
    timeSynch(timezone);
    HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
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

String GetTime()
{
    time_t now = time(nullptr);
    String Time = "";
    Time += ctime(&now);
    int i = Time.indexOf(":");
    Time = Time.substring(i - 2, i + 6);
    return Time;
}

String GetDate()
{
    time_t now = time(nullptr);
    String Data = "";
    Data += ctime(&now);
    int i = Data.lastIndexOf(" ");
    String Time = Data.substring(i - 8, i + 1);
    Data.replace(Time, "");
    return Data;
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
    timeSynch(timezone);
    HTTP.on("/configs.json", handle_ConfigJson);
    HTTP.on("/ssdp", handle_Set_Ssdp);
    HTTP.on("/TimeZone", handle_time_zone);
    HTTP.on("/ssid", handle_Set_Ssid);
    HTTP.on("/ssidap", handle_Set_Ssidap);
    HTTP.on("/restart", handleRestart);
    HTTP.on("/Time", handle_Time);          // Синхронизировать время устройства по запросу вида /Time
    HTTP.on("/TimeZone", handle_time_zone); // Установка времянной зоны по запросу вида http://192.168.0.101/TimeZone?timezone=3
    httpUpdater.setup(&HTTP);

    HTTP.begin();
}
