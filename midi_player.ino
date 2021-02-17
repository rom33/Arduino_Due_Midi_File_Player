////////////////////////////////////////////
//  3.5" TOUCH SCREEN GM Midi file player //
//                                        //
//            rom3 11.2020                //
//                                        //
////////////////////////////////////////////
#include "Arduino.h"
#include "TouchScreen.h"

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(52, 46, 48, 50, 10);

// *** display
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
Adafruit_GFX_Button button[2] = Adafruit_GFX_Button();

// *** touch
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin
int TS_MINX = 890;
int TS_MAXX = 90;
int TS_MINY = 890;
int TS_MAXY = 214;
#define MINPRESSURE 25
TouchScreen_kbv myTouch = TouchScreen_kbv(XP, YP, XM, YM, 300);
TSPoint_kbv tp;
#define GetTouchPoints tp=myTouch.getPoint();xx=map(tp.x,TS_MINX,TS_MAXX,320,0);yy=map(tp.y,TS_MINY,TS_MAXY,240,0);

unsigned short xx, yy;
String filename;
String names[500] = {};
int count;
File root, entry;
int i;

void setup() {
  Serial.begin(9600);
  tft.begin(tft.readID());
  tft.setRotation(1);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.fillScreen(TFT_BLUE);
  button[0].initButton(&tft, 180, 200, 100, 40, TFT_WHITE, TFT_CYAN, TFT_BLACK, "prev", 2);
  button[1].initButton(&tft, 300, 200, 100, 40, TFT_WHITE, TFT_CYAN, TFT_BLACK, "next", 2);
  button[0].drawButton(false);
  button[1].drawButton(false);
  // initialise the music player
  musicPlayer.begin();
  musicPlayer.sciWrite(VS1053_REG_WRAMADDR, VS1053_GPIO_DDR);
  musicPlayer.sciWrite(VS1053_REG_WRAM, 0x0003);
  musicPlayer.GPIO_digitalWrite(0x0000);
  musicPlayer.softReset();
  SD.begin(10, 11, 12, 13);
  getFiles();
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(10, 10);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
}

void loop() {
  //  for (uint8_t i = 0; i < ARRAY_SIZE(names); i++)
  Serial.println(names[i]);
  Serial.println(i);
  musicPlayer.startPlayingFile(names[i].c_str());
  while (musicPlayer.playingMusic) {
    GetTouchPoints;
    if (tp.z > MINPRESSURE) {
      GetTouchPoints;
      if (button[0].contains(xx, yy)); {
        Serial.println("prev");
        i -= 1;
        if (i < 0) i = count - 1;
        musicPlayer.stopPlaying();
        delay(500);
        break;
      }
      if (button[1].contains(xx, yy)); {
        Serial.println("next");
        i += 1;
        if (i >= count) i = 0;
        musicPlayer.stopPlaying();
        delay(500);
        break;
      }
      delay(200);
    }
  }
}

void getFiles() {
  Serial.println("Opened directory!");
  Serial.println("Playable Files marked with *: ");
  root = SD.open("/");

  count = 0;
  while (true) {
    File entry =  root.openNextFile();
    if (! entry) {
      break;
    }
    filename = String(entry.name());
    filename.toLowerCase();

    if (filename.endsWith(".ogg") ||
        filename.endsWith(".mp3") ||
        filename.endsWith(".wav") ||
        filename.endsWith(".wma") ||
        filename.endsWith(".mid"))
    {
      names[count] = String(entry.name());
      count += 1;
      Serial.print(String(entry.name()));
      Serial.print(count);
      Serial.println("*");
      if (count > 500) {
        break;
      }
    }
    else {
      Serial.println(String(entry.name()));
    }
    entry.close();
  }

}
