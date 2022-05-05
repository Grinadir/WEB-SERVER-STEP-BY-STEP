#include <SSDP.h>
#include <WebServer.h>
#include <main.h>

void SSDP_init(void)
{
    HTTP.on("/description.xml", HTTP_GET, []()
            {
                SSDP.schema(HTTP.client());
            });
    SSDP.setDeviceType("upnp:rootdevice");
    SSDP.setSchemaURL("description.xml");
    SSDP.setHTTPPort(80);
    SSDP.setName(SSDP_Name);
    SSDP.setSerialNumber("1111111");
    SSDP.setURL("/");
    SSDP.setModelName("SSDP-Test");
    SSDP.setModelNumber("NodeMCU");
    SSDP.setModelURL("http://esp8266.ru");
    SSDP.setManufacturer("Super Tester");
    SSDP.setManufacturerURL("http://www.google.ru");
    SSDP.begin();
}