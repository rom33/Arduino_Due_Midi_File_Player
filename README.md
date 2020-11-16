# Arduino_Due_Midi_File_Player
A simple Midi file player

Another project using the vs1053 and the 3, 5' tft display. At the moment only the sd-card is used. General MIDI format 0 files can played.

Needed libraries:

SD librariry from https://github.com/adafruit/SD.

Adafruit_GFX and MCUFRIEND_kbv can install from the library manager.

Decompress the zip file to your home directory of you sd-card.

Wiring

for the vs1053:

    XCS -> 46
    XDCS -> 48
    DREQ -> 50
    XRST -> 52
    MOSI -> A.26
    MISO -> A.25
    SCK -> A.27
    5V -> 5V
