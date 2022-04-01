#include <ArduinoSTL.h>
#include <map>
/*** layout pins ***/
/*
5V  ------> VCC
GND ------> GND
RX3 ------> RxOut
TX3 ------> TxIn 
 */

#define RS232PORT Serial3
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
String RawCommands[5] = {"R0","MS,OUT01","MS,OUT02","MS,OUT03","MM,1110000000000","MA"};
// map of command Strings to raw commands +CR
std::map<String, String> commands{
{"general_mode",RawCommands[0]+CR},
{"mesure_value_output1",RawCommands[1]+CR},
{"mesure_value_output2",RawCommands[2]+CR},
{"mesure_value_output3",RawCommands[3]+CR},
{"mesure_value_multiple123",RawCommands[4]+CR},
{"mesure_value_All",RawCommands[5]+CR},
};

void setup() {
  // put your setup code here, to run once:
RS232PORT.begin(BAUDRATE);
USBPORT.begin(BAUDRATE);
}

void loop()
{
  //Declarations
  byte cData[100];
  int nBytesAvail = 0;
  int nBytes=0;
  //check for data from the rs232 port
  if((nBytesAvail = RS232PORT.available())>0)
  {
    // Read data from rs232 port
    nBytes=RS232PORT.readBytes(cData,nBytesAvail);

    // write the data to the other port 
    USBPORT.write(cData, nBytes);
  }
  // check for data from the usb port 
  if (((nBytesAvail = USBPORT.available())>0))
  {
    // Read data from rs232 port
    nBytes=USBPORT.readBytes(cData,nBytesAvail);

    // write the data to the usb port 
    USBPORT.write(cData, nBytes);
  }
}