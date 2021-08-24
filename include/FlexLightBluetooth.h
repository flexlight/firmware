#ifndef FlexLightBluetooth_h
#define FlexLightBluetooth_h

#include <Arduino.h>
#include <BluetoothSerial.h>

#define BT_DEVICE_NAME  "FlexLight"
BluetoothSerial SerialBT;

void setupBluetooth() {
    SerialBT.begin(BT_DEVICE_NAME);
    Serial.println("Bluetooth setup complete");
}

void handleBluetoothConnection() {
     if (Serial.available()) {
      SerialBT.write(Serial.read());
    }
    if (SerialBT.available()) {
      Serial.write(SerialBT.read());
    }
}

#endif