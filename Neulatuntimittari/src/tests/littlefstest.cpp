#if 0
#include <debug_serial.h>
#include "LittleFS.h"
 
void setup() {
  Serial.begin(9600);
  
  if(!LittleFS.begin(true)){
    //DebugPrintln("An Error has occurred while mounting LittleFS");
    return;
  }
  
  File file = LittleFS.open("/id_hours.csv");
  if(!file){
    //DebugPrintln("Failed to open file for reading");
    return;
  }
  
  //DebugPrintln("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}
 
void loop() {

}
#endif