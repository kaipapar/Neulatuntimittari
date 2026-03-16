# Neulatuntimittari
<img src="https://github.com/user-attachments/assets/294f2586-e52d-4fd3-84c9-7718e3598d11" width=500px>

## Description
Neulatuntimittari is a turntable stylus wear indicator. The lifespan of a stylus is commonly listed as 500 hours of usage. Neulatuntimittari aims to answer two main questions, and some subquestions: 
1. How does an end user know how much theoretical life a stylus has left? 
	a. What can 'bad sound' be attributed to in a case by case basis along the lifespan of the stylus? Ie. bad sound at 5 hours vs bad sound at 500 hours might warrant different diagnoses.
2. Among turntable cartridges and styli there are many variables, for example tracking force(s), aligment, stylus profile and material etc. How accurate is '500 hours' across different manufacturing philosophies? 

Other use cases:
- Cleaning -- setting a cleaning interval can be helpful in maintaining optimal performance. Monitoring wear hours helps to keep cleaning routines.
- Listening habits -- Tracking how much music you consume via physical media is tricky without any automation. With Neulatuntimittari you can track how much music you listen to in a speified timeframe (and when, more on that in [Roadmap](#Roadmap)).

Neulatuntimittari is fully automated and once set up once requires human interaction if you want to change the stylus or reset wear hours. It is power efficient, going to Ultra Low Power mode when not in use, accurate, it uses two sensors to make sure a listening event is happening and that it is not just idling. 

The two sensors are an IR sensor which monitors tonearm position and a reed switch which monitors platter movement. If the platter is moving and the tonearm is over the platter, a listening event is happening and wear hours are accumulated. Wear hours and the current stylus with which is being worn are viewed with an e-paper display. All the physical modules can be housed in enclosures that fit the surrounding decor, I carved mine from an oak board. 

---

## Table of Contents
- [File structure](#file-structure)
- [Built with](#built-with)
	- [Hardware](#hardware)
- [Instructions](#instructions)
	- [Installation](#installation)
	- [Enclosures](#enclosures)
	- [Usage](#usage)
- [Documentation](#documentation)
- [Known bugs / issues](#known-bugs--issues)
- [Roadmap](#roadmap)

---
## File structure
Neulatuntimittari/ 
```sh
karri@karri-ThinkPad-P1-Gen-3:~/Neulatuntimittari$ tree 
.
├── blink_test
│   ├── include
│   │   └── README
│   ├── lib
│   │   └── README
│   ├── platformio.ini
│   ├── src
│   │   └── main.cpp
│   └── test
│       └── README
├── documentation
│   ├── attachments
│   │   ├── IMG20250628234006.jpg
│   │   ├── IMG20250629134331.jpg
│   │   ├── IMG_20250630_093625.jpg
│   │   ├── IMG20250718191820.jpg
│   │   ├── IMG20250718194050.jpg
│   │   ├── IMG20250718194119.jpg
│   │   ├── IMG20250718205333.jpg
│   │   ├── IMG20250718205340.jpg
│   │   ├── IMG20250720140437.jpg
│   │   ├── IMG20250728212540.jpg
│   │   ├── IMG20251007161620.jpg
│   │   ├── IMG20251015134359.jpg
│   │   ├── IMG20251024152710.jpg
│   │   ├── IMG20251025171941.jpg
│   │   ├── IMG20251025182849.jpg
│   │   ├── IMG20251027161657.jpg
│   │   ├── IMG20251027165856.jpg
│   │   ├── IMG20251027173031.jpg
│   │   ├── IMG20251027175943.jpg
│   │   ├── IMG20251027180029.jpg
│   │   ├── Pasted image 20250918123249.png
│   │   ├── Pasted image 20250922162426.png
│   │   ├── Pasted image 20250922215123.png
│   │   └── Screenshot_2025-07-04-13-19-35-19_e2d5b3f32b79de1d45acd1fad96fbb0f.jpg
│   ├── Diary.md
│   ├── Issues.md
│   ├── LittleFS.md
│   ├── Neulatuntimittari.md
│   ├── State chart.canvas
│   ├── Testausta.md
│   ├── the_box.md
│   ├── The whole process in pictures.md
│   ├── TODO.md
│   └── UI.md
├── ir_sensor_test
│   ├── include
│   │   └── README
│   ├── lib
│   │   └── README
│   ├── platformio.ini
│   ├── src
│   │   └── main.cpp
│   └── test
│       └── README
├── LICENSE
├── Neulatuntimittari
│   ├── data
│   │   └── id_hours.csv
│   ├── include
│   │   ├── display
│   │   │   ├── GxEPD2_display_selection_added.h
│   │   │   ├── GxEPD2_display_selection.h
│   │   │   ├── GxEPD2_display_selection_new_style.h
│   │   │   ├── GxEPD2_selection_check.h
│   │   │   ├── GxEPD2_wiring_examples.h
│   │   │   └── waveshare.h
│   │   ├── README
│   │   ├── sensor
│   │   │   ├── button.h
│   │   │   ├── dist.h
│   │   │   └── reed.h
│   │   ├── sleep
│   │   │   └── sleep.h
│   │   ├── storage
│   │   │   └── csv.h
│   │   └── time
│   │       └── time.h
│   ├── lib
│   │   ├── DebugSerial
│   │   │   └── debug_serial.h
│   │   └── README
│   ├── platformio.ini
│   ├── src
│   │   ├── display
│   │   │   └── waveshare.cpp
│   │   ├── main.cpp
│   │   ├── sensor
│   │   │   ├── button.cpp
│   │   │   ├── dist.cpp
│   │   │   └── reed.cpp
│   │   ├── sleep
│   │   │   └── sleep.cpp
│   │   ├── storage
│   │   │   └── csv.cpp
│   │   ├── tests
│   │   │   └── sleeptest.cpp
│   │   └── time
│   │       └── time.cpp
│   └── test
│       └── README
└── waveshare_test
    ├── include
    │   ├── GxEPD2_display_selection_added.h
    │   ├── GxEPD2_display_selection.h
    │   ├── GxEPD2_display_selection_new_style.h
    │   ├── GxEPD2_selection_check.h
    │   ├── GxEPD2_wiring_examples.h
    │   └── README
    ├── lib
    │   └── README
    ├── platformio.ini
    ├── src
    │   ├── e-ink_partial_update.ino
    │   ├── GxEPD2_Example.ino
    │   └── main.cpp
    └── test
        └── README

36 directories, 84 files
```
Where Neulatuntimittari/ houses all of the source files, platformio project configuration etc.
directories ending with \_test contain sketches which I used when testing each of the hardware modules individually. They can be used to verify functionality of the ir sensor, esp32 onboard led and the e-paper display before attempting to compile the main project. 

Documentation/ contains my working process documentation in separate MD files. [Whole process in pictures]() tells a broad overview of what has happened in phaze 1 of the project (2025). For example, [Neulatuntimittari.md]() and [Diary.md] are good resources. Unfortunately Neulatuntimittari.md is in finnish.

---
## Built with
Build configuration and dependencies: 
```sh
# from `Neulatuntimittari/platformio.ini`
[env:upesy_wroom]
platform = espressif32
board = upesy_wroom
framework = arduino
lib_deps = 
	zinggjm/GxEPD2@^1.6.4
	olikraus/U8g2_for_Adafruit_GFX@^1.8.0
monitor_speed = 9600
board_build.filesystem = littlefs
build_flags = -Iinclude/* ;-DDEBUG
platform_packages = platformio/tool-esptoolpy@^2.40900.250804

# from platformio
Resolving upesy_wroom dependencies...
Platform espressif32 @ 6.12.0 (required: espressif32)
├── framework-arduinoespressif32 @ 3.20017.241212+sha.dcc1105b (required: platformio/framework-arduinoespressif32 @ ~3.20017.0)
├── tool-esptoolpy @ 2.40900.250804 (required: platformio/tool-esptoolpy @ ^2.40900.250804)
├── tool-mkfatfs @ 2.0.1 (required: platformio/tool-mkfatfs @ ~2.0.0)
├── tool-mklittlefs @ 1.203.210628 (required: platformio/tool-mklittlefs @ ~1.203.0)
├── tool-mkspiffs @ 2.230.0 (required: platformio/tool-mkspiffs @ ~2.230.0)
├── tool-openocd-esp32 @ 2.1100.20220706 (required: platformio/tool-openocd-esp32 @ ~2.1100.0)
├── toolchain-riscv32-esp @ 8.4.0+2021r2-patch5 (required: espressif/toolchain-riscv32-esp @ 8.4.0+2021r2-patch5)
└── toolchain-xtensa-esp32 @ 8.4.0+2021r2-patch5 (required: espressif/toolchain-xtensa-esp32 @ 8.4.0+2021r2-patch5)

Libraries
├── GxEPD2 @ 1.6.5 (required: zinggjm/GxEPD2 @ ^1.6.4)
│ └── Adafruit GFX Library @ 1.12.1 (required: Adafruit GFX Library)
│ │ └── Adafruit BusIO @ 1.17.2 (required: Adafruit BusIO)
└── U8g2_for_Adafruit_GFX @ 1.8.0 (required: olikraus/U8g2_for_Adafruit_GFX @ ^1.8.0)
```
The only library dependencies are related to the display. The rest of the libraries are espressif32 standard libraries, like stdint.h, esp_sleep.h.

### Hardware
Here's what hardware I have used to build mine, and links to where I bought them:
<img src="https://github.com/user-attachments/assets/161c267a-febf-483f-9d15-1ab1b63bb5a3" width=500px>

I bought everything from tme.eu.

Microcontroller: https://www.tme.eu/fi/en/details/df-dfr0478/programmable-controllers/dfrobot/dfr0478/
- Esp32, cheap, with wi-fi
Cables: https://www.tme.eu/fi/en/details/cab_ag/development-kits-accessories/kamami/cab-f-f-10-25-g/
- Only green ones, because they look nice
Reed switch: https://www.tme.eu/fi/en/details/ksk1a87-1015/reed-sensors/meder/ksk-1a87-1015/ 
- It doesn't really matter what kind you choose. Pick one that fits the case you've designed. NB. you need a magnet attached to the platter for the reed switch to work. I used a small neodinium magnet from the hardware store.
IR sensor: https://www.tme.eu/fi/en/details/pololu-2579/distance-sensors/pololu/38-khz-ir-proximity-sensor-low-brightnes/
- This one is good, because it can detect from a very short distance, is cheap and small form factor.
E-paper display: https://www.tme.eu/fi/en/details/wsh-18321/e-paper/waveshare/18321/
- I built mine with waveshare, and this one. I wanted a smaller display, but TME were out of stock. This one is fine, but the smaller ones might be sufficient (changing the display requires rewriting UI specific code and reconfiguring GxEPD2 files from `Neulatuntimittari/include/display/`. (Warning: the config was a tough cookie.))
Push button: https://www.tme.eu/fi/en/details/1-1825910-4/microswitches-tact/te-connectivity/
- Any one should be fine. I chose this one with a tall hat, so it can be mounted from the inside of the enclosure.

You also need a suitable usb-cable to connect the esp32 target to your development machine.

---
## Instructions
### Installation
I used platformio with visual studio code. 
```sh
karri@karri-ThinkPad-P1-Gen-3:~/Neulatuntimittari/Neulatuntimittari$ pio --version
PlatformIO Core, version 6.1.19
```

1. clone repo to your machine
2. open Neulatuntimittari/Neulatuntimittari with VS code
3. open platformio extension
4. open current folder as project (or something like this, maybe it will find the platformio.ini file and open the project automatically)
5. connect esp32 to your machine via usb (platformio should automatically select the correct COM port and baud rate)
6. build filesystem
7. upload filesystem
8. build
9. upload
10. voila! everything should work.

If everything doesn't work here are some steps you can take:
- check the platformio terminal for failed or succeeded build and upload processes etc.
- check wiring and then check it again
- de-comment the -DDEBUG flag from platformio.ini (this enables prints to serial monitor)
- go back and try to build the test sketches for all of the hardware modules

### Enclosures
I built mine from an oak board, since that is what we had lying around. I did it so that the push button, display and reed switch are in one box, the IR sensor in its own box and I adhered the esp32 to the back of my turntable with dual sided tape, since that was most convenient. 

Considerations:
1. The internal area of the IR sensor enclosure needs to reflect as little light as possible. The IR sensor I have chosen blasts IR in a 180 degree field, if it is not controlled with a funnel type apparatus. The receiver also collects emitted beams from a broad field. In our usecase we only care about what happens directly above the sensor a few centimeters away. The funnel needs to be tight to the sides of the sensor board, as not to introduce cross contamination from emitter to receiver, which would cause sporadic output. The position of the sensor on the turntable needs to be so it is under the tonearm. You would need to tune the position to be such that the output changes when the tonearm is moved from its resting position over the platter. The sensor I have has a red led, which shows the status of the sensor. I dyed the interior of the casing with black ink, like so:

<img src="https://github.com/user-attachments/assets/639e3dfb-49b7-4f15-a889-31ec1428b36d" width=500px>

2. Since the reed switch engages when a magnetic field is nearby, it doesn't need visual connection to the magnet, meaning that you don't have to cut a hole into the enclosure. The switch just has to witness a 'strong enough' magnetic field. Again, the distance between magnet and reed switch might have to be tuned by end user.

### Usage
Once the reed switch and IR sensor are tuned to positions where they work as intended (status of the reed switch changes when the magnet passes by and status of the IR sensor changes when the tonearm is moved to the platter) it should just work.

When the system is not in use the display should read Sleep, then when the platter is spinning the reed switch sends a hardware interrupt signal to wake up the esp32, display reads Deactive. Then once the system is Deactive and the tonearm is moved to the platter, the display should read Active. And it stays active until the platter stops spinning or the tonearm is resting. The tonearm position does not wake up the esp32.

The push button has two functionalities: short press, this changes the stylus. Currently there are 10 styli, from 0-9. Each adds up time to a different field, meaning that you have the hours of 10 possible styli in memory. The COLS macro in csv.h defines the number of styli you can define. Long press, it resets the current stylus hours to 0. The macro SLOW_THRHLD in button.h contains the lenght of time needed so a long press is registered, right now it is 5000 ms -> 5 seconds. A SUPER_SLOW macro is also defined to be 8000 ms, which cancels a button press altogether, acting as a fail safe for accidental button presses. 
## Documentation
A brief process documentation can be found from my blog: [kaipapar.github.io](https://kaipapar.github.io/software/neulatuntimittari/whole-process-in-pictures/)

The same file and other process related files are in this repo at documentation/

I've also tried to write readable code with ample commenting, but this isn't always sufficient. If you have problems, contact me.

---
## Known bugs / issues
1. Sometimes the whole system restarts in deactive mode, or at least the display restarts. 
	- I've not yet found a culprit.
2. Upon startup, the display flashes black and white multiple times before displaying the correct information
	- Is this a feature of the waveshare displays (or all e-paper displays)? Or an issue with my code?
3. The system always tries to wake up when the magnet stops where the reed switch activates.
	- This is a feature of how the wake up call works. As far as I know, the wakeup signal can only be defined as up or down, meaning that a rising or falling signal cannot be implemented. NOTE: I've defined the reed interrupt as CHANGE. Does the problem still stand? need to test.

---
## Roadmap
