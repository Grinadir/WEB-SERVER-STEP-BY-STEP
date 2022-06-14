//Загрузка данных сохраненных в файл config.json
#include <FS.h>
#include <main.h>
#include <ArduinoJson.h>
#include <FileConfig.h>
#include <WebServer.h>


bool saveConfig(){
      // Резервируем памяь для json обекта буфер может рости по мере необходимти предпочтительно для ESP8266 
  DynamicJsonBuffer jsonBuffer;
  //  вызовите парсер JSON через экземпляр jsonBuffer
  JsonObject& json = jsonBuffer.parseObject(jsonConfig);
  // Заполняем поля json 
  json["SSDPName"] = SSDP_Name;
  json["ssidAPName"] = _ssidAP;
  json["ssidAPPassword"] = _passwordAP;
  json["ssidName"] = _ssid;
  json["ssidPassword"] = _password;
  json["timezone"] = timezone;
  json["ip"]=WiFi.localIP().toString();
  json["time"]=GetTime();
  json["date"]=GetDate();
  // Помещаем созданный json в глобальную переменную json.printTo(jsonConfig);
  json.printTo(jsonConfig);
  // Открываем файл для записи
  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    //Serial.println("Failed to open config file for writing");
    return false;
  }
  // Записываем строку json в файл 
  json.printTo(configFile);
  return true;
    
}


bool loadConfig(){
    File configFile=SPIFFS.open("/config.json", "r");
    if(!configFile) {
        //Если файл не найден
        Serial.println("Failed to open config file");
        // Создаем файл записав в него данные по умолчанию
        saveConfig();
        return false;
    } 
    //Проверяем размер файла, будем использовать файл размером меньше 1024 байта
    size_t size=configFile.size();
    if(size>1024){
        Serial.println("Config file size is too large");
        return false;
    }
    //загружаем файл конфигурации в глобальную переменную
    jsonConfig=configFile.readString();
    //Резервируем память для json объекта, буфер может рости по мере необходимости предпочтительно для ESP8266
    DynamicJsonBuffer jsonBuffer;
    //Вызовем парсер JSON через экземпляр jsonBuffer
    //строку возьмем из глобальной переменной String jsonConfig
    JsonObject& root=jsonBuffer.parseObject(jsonConfig);
    //Теперь можно получить значения из root
    _ssidAP=root["ssidAPName"].as<String>();
    _passwordAP=root["ssidAPPassword"].as<String>();
    timezone=root["timezone"];
    SSDP_Name=root["SSDPName"].as<String>();
    _ssid=root["ssidName"].as<String>();
    Serial.println(_ssid);
    //_password=root["ssidPassword"].as<String>();
    Serial.println(_password);
    Serial.println("File Config loaded!");
    return true;

}


