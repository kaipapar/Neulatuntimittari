[[25.08.07]]
Video joka vertailee tiedostojärjestelmiä:
[# #2 – ESP32 File Systems Explained: LittleFS vs SPIFFS vs FatFS + Arduino 2 IDE LittleFS Setup Guide](https://www.youtube.com/watch?v=Qw5mQus-WwA&ab_channel=Tony%27sLab)

Artikkeli LittleFS käytöstä PlatformIOn kanssa. Käytin tätä!
[# ESP32 with VS Code and PlatformIO: Upload Files to LittleFS Filesystem](https://randomnerdtutorials.com/esp32-vs-code-platformio-littlefs/)


## CSV 
[[25.08.20]]
koitin eka käyttää [CsvParser.h](https://sourceforge.net/projects/cccsvparser/files/), koska olin käyttänyt sitä aiemminkin Capstone-kurssilla opinnäytetöiden asiasanojen käsittelyyn (https://github.com/kaipapar/capstone_C). Mutta koska LittleFS ei käytä stdio.h tietorakennetta `FILE *` vaan FS.h luokkaa `File`, ei CsvParser.h:n käyttö ollutkaan ihan plug and play. Tämä ratkaistiin tekemällä oma pieni Csv parser chatgpt:n kanssa, joka toimii!