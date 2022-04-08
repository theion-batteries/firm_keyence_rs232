/**
 * @file main.cpp
 * @author sami dhiab (sami@theion.de)
 * @brief 
 * @version 0.1
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "DistanceSensor.hpp"

// Create Objects 
  DistanceSensor DS_x(XSensorHead);
  DistanceSensor DS_y(YSensorHead);
  DistanceSensor DS_z(ZSensorHead);

void setup() {
  USBPORT.begin(BAUDRATE);
  DS_x.initKeyenceCom();
}
void loop() { 
  DS_x.getCurrentDistance();
}
