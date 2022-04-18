//
// Created by noahb on 18.04.2022.
//

#include "temperature.h"


bool temperature::onPowerState(const String &deviceId, bool &state) {
    return false;
}

void temperature::handleTemperaturesensor() {
    if (!deviceIsOn) return;

    unsigned long actualMillis = millis();
    if (actualMillis - lastEvent < waitTime) return;

    currTemperature = dht.readTemperature();
    currHumidity = dht.readHumidity();

    if (isnan(currTemperature) || isnan(currHumidity)){
        return;
    }

    if (currTemperature == lastTemperature || currHumidity == lastHumidity) return;

    myTemp.sendTemperatureEvent(currTemperature, currHumidity);


    lastTemperature = currTemperature;  // save actual temperature for next compare
    lastHumidity = currHumidity;        // save actual humidity for next compare
    lastEvent = actualMillis;
    // save actual time for next compare
}

temperature::temperature(DHT &dht, SinricProTemperaturesensor &myTemp, long waitTime) {
    this->dht = dht;
    this->myTemp = myTemp;
    this->waitTime = waitTime;
    this->lastEvent = (-waitTime);
}
