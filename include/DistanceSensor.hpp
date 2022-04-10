/**
 * @file DistanceSensor.hpp
 * @author sami dhiab (sami@theion.de)
 * @brief 
 * @version 0.1
 * @date 2022-02-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "Configs.h"
#include "Keyence_API.h"
class DistanceSensor
{
    public:
    int Pin;
    bool state;
    double currentDistance;
    #ifdef hc_sr04
    int EchoPin;
    int TrigPin;
    DistanceSensor(int EchoPin, int TrigPin);
    #endif
    #ifdef keyence
    Keyence_rs232_interface* IkeyenceRS232;
    int HeadNum;
    DistanceSensor(int OutputHeadNumber);
    void setKeyenceCom();
    #endif
    //generic methods
    double getCurrentDistance();
    void printDistance(float val);
};