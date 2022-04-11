/**
   @file Keyence_API.h
   @author sami dhiab (sami@theion.de)
   @brief keyence sensors APIs
   @version 0.1
   @date 2022-04-06

   @copyright Copyright (c) 2022

*/
#include "Keyence_API.h"

//keyence base class 
////define keyence static variables
int Keyence_base::HeadsCount=0;
std::vector<int> Keyence_base::NumUsedHeads;
int Keyence_base::HeadsArray[12];

// list heads availble
void Keyence_base::listHeads()
{   
    
    transformArrayToVector(HeadsArray,NumUsedHeads);
    NumUsedHeads.resize(HeadsCount);
    Serial.println("listing heads in vector container");
      // For loop using iterators
    if(!NumUsedHeads.empty())
    {
      for (std::vector<int>::iterator it = NumUsedHeads.begin(); it != NumUsedHeads.end(); it++)
      {
      Serial.println("next head number:");
      Serial.println(*it);
      }
    }
    else Serial.println("empty heads container");
}
//commands section
// helper method to retrieve commands from map
String Keyence_base::findCommand(String& command, std::map<String, String>& CommandMap)
{
     for (auto it = CommandMap.begin(); it != CommandMap.end(); ++it) 
      {
        if((*it).first==command)
        {
          return (*it).second;
        }
      }	
}

// keyence rs232 

//constructor: take a serial handler and baudrate by default defined in config file
Keyence_rs232_interface::Keyence_rs232_interface(HardwareSerial& serHandler=KEYENCE_SERIAL_HANDLER, unsigned long baud=KEYENCE_SERIAL_BAUDRATE)
{
  this->serialHandler=&serHandler;
  this->baudrate=baud;

}
// if the serial handler is changed dynamicly
void Keyence_rs232_interface::setSerialHandler(HardwareSerial& serHandler)
{
  this->serialHandler=&serHandler;
}
// if baudrate is changed dynamicly
void Keyence_rs232_interface::setSerialBaudrate(unsigned long baud)
{
  this->baudrate=baud;
} 

//init the com with keyence
void Keyence_rs232_interface::initKeyenceCom()
{
serialHandler->begin(baudrate);
}

