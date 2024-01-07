// Play back sounds from multiple SD cards
// Tested on Teensy 4.1, changes may be needed for 3.x

#include <SD.h>
#include <Bounce.h>
#include <Audio.h>
#include "play_wav_buffered.h"

#define SDCARD_CS_PIN BUILTIN_SDCARD // audio adaptor

// #define sd1 SD // can do this for one card
SDClass sd1;
File frec;

// GUItool: begin automatically generated code
AudioOutputTDM          tdm_out;
AudioControlCS42448     codec;

AudioPlayWAVstereo       playRaw1;       //xy=302,157

AudioConnection          patchCord0(playRaw1, 0, tdm_out, 0);
AudioConnection          patchCord1(playRaw1, 1, tdm_out, 2);
AudioConnection          patchCord2(playRaw1, 2, tdm_out, 4);
AudioConnection          patchCord3(playRaw1, 3, tdm_out, 6);
AudioConnection          patchCord4(playRaw1, 4, tdm_out, 8);
AudioConnection          patchCord5(playRaw1, 5, tdm_out, 10);
AudioConnection          patchCord6(playRaw1, 6, tdm_out, 12);
AudioConnection          patchCord7(playRaw1, 7, tdm_out, 14);
// GUItool: end automatically generated code

// Use these with the Teensy 3.5 & 3.6 & 4.1 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

//==================================================================
void setup() {

  // Configure the pushbutton pins
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);

  // Audio connections require memory
  AudioMemory(1000);
  codec.enable();
  codec.volume(1);

  while (!Serial)
    ;
  Serial.println("Started!");

  playRaw1.createBuffer(8192,AudioBuffer::inHeap);
  playRaw1.setLooping(true);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

      Serial.print("Play 1 - Buffered - Looping = ");
    Serial.println(playRaw1.isLooping());
    // playRaw1.play("sine220.wav"); // if sd1 is #defined as SD, this works
    playRaw1.play("VOX8.WAV", SD);
    delay(1000);

}


//==================================================================
void loop() {

  // if (!playRaw1.isPlaying()) {
  //   Serial.print("Play 1 - Buffered - Looping = ");
  //   Serial.println(playRaw1.isLooping());
  //   // playRaw1.play("sine220.wav"); // if sd1 is #defined as SD, this works
  //   playRaw1.play("VOX8.WAV", SD);
  //   delay(1000);
  // }else 
  
  if(playRaw1.hasLooped()){
    Serial.println("Looped Play 1!");
    delay(1000);
  }else{
    Serial.println(playRaw1.positionMillis());
    Serial.println(playRaw1.isPlaying());
    delay(1000);
  }

}
