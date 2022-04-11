/**
 * @file main.cpp
 * @author sami dhiab (sami@theion.de)
 * @brief test keyence sensor functionality
 * @version 0.1
 * @date 2022-02-11
 * @copyright Copyright (c) 2022
 * 
 */

#include "DistanceSensor.hpp"

// Create Objects 
  DistanceSensor DS_x(XSensorHead);
  DistanceSensor DS_y(YSensorHead);
  DistanceSensor DS_z(ZSensorHead);
// while we can not use inline static in cpp 11
// we can't define static vector inside class
// composition is better than inheritance 
void setup() {
  Serial.begin(BAUDRATE);
  Keyence_base::listHeads();
  DS_x.setKeyenceCom();
}

void loop() { 
  //DS_x.getCurrentDistance();
  //DS_y.getCurrentDistance();
  //DS_z.getCurrentDistance();
  DS_x.IkeyenceRS232->getValueMultipleOutputHead("111000000000");
  //DS_x.IkeyenceRS232->getValueOutputHeadAll();
  delay(300);


}
