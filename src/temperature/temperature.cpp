//
// Created by noahb on 18.04.2022.
//
#include "temperature.h"

bool temperature::onPowerState(const String &deviceId, bool &state) {
    deviceIsOn = state;
    return true;
}

void temperature::handleTemperaturesensor() {
    if (!deviceIsOn) return;

    unsigned long actualMillis = millis();
    if (actualMillis - lastEvent < waitTime) return;

    currTemperature = dht->readTemperature();
    currHumidity = dht->readHumidity();

    if (isnan(currTemperature) || isnan(currHumidity)){
        return;
    }

    if (currTemperature == lastTemperature || currHumidity == lastHumidity) return;

    myTemp->sendTemperatureEvent(currTemperature, currHumidity);


    lastTemperature = currTemperature;
    lastHumidity = currHumidity;
    lastEvent = actualMillis;
}

temperature::temperature(DHT *dht, SinricProTemperaturesensor *myTemp, long waitTime) {
    this->dht = dht;
    this->myTemp = myTemp;
    this->waitTime = waitTime;
    this->lastEvent = (-waitTime);
}
