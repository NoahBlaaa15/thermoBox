#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "SinricPro.h"
#include "privateConfig.h"
#include "temperature/temperature.h"
#include "blinds/blinds.h"
#include "thermostat/thermostat.h"

#define BAUD_RATE         115200

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
    SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); });
    SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
    SinricPro.restoreDeviceStates(true);
    SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
    Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");

    setupThermostat();
    setupTemperature();
    setupBlinds();

    setupWiFi();
    setupSinricPro();
}

void loop() {
    SinricPro.handle();
    handleTemperature();
}