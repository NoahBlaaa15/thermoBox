#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "SinricPro.h"
#include "SinricProBlinds.h"
#include "SinricProTemperaturesensor.h"
#include "SinricProThermostat.h"
#include "DHT.h"
#include "privateConfig.h"
#include "temperature/temperature.h"

#define BAUD_RATE         115200

DHT dht(2, DHT11);

SinricProThermostat &myThermostat = SinricPro[thermostatId];
SinricProTemperaturesensor &myTemp = SinricPro[tempId];
SinricProBlinds &myBlinds = SinricPro[blindsId];

temperature tempSensor;

bool onPowerState(const String &deviceId, bool &state) {
    Serial.printf("Temperaturesensor turned %s (via SinricPro) \r\n", state?"on":"off");
    deviceIsOn = state; // turn on / off temperature sensor
    return true; // request handled properly
}

void setupWiFi() {
    Serial.printf("\r\n[Wifi]: Connecting");
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.printf(".");
        delay(250);
    }
    IPAddress localIP = WiFi.localIP();
    Serial.printf("connected!\r\n[WiFi]: IP-Address is %d.%d.%d.%d\r\n", localIP[0], localIP[1], localIP[2], localIP[3]);
}

void setupSinricPro() {

    myTemp.onPowerState(onPowerState);

    SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); });
    SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
    SinricPro.restoreDeviceStates(true);
    SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
    Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");

    dht.begin();

    setupWiFi();
    setupSinricPro();
}

void handleTemperaturesensor() {

}

void loop() {
    SinricPro.handle();
    handleTemperaturesensor();
}