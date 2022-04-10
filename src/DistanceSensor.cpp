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
#include "DistanceSensor.hpp"

#ifdef hc_sr04
DistanceSensor::DistanceSensor(int EchoPin, int TrigPin){
    this->EchoPin=EchoPin;
    this->TrigPin=TrigPin;
    pinMode(EchoPin, INPUT);
    pinMode(TrigPin,OUTPUT);
    digitalWrite(TrigPin, LOW);
}
#endif
#ifdef keyence
DistanceSensor::DistanceSensor(int OutputHeadNumber)
{

this->HeadNum=OutputHeadNumber;


}

void DistanceSensor::setKeyenceCom()
{
    IkeyenceRS233->initKeyenceCom();
    IkeyenceRS233->setGeneralMode();
}

#endif

// generic methods
double DistanceSensor::getCurrentDistance()
{
    #ifdef hc_sr04 //how to read with hc_sr04
        unsigned long t1;
        unsigned long t2;
        unsigned long pulse_width;
        float cm;
        digitalWrite(TrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(TrigPin, LOW);
        while ( digitalRead(EchoPin) == 0 );
        t1 = micros();
        while ( digitalRead(EchoPin) == 1);
        t2 = micros();
        pulse_width = t2 - t1;
        cm = pulse_width / 58.0;
        long mm = cm*10;
        currentDistance=mm;
        return currentDistance;
    #endif
    /******* get values from keyence *********/
    #ifdef keyence //how to read with keyence
    return currentDistance=IkeyenceRS233->getValueSingleOutputHead(this->HeadNum);
    #endif
}
void DistanceSensor::printDistance(float val)
{
        Serial.println("current distance");
        Serial.println(val);
}
