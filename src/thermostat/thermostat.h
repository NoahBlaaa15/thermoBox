//
// Created by noahb on 19.04.2022.
//
#include "Arduino.h"
#include "SinricProThermostat.h"
#include "SinricPro.h"
#include "privateConfig.h"

#ifndef THERMOBOX_THERMOSTAT_H
#define THERMOBOX_THERMOSTAT_H


//attributes for thermostat
bool deviceIsOn_Thermostat;

SinricProThermostat &iotThermostat = SinricPro[thermostatId];

//functions for thermostat
bool onPowerState_Thermostat(const String &deviceId, bool &state){
    deviceIsOn_Thermostat = state;
    return true;
}

void setupThermostat(){
    iotThermostat.onPowerState(onPowerState_Thermostat);
}

void handleThermostat(){

}

#endif //THERMOBOX_THERMOSTAT_H
