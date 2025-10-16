#if 0
#include <debug_serial.h>
#include "LittleFS.h"
#include <csvparser.h>
 
void setup() {
  Serial.begin(9600);
  
  if(!LittleFS.begin(true)){
    //DebugPrintln("An Error has occurred while mounting LittleFS");
    return;
  }
  
//   File file = LittleFS.open("/text.txt");
  CsvParser *file = CsvParser_new("/id_hours.csv",",",1);
  if(!file){
    //DebugPrintln("Failed to open file for reading");
    return;
  }
  //DebugPrintln("File Content:");
  while((file->fileHandler_).available()){
    Serial.write((file->fileHandler_).read());
  }
  CsvParser_destroy(file);
}
 
void loop() {

}
#endif