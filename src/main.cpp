#include <ArduinoSTL.h>
#include <map>
#include <string>

/*** layout pins ***/
/*
5V  ------> VCC
GND ------> GND
RX3 ------> RxOut
TX3 ------> TxIn 
 */
#define UNO
//define MEGA
#ifdef MEGA
#define RS232PORT Serial1
#endif
#define USBPORT Serial
#define BAUDRATE 115200
#define CR "\r" //assume carriage return is \r otherwise + \n, \0
#define LF "\n" //assume next line or Line Feed used
/***** rs232 device commands ****/
/*
* the commands must be sent to the device using CR as delimeter, 
* and the response must be received also with CR.
* the controller (arduino) must send one command and wait for
* the response to send next one.
* General Mode: During measurement The measurement control commands are accepted.
Commands such as writing/reading setting values are not accepted
* Communication Mode: • When the command "Q" "0" "CR" is received, the mode changes to
the communication mode, and the setting values are written/read.
• The measurement stops during the communication mode.
* command | description | Mode | response | ERROR
--------------------------------------------------------------------------
* Q0 CR | Changing to the communication mode  | communication |  same as command  | Err-51
--------------------------------------------------------------------------
* R0 CR | Changing to the general mode | general | same as command  | ERROR
--------------------------------------------------------------------------
* MS,OUT01 CR | Measured value output (single) 01-12 | General | MS,OUT01,value CR | ERROR
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* MM,010010000000 CR | Measured value output (multiple) 01-12 ex here out2 and out5| General | MM,010010000000,value[,value,value] CR | ERROR
--------------------------------------------------------------------------
* MA CR | Measured value output (all) 01-12| General | MA,value[,value,value] CR | ERROR
--------------------------------------------------------------------------
* Timing Diagrams
* t: time between receiving command and responding: process time
* Mesrument/control PW: 100ms + number of heads x 100ms : if one head: 200ms if 3 heads 100ms +3*100=400ms
* Error Code
• 50: Command error
• 51: Status error
• 60: Command length error
• 61: Parameter count error
• 62: Parameter range error
• 88: Timeout error
• 99: Other error
*/
// Array of Raw Commands
String RawCommands[6] = {"R0","MS,OUT01","MS,OUT02","MS,OUT03","MM,1110000000000","MA"};
// map of command Strings to raw commands +CR
std::map<String, String> commands{
{"set_general_mode\n",RawCommands[0]+CR},
{"mesure_value_output1\n",RawCommands[1]+CR},
{"mesure_value_output2\n",RawCommands[2]+CR},
{"mesure_value_output3\n",RawCommands[3]+CR},
{"mesure_value_multiple123\n",RawCommands[4]+CR},
{"mesure_value_All\n",RawCommands[5]+CR},
};
void findCommand(String& command, std::map<String, String>& CommandMap)
{
     for (auto it = CommandMap.begin(); it != CommandMap.end(); ++it) 
      {
        if((*it).first==command)
        {
          USBPORT.println("found command String: ");
          USBPORT.print(command);
          USBPORT.println("command value: ");
          String value=(*it).second;
          USBPORT.println(value);
        }
      }	
}
void setup() {
  // put your setup code here, to run once:
#ifdef MEGA
RS232PORT.begin(BAUDRATE);
#endif
USBPORT.begin(BAUDRATE);
}

void loop()
{
  //Declarations
  byte cData[100];
  int nBytesAvail = 0;
  String incomingBytes;
  //check for data from the rs232 port
#ifdef MEGA
  if((nBytesAvail = RS232PORT.available())>0)
  {
    // Read data from rs232 port
    nBytes=RS232PORT.readBytes(cData,nBytesAvail);

    // write the data to the other port 
    USBPORT.write(cData, nBytes);
  }
#endif
  // check for data from the usb port 
  if (((nBytesAvail = USBPORT.available())>0))
  {
    // Read data from usb port
    incomingBytes=USBPORT.readString();
    USBPORT.println("data received");
   findCommand(incomingBytes,commands);
  }
}

