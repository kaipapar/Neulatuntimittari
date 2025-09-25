/* 
LittleFS + CSV fileIO functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#include "storage/csv.h"
#include <Arduino.h>
//Filesystem
#include "LittleFS.h"
uint64_t csvData[ROWS][COLS];

int setup_littlefs(){
    if (!LittleFS.begin()) {
        Serial.println("LittleFS Mount Failed");
        return 1;
    }
    return 0;
}
/* Read CSV to a 2d array */
uint8_t get_hours_csv(uint64_t array[ROWS][COLS]){
    File file = LittleFS.open("/id_hours.csv", "r", true);
    if(!file){
        Serial.println("Failed to open file for reading");
        return 1;
    }

    int row = 0;
    Serial.println("Contents:...");
    while (file.available() && row < ROWS) {
        String line = file.readStringUntil('\n');  // read one line
        line.trim();  // remove \r or spaces

        int col = 0;
        int start = 0;

        while (col < COLS) {
            int idx = line.indexOf(',', start);
            String token;
            if (idx == -1) {
                token = line.substring(start);  // last number
            } else {
                token = line.substring(start, idx);
                start = idx + 1;
            }
            if (token.length() > 0) {
                csvData[row][col] = (uint16_t) token.toInt();
            } else {
                csvData[row][col] = 0;
            }

            col++;
            if (idx == -1) break;  // no more commas
        }
        row++;
    }
    file.close();

    // Debug print
    Serial.println("Debug...");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < COLS; j++) {
            Serial.print(csvData[i][j]);
            Serial.print(" ");
            array[i][j] = csvData[i][j];
        }
    Serial.println();
    }
    return 0;
} 
// Write updated CSV
/* uint8_t save_hours_csv(uint64_t array[ROWS][COLS]){
    File file = LittleFS.open("/id_hours.csv", "w", true);
    if(!file){
        Serial.println("Failed to open file for reading");
        return 1;
    }
    int row = 0;
    while (file.available() && row < ROWS){
        int col = 0;
        while (col < COLS){
            file.print(array[row][col]);
            if (col == (COLS-1))
                file.print(",");
            col++;
        }
        row++;
        file.println();
    }
  
    return 0;
} */
uint8_t save_hours_csv(uint64_t array[ROWS][COLS]){
    File file = LittleFS.open("/id_hours.csv", "w");
    if(!file){
        Serial.println("Failed to open file for writing");
        return 1;
    }

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            file.print(array[row][col]);
            if (col < COLS - 1) file.print(",");
        }
        file.println();
    }

    file.close();
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

uint8_t print_table(uint64_t array[ROWS][COLS]){
    Serial.println("Printing table: ");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            Serial.print(array[i][j]);
            Serial.print(" ");
        }
    Serial.println();
    }
    return 0;   
}