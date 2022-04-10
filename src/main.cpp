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
  Serial.println(Keyence_base::NumUsedHeads.size());
  Serial.println(Keyence_base::HeadsCount);
  Keyence_base::printArrayElements(Keyence_base::HeadsArray);
  Keyence_base::transformArrayToVector(Keyence_base::HeadsArray,Keyence_base::NumUsedHeads);
  Keyence_base::listHeads();
}

void loop() { 
  DS_x.getCurrentDistance();
  DS_y.getCurrentDistance();
  DS_z.getCurrentDistance();
  delay(500); // delay for next mesurement for test
}
