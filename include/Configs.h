/**
   @file Configs.h
   @author sami dhiab (sami@theion.de)
   @brief Place the definition of Macros here like pins, enumerate and so on
   @version 0.1
   @date 2022-02-10

   @copyright Copyright (c) 2022

*/
/**********MACROS****************/
#pragma once
#include <ArduinoSTL.h>
//#define VIRTUAL
//#define DEBUG_ALIGN
//#define MICRO // define this to switch to micrometers
#define DEBUG
#define USBPORT Serial
#define BAUDRATE 115200

//#define COMMUNICATION
//#define TEST
//#define RELEASE
#define TIMEOUT false
//#define DEBUG_UP_DISTANCE
//#define DEBUG_UP
//#define DEBUG_DOWN
//#define DEBUG_DOWN_DISTANCE
/*********** define Motors***************/
// Motor X
#define XMs1_pin A10 // microsteps are coupled together in hardware
#define XMs2_pin A10
#define XMs3_pin A10
#define XDir_pin 5
#define XEnable_pin 8 // same enable for 3 motors
#define XStep_pin 2
// Motor Y
#define YMs1_pin A10
#define YMs2_pin A10
#define YMs3_pin A10
#define YDir_pin 6
#define YEnable_pin 8 // same pin for 3
#define YStep_pin 3
// Motor Z
#define ZMs1_pin A10
#define ZMs2_pin A10
#define ZMs3_pin A10
#define ZDir_pin 7
#define ZEnable_pin 8
#define ZStep_pin 4
// PrintHEad motor
#define PHMs1_pin A10
#define PHMs2_pin A10
#define PHMs3_pin A10
#define PHDir_pin 9
#define PHEnable_pin 8
#define PHStep_pin 10
/************* endstops***********/
// Endswitch
#define E_X 21
// Endswitch
#define E_Y 22
// Endswitch
#define E_Z 52
// define light barriers
#define LB_X 26
#define LB_Y 24
#define LB_Z 48
// safety
#define E_Emergency A12
/*********** Distance sensors *********/
//define which distance sensor is used: uncomment the wrong one
//#define hc_sr04
#define keyence
#ifdef hc_sr04
#define Trig A10
#define Echo A10
// Distance Sensor
#define D_X A10 // echo 
#define DT_x A10 // Trigger
// Distance Sensor
#define D_Y A10 //echo 
#define DT_y A10 // Trigger
// Distance Sensor
#define D_Z A10 // echo
#define DT_z A10 // Trigger
#endif
#ifdef keyence

// serial handler
#define KEYENCE_SERIAL_HANDLER Serial1
// serial baudrate
#define KEYENCE_SERIAL_BAUDRATE 115200
// map each sensor head to axis
#define XSensorHead 1
#define YSensorHead 2
#define ZSensorHead 3

// Distance Sensor x
#define D_X 19 // Rx 
#define DT_x 18 // Tx
// Distance Sensor y
#define D_Y 17 //Rx 
#define DT_y 16 // Tx
// Distance Sensor z
#define D_Z 15 // Rx
#define DT_z 14 // Tx
#endif

/******** define generic direction*********/
#define up 1
#define down 0
#define on 0
#define off 1
#define clk 1
#define cclk 0

/***** define generic formula****/
//#define USE_GENERIC_FORMULA
#ifdef USE_GENERIC_FORMULA
// parameters

//#define MEASUREMENT 0 //T mesurement is done later
#define SENSOR_HEIGHT 30 //S: random value
// Generic formula
#define AIR_GAP_BETWEEN_PRINTHEAD_AND_ML -DISTANCE_PRINTHEAD_PLATFORM-PLATFORM_THICKNESS-SENSOR_HEIGHT

#define SENSOR_ABOVE_PLATFORM
//#define SENSOR_UNDER_PLATFORM-
#ifdef SENSOR_ABOVE_PLATFORM
#define SENSOR_HEIGHT 0 //S
#define PLATFORM_THICKNESS 12.5 //mm Z
#endif
#ifdef SENSOR_UNDER_PLATFORM
#define SENSOR_HEIGHT -SENSOR_HEIGHT
#define PLATFORM_THICKNESS 0
#endif
#endif

/*************** mechanical parameters**********/
// Generic Values
#define MotorLength 27.2 //mm
#define LeadScrewLEngth 95 //mm
#define Linear_travel_per_step 0.006 //mm
#define Angle_per_step 1.8 //degree
#define EndeffectorThickness 28 //mm
#define RodLength 115 //mm Stab
#define MotorSensorHolderThickness 12.5 //mm
#define DISTANCE_PRINTHEAD_PLATFORM 123.080 //mm Y
#define SensorThreashold 2 //mm
#define SensorThickness 30 // mm
#define AllowedPath LeadScrewLEngth-(MotorLength+MotorSensorHolderThickness) //
#define RodLength_EndeffectorThickness RodLength+EndeffectorThickness // min =< 115+28=143, mesured + SensorThickness
// RodLength_EndeffectorThickness + LeadScrewLEngth = max >=95 + 143 = 238
#define MicroResolution 4 // 

/********** enumerations*********/
enum retVal {
  not_ok = false,
  ok = true,
  X_OK = 1,
  Y_OK = 2,
  Z_OK = 3,
};

