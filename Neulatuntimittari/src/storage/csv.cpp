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
uint8_t get_hours_csv(uint64_t array[ROWS][COLS]) {
    File file = LittleFS.open("/id_hours.csv", "r");
    if (!file) {
        Serial.println("Failed to open file for reading");
        return 1;
    }

    int row = 0;
    while (file.available() && row < ROWS) {
        String line = file.readStringUntil('\n');
        line.trim();

        int col = 0;
        int start = 0;

        while (col < COLS) {
            int idx = line.indexOf(',', start);
            String token;
            if (idx == -1) {
                token = line.substring(start);
            } else {
                token = line.substring(start, idx);
                start = idx + 1;
            }

            if (token.length() > 0) {
                array[row][col] = strtoull(token.c_str(), NULL, 10);
            } else {
                array[row][col] = 0;
            }

            col++;
            if (idx == -1) break;
        }
        row++;
    }
    file.close();
    // Debug print
    Serial.println("Debug...");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < COLS; j++) {
            Serial.print(array[i][j]);
            Serial.print(" ");
        }
        Serial.println();
    }
    return 0;
}

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
    file.flush();
    file.close();
    return 0;
}

/* Log time spent in active mode
  Check correct needle id 
  > add difference of end and start to corresponding field 
  > send array to be saved as csv

  time : time spent in active mode since last boot
  field : single field of array that is to be updated
*/
uint8_t log_hours(uint64_t time, uint64_t* field) {
    *field += time;
    return 0;
}

uint8_t print_table(uint64_t array[ROWS][COLS]){
    //Serial.println("Printing table: ");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            //Serial.print(array[i][j]);
            //Serial.print(" ");
        }
    //Serial.println();
    }
    return 0;   
}