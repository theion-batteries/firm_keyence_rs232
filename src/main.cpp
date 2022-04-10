/**
 * @file main.cpp
 * @author sami dhiab (sami@theion.de)
 * @brief 
 * @version 0.1
 * @date 2022-02-11
 * @copyright Copyright (c) 2022
 * 
 */

#include "DistanceSensor.hpp"
int Keyence_base::HeadsCount=0;
std::vector<int> Keyence_base::NumUsedHeads;
// Create Objects 
DistanceSensor DS_x(XSensorHead);
DistanceSensor DS_y(YSensorHead);
DistanceSensor DS_z(ZSensorHead);
void setup() {
  USBPORT.begin(BAUDRATE);
  DS_x.setKeyenceCom();
  //Keyence_rs232_interface::initKeyenceCom();
  Keyence_base::printNumHeads();
  Keyence_base::listUsedHeads();
}
void loop() { 
  DS_x.getCurrentDistance();
  DS_y.getCurrentDistance();
  DS_z.getCurrentDistance();
  delay(500); // delay for next mesurement for test
}
