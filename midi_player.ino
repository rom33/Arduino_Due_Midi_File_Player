////////////////////////////////////////////
//  3.5" TOUCH SCREEN GM Midi file player //
//                                        //
//            rom3 11.2020                //
//                                        //
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
Adafruit_GFX_Button mybutton = Adafruit_GFX_Button();

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

// The files in the tune list should be located on the SD card
// or an error will occur opening the file and the next in the
// list will be opened (skips errors).
char *tuneList[] =
{
  "LOOPDEMO.MID",  // simplest and shortest file
  "ELISE.MID",
  "TWINKLE.MID",
  "GANGNAM.MID",
  "FUGUEGM.MID",
  "POPCORN.MID",
  "AIR.MID",
  "PRDANCER.MID",
  "MINUET.MID",
  "FIRERAIN.MID",
  "MOZART.MID",
  "FERNANDO.MID",
  "SONATAC.MID",
  "SKYFALL.MID",
  "XMAS.MID",
  "GBROWN.MID",
  "PROWLER.MID",
  "IPANEMA.MID",
  "JZBUMBLE.MID",
  "SYMPH9.MID",
  "CHATCHOO.MID",
  "STRIPPER.MID"
};
void setup() {
  Serial.begin(9600);
  tft.begin(tft.readID());
  tft.setRotation(1);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.fillScreen(TFT_BLUE);
  // initialise the music player
  musicPlayer.begin();
  musicPlayer.sciWrite(VS1053_REG_WRAMADDR, VS1053_GPIO_DDR);
  musicPlayer.sciWrite(VS1053_REG_WRAM, 0x0003);
  musicPlayer.GPIO_digitalWrite(0x0000);
  musicPlayer.softReset();
  SD.begin(10, 11, 12, 13);

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(10, 10);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
}

void loop() {
  for (uint8_t i = 0; i < ARRAY_SIZE(tuneList); i++)
  {
    Serial.println(tuneList[i]);
    musicPlayer.startPlayingFile(tuneList[i]);
    while (musicPlayer.playingMusic) {

    }
  }
}
