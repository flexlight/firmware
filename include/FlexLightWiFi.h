#ifndef FlexLightWiFi_h
#define FlexLightWiFi_h

#include <Arduino.h>
#include <WiFi.h>

const char *ssid = "FlexLight";
const char *password = "12345678";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void setupNetworking() {
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    
    Serial.println("WIFI setup complete");
}

#endif