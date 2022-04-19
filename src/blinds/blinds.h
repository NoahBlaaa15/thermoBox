//
// Created by noahb on 19.04.2022.
//
#include "Arduino.h"
#include "SinricProBlinds.h"
#include "SinricPro.h"
#include "privateConfig.h"

#ifndef THERMOBOX_BLINDS_H
#define THERMOBOX_BLINDS_H

//attributes for blinds
bool deviceIsOn_Blinds;

SinricProBlinds &iotBlinds = SinricPro[blindsId];

//functions for blinds
bool onPowerState_Blinds(const String &deviceId, bool &state){
    deviceIsOn_Blinds = state;
    return true;
}

void setupBlinds(){
    iotBlinds.onPowerState(onPowerState_Blinds);
}

void handleBlinds(){

}

#endif //THERMOBOX_BLINDS_H