//get a output value of single head: head number format is 01,02,03... but param is given as int 1,2,3...
double Keyence_rs232_interface::getValueSingleOutputHead(int output_head_Nr)
{
    String Zero="0";
    String Soutput_head_Nr=String(output_head_Nr);
    //write the get value command
    String command="mesure_value_outputN";
    String cmd=findCommand(command,commands);
    if (output_head_Nr<9){
      Soutput_head_Nr=Zero+Soutput_head_Nr;
      }
    cmd+=Soutput_head_Nr;
    serialHandler->print(cmd+CR);
    Serial.println("sending command:");
    Serial.println(cmd+CR);
  if(serialHandler->available()>0)
  {
    // Read data from rs232 port
    String Response=serialHandler->readStringUntil('\r');
    #ifdef DEBUG
    // write the data to the other port
    Serial.println("full response:");
    Serial.println(Response);
    if(Response.indexOf("-")) //if there is a negtaiv sign
    {
      double negativ = -1.0;
    //MS,OUT01,value CR: remove M->,: 9
    Response.remove(0,9); //remove default response
    Response.c_str(); // type cast to double 
    double Res = double(Response.toDouble());
    Res*=negativ;//time * negtaiv
    Serial.println("response to negativ double");
    Serial.println(Res);
    return Res;
    } 
    //MS,OUT01,value CR: remove M->,: 9
    Response.remove(0,9); //remove default response
    Response.toDouble(); // type cast to double * negtaiv    
    Serial.println("response to double");
    Serial.println(Response);
    #endif
    return Response.toDouble();
  }
}
//get output multiple heads in this format: "0-12" example: head 1,2 and 3 will be 111000000000
double* Keyence_rs232_interface::getValueMultipleOutputHead(String HeadsArray)
{
  int NumOfOutputs = 0;
    //write the get value command
    if(NumOfOutputs<1)
    {
      for (auto& element:HeadsArray)
      {
        if(element=='1')
        {
          NumOfOutputs++;
        }
      }
    }
    double* Values = new double[NumOfOutputs];
    //double Values[NumOfOutputs];
    String valuesHolder="";
    int ValuesCounter=0;
    Serial.println("number of heads");
    Serial.println(NumOfOutputs);
    String command="mesure_value_multipleN";
    String cmd=findCommand(command,commands);
    //cmd:MM,010010000000
    cmd+=String(HeadsArray);
    Serial.println("command sent:");
    Serial.println(cmd);
    serialHandler->println(cmd);
  if(serialHandler->available()>0)
  {
    // Read data from rs232 port
    String Response=serialHandler->readStringUntil('\r');
    #ifdef DEBUG
    // write the data to the other port
    Serial.println("response:");
    Serial.println(Response);
    #endif
    // Response: MM,010010000000,value[,value,value]: 
    Response.replace(cmd,""); //remove default response
    Serial.println(Response);
    // iterate response and extract values

    for (int i=0; i<Response.length();i++)
    {// ,val1,val2,val3,val4,val5
      if(Response[i]==',')
      {        
        valuesHolder=Response.substring(i+1,Response.indexOf(',',i+1));
        Serial.println("value holder got");
        Serial.println(valuesHolder);
        Values[ValuesCounter]=valuesHolder.toDouble();
        ValuesCounter++;
        valuesHolder="";
      }
      if(ValuesCounter==NumOfOutputs) break;
    }
    for (int i =0; i<NumOfOutputs; i++)
    {
      Serial.println("extracted values");
      Serial.println(*(Values + i));
    }
    return Values;
  }
}
// get output all
double* Keyence_rs232_interface::getValueOutputHeadAll()
{
    double* Values = new double[HeadsCount];
    //double Values[NumOfOutputs];
    String valuesHolder="";
    int ValuesCounter=0;
    Serial.println("number of heads");
    Serial.println(HeadsCount);
    //write the get value command
    String command="mesure_value_All";
    String cmd=findCommand(command,commands);
    serialHandler->print(cmd+CR);
    if(serialHandler->available()>0)
  {
    // Read data from rs232 port
    String Response=serialHandler->readStringUntil('\r');
    #ifdef DEBUG
    // write the data to the other port
    Serial.println("response:");
    Serial.println(Response);
    #endif
    // MA,value[,value,value]: 
    Response.replace(cmd,""); //remove default response
    Serial.println(Response);
    // iterate response and extract values
    for (int i=0; i<Response.length();i++)
    {// ,val1,val2,val3,val4,val5
      if(Response[i]==',')
      {        
        valuesHolder=Response.substring(i+1,Response.indexOf(',',i+1));
        Serial.println("value holder got");
        Serial.println(valuesHolder);
        Values[ValuesCounter]=valuesHolder.toDouble();
        ValuesCounter++;
        valuesHolder="";
      }
      if(ValuesCounter==HeadsCount) break;
    }
    for (int i =0; i<HeadsCount; i++)
    {
      Serial.println("extracted values");
      Serial.println(*(Values + i));
    }
    return Values;
  }
}

// set general mode
void Keyence_rs232_interface::setGeneralMode()
{

    //write the get value command
    String command="set_general_mode";
    String cmd=findCommand(command,commands);
    serialHandler->print(cmd+CR);
  delay(100); //this delay is obligatory to clear buffer
  if(serialHandler->available()>0)
  {
    // Read data from rs232 port
    String Response=serialHandler->readStringUntil('\r');
    #ifdef DEBUG
    // write the data to the other port
    Serial.println("response:");
    Serial.println(Response);
    
    #endif
  }
  serialHandler->write("");
  serialHandler->flush();

}
// set communication mode
void Keyence_rs232_interface::setCommunicationMode()
{

    //write the get value command
    String command="set_communication_mode";
    String cmd=findCommand(command,commands);
    serialHandler->print(cmd+CR);
  delay(100); //this delay is obligatory to clear buffer

  if(serialHandler->available()>0)
  {
    // Read data from rs232 port
    String Response=serialHandler->readStringUntil('\r');
    #ifdef DEBUG
    // write the data to the other port
    Serial.println("response:");
    Serial.println(Response);
    #endif
  }
  serialHandler->write("");
  serialHandler->flush();
}

