#include <Arduino.h>
#include "FlexLightMesh.h"
#include "FlexLightWiFi.h"
#include "FlexLightWebserver.h"
//#include "FlexLightBluetooth.h"
#include "FlexLightLED.h"

#define BAUD  115200

void setup() {
    //recovery
    delay(3000);

    Serial.begin(BAUD);

    setupMesh();
    setupNetworking();
    setupWebserver();
    //setupBluetooth();
    setupLED();

    Serial.println("ESP32 setup completed");
}

void loop() {
    loopLED();
    loopMesh();
}
