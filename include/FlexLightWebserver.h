#ifndef FlexLightWebserver_h
#define FlexLightWebserver_h

#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

void setupWebserver() {
    if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server.on("/bootstrap.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/bootstrap.bundle.min.js", "text/javascript");
    });

    server.on("/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/bootstrap.min.css", "text/css");
    });
  
    server.begin();
    Serial.println("Webserver setup complete");
}

#endif