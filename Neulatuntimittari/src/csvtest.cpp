#include <Arduino.h>
#include <LittleFS.h>
/* Works! */
#if 0
#define ROWS 50   // adjust for your file
#define COLS 10   // adjust for max columns per row

uint16_t csvData[ROWS][COLS];

void setup() {
  Serial.begin(9600);

  if (!LittleFS.begin()) {
    Serial.println("LittleFS Mount Failed");
    return;
  }
  File file = LittleFS.open("/id_hours.csv", "r", true);
  if (!file) {
    Serial.println("Failed to open file");
    return;
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
    }
    Serial.println();
  }
}

void loop() {
}
#endif