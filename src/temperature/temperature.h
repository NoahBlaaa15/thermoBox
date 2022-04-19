//
// Created by noahb on 18.04.2022.
//
#include "Arduino.h"
#include "DHT.h"
#include "SinricProTemperaturesensor.h"
#include "SinricPro.h"
#include "privateConfig.h"

#ifndef THERMOBOX_TEMPERATURE_H
#define THERMOBOX_TEMPERATURE_H

#define eventWaitTime_Temperature 60000

//attributes for temperature sensor
bool deviceIsOn_Temperature;                              // Temperature sensor on/off state
float currTemperature_Temperature;                            // actual temperature
float currHumidity_Temperature;                               // actual humidity
float lastTemperature_Temperature;                        // last known temperature (for compare)
float lastHumidity_Temperature;
unsigned long lastEvent_Temperature;

DHT dht_Temperature = DHT(2, DHT11);
SinricProTemperaturesensor &iotTemp = SinricPro[tempId];


//functions for temperature sensor
bool onPowerState_Temperature(const String &deviceId, bool &state){
    deviceIsOn_Temperature = state;
    return true;
}

void setupTemperature(){
    dht_Temperature.begin();

    iotTemp.onPowerState(onPowerState_Temperature);

    lastEvent_Temperature = (-eventWaitTime_Temperature);
}

void handleTemperature(){
    if (!deviceIsOn_Temperature) return;

    unsigned long actualMillis = millis();
    if (actualMillis - lastEvent_Temperature < eventWaitTime_Temperature) return;

    currTemperature_Temperature = dht_Temperature.readTemperature();
    currHumidity_Temperature = dht_Temperature.readHumidity();

    if (isnan(currTemperature_Temperature) || isnan(currHumidity_Temperature)){
        return;
    }

    if (currTemperature_Temperature == lastTemperature_Temperature || currHumidity_Temperature == lastHumidity_Temperature) return;

    iotTemp.sendTemperatureEvent(currTemperature_Temperature, currHumidity_Temperature);


    lastTemperature_Temperature = currTemperature_Temperature;
    lastHumidity_Temperature = currHumidity_Temperature;
    lastEvent_Temperature = actualMillis;
}

#endif //THERMOBOX_TEMPERATURE_H
