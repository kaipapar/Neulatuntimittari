#if 0
#include <Arduino.h>
#include "LittleFS.h"
#include <csvparser.h>
 
void setup() {
  Serial.begin(9600);
  
  if(!LittleFS.begin(true)){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
  
//   File file = LittleFS.open("/text.txt");
  CsvParser *file = CsvParser_new("/id_hours.csv",",",1);
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  Serial.println("File Content:");
  while((file->fileHandler_).available()){
    Serial.write((file->fileHandler_).read());
  }
  CsvParser_destroy(file);
}
 
void loop() {

}
#endif