/* 
LittleFS + CSV fileIO functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#include "storage/csv.h"
#include <Arduino.h>
//Filesystem
#include "LittleFS.h"


int get_hours(){
  // LittleFS
  // Read CSV to 2d array 
  File file = LittleFS.open("/id_hours.csv");
  if(!file){
    Serial.println("Failed to open file for reading");
    return 0;
  }
  Serial.println("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
  return 0;
} 
// Write updated CSV
int save_hours(){
  return 0;
}
/* Log time spent in active mode
  Check correct needle id 
  > add difference of end and start to corresponding field 
  > send array to be saved as csv
*/
int logging(int64_t time) {
  
  return 0;
}

