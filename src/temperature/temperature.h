//
// Created by noahb on 18.04.2022.
//
#include "Arduino.h"
#include "DHT.h"
#include "SinricProTemperaturesensor.h"

#ifndef THERMOBOX_TEMPERATURE_H
#define THERMOBOX_TEMPERATURE_H

class temperature {
private:
    bool deviceIsOn;                              // Temeprature sensor on/off state
    float currTemperature;                            // actual temperature
    float currHumidity;                               // actual humidity
    float lastTemperature;                        // last known temperature (for compare)
    float lastHumidity;
    long waitTime;
    unsigned long lastEvent;

    DHT &dht;
    SinricProTemperaturesensor &myTemp;
public:
    explicit temperature(DHT &dht, SinricProTemperaturesensor &myTemp, long waitTime);
    bool onPowerState(const String &deviceId, bool &state);
    void handleTemperaturesensor();
};


#endif //THERMOBOX_TEMPERATURE_H
