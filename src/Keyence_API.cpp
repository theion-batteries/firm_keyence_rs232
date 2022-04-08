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
// print number of heads
void Keyence_base::printNumHeads() const
{
    Serial.println("number of heads counted:");
    Serial.println(HeadsCount);
}
// list heads availble
void Keyence_base::listUsedHeads() const
{
      // For loop using iterators
    for (std::vector<int>::iterator it = NumUsedHeads.begin(); it != NumUsedHeads.end(); it++)
    {
    Serial.println("found saved head number:");
    Serial.println(*it );
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
  if(serialHandler->available()>0)
  {
    //write the get value command
    String command="mesure_value_outputN";
    String cmd=findCommand(command,commands);
    if (output_head_Nr<9){String(output_head_Nr)="0"+String(output_head_Nr);}
    cmd+=String(output_head_Nr);
    serialHandler->print(cmd+CR);
    // Read data from rs232 port
    String Response=serialHandler->readString();
    #ifdef DEBUG
    // write the data to the other port
    Serial.println("response:");
    Serial.println(Response);
    Serial.println("response to double");
    //MS,OUT01,value CR: remove M->,: 9
    Response.remove(0,9); //remove default response
    Response.toDouble(); // type cast to doule
    Serial.println(Response);
    #endif
    return Response.toDouble();
  }
}
//get output multiple heads in this format: "0-12" example: head 1,2 and 3 will be 111000000000
double* Keyence_rs232_interface::getValueMultipleOutputHead(String HeadsArray)
{
  if(serialHandler->available()>0)
  {
    //write the get value command
    String command="mesure_value_multipleN";
    String cmd=findCommand(command,commands);
    //cmd:MM,010010000000
    cmd+=String(HeadsArray);
    serialHandler->print(cmd);
    // Read data from rs232 port
    String Response=serialHandler->readString();
    #ifdef DEBUG
    // write the data to the other port
    Serial.println("response:");
    Serial.println(Response);
    #endif
    // Response: MM,010010000000,value[,value,value]: 
    Response.remove(0,21); //remove default response
    // iterate string of values: take , as delimiter for value
    // extract value and add them to array
    double Values[12];
    char* valuesHolder="";
    int ValuesCounter=0;
    for (int i=0; i<Response.length(); i++)
    {
  // we check if the this char is digit, +, -, . or ,
  // example: [,+0.0123,-1.258,+8.235]
    if (isdigit(Response[i])) // if is char digit
      {
        valuesHolder+=Response[i]; //add char to valuesHolder
      }
    if (Response[i]=='+')
      {
        //ignore + sign
      }
    if (Response[i]=='-')
      {
        valuesHolder+=Response[i];
      }
    if (Response[i]=='.')
      {
        valuesHolder+=Response[i];
      }
    if (Response[i]==',')
      {
        if(i>2)
        {
          ++ValuesCounter; 
            Values[ValuesCounter]=String(valuesHolder).toDouble();
        }
      }
    }
    Serial.println(*Values);
    return Values;
  }
}
// get output all
double* Keyence_rs232_interface::getValueOutputHeadAll()
{
  if(serialHandler->available()>0)
  {
    //write the get value command
    String command="mesure_value_All";
    String cmd=findCommand(command,commands);
    serialHandler->print(cmd+CR);
    // Read data from rs232 port
    String Response=serialHandler->readString();
    #ifdef DEBUG
    // write the data to the other port
    Serial.println("response:");
    Serial.println(Response);
    #endif
    // MA,value[,value,value]: remove M->e:8
    Response.remove(0,8); //remove default response
    // iterate string of values: take , as delimiter for value
    // extract value and add them to array
    double Values[12];
    char* valuesHolder="";
    int ValuesCounter=0;
    for (int i=0; i<Response.length(); i++)
    {
  // we check if the this char is digit, +, -, . or ,
  // example: [,+0.0123,-1.258,+8.235]
    if (isdigit(Response[i])) // if is char digit
      {
        valuesHolder+=Response[i]; //add char to valuesHolder
      }
    if (Response[i]=='+')
      {
        //ignore + sign
      }
    if (Response[i]=='-')
      {
        valuesHolder+=Response[i];
      }
    if (Response[i]=='.')
      {
        valuesHolder+=Response[i];
      }
    if (Response[i]==',')
      {
        if(i>2)
        {
          ++ValuesCounter; 
            Values[ValuesCounter]=String(valuesHolder).toDouble();
        }
      }
    }
    Serial.println(*Values);
    return Values;
  }
}

// set general mode
void Keyence_rs232_interface::setGeneralMode()
{
  if(serialHandler->available()>0)
  {
    //write the get value command
    String command="set_general_mode";
    String cmd=findCommand(command,commands);
    serialHandler->print(cmd+CR);
    // Read data from rs232 port
    String Response=serialHandler->readString();
    #ifdef DEBUG
    // write the data to the other port
    Serial.println("response:");
    Serial.println(Response);
    #endif
  }
}
// set communication mode
void Keyence_rs232_interface::setCommunicationMode()
{
  if(serialHandler->available()>0)
  {
    //write the get value command
    String command="set_communication_mode";
    String cmd=findCommand(command,commands);
    serialHandler->print(cmd+CR);
    // Read data from rs232 port
    String Response=serialHandler->readString();
    #ifdef DEBUG
    // write the data to the other port
    Serial.println("response:");
    Serial.println(Response);
    #endif
  }
}