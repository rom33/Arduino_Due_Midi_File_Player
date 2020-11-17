# Arduino_Due_Midi_File_Player
A simple Media file player via vs1053 (http://www.vlsi.fi/en/products/vs1053.html)

Another project using the vs1053 and the 3, 5' tft display and the vs1053. At the moment only the sd-card and basic touch functions. General MIDI format 0, ogg, wav and wma files can played.

Put your media file in the root directory of your sd-card (MIDI format 0, ogg, wav, wma).
Touch the screen for next title.

Needed libraries:

SD librariry from https://github.com/adafruit/SD.

Adafruit_GFX and MCUFRIEND_kbv can install from the library manager.

Decompress the zip file to your home directory of you sd-card.

Wiring

for the vs1053:
```sh
    XCS -> 46
    XDCS -> 48
    DREQ -> 50
    XRST -> 52
    MOSI -> A.26
    MISO -> A.25
    SCK -> A.27
    5V -> 5V
```
