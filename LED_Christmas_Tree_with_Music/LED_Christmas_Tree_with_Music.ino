//Arduino Christmas Tree
//3 x XC4380= 24 LED's arranged as a tree
//uses TMRPCM library to play wav files from root directory in a loop

#define LEDCOUNT 24

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LEDCOUNT, 6, NEO_GRB + NEO_KHZ800);

unsigned long colours[6]={      //only using half intensity so we don't overload USB power
  pixels.Color(127,0,0),        //red
  pixels.Color(0,127,0),        //green
  pixels.Color(0,0,127),        //blue
  pixels.Color(127,127,0),      //yellow
  pixels.Color(127,0,127),      //purple
  pixels.Color(127,63,0)        //orange
};

#include <SD.h>                 // need to include the SD library
#include <TMRpcm.h>             // also need to include this library
#include <SPI.h>
TMRpcm tmrpcm;   // create an object for use in this sketch
File root;
File track;
  
void setup() {
  Serial.begin(115200);
  pixels.begin(); // This initializes the NeoPixel library.
  for(int i=0;i<LEDCOUNT;i++){
    pixels.setPixelColor(i,pixels.Color(5,25,0));   //tree green    
  }
  pixels.setPixelColor(15,pixels.Color(127,127,127));   //white star at top  
  pixels.show();                    // update display
  randomSeed(analogRead(1));        //A4/A5 connected to RTC so won't be random
  tmrpcm.speakerPin = 9;            //must be 9 on Uno
  if(!SD.begin(10)) {               //see if the card can be initialized:
    Serial.println("SD fail");  
  }
  root = SD.open("/");
}

void loop() {                       //each cycle we randomly twinkle a spot on the tree
  int n,c;                          //colour and led to show
  unsigned long oldc;
  n=random(LEDCOUNT);
  c=random(6);                      //6 colours to choose from
  oldc=pixels.getPixelColor(n);     //save the old colour for later
  pixels.setPixelColor(n,colours[c]);
  pixels.show();                    // update display
  delay(300);
  pixels.setPixelColor(n,oldc);
  pixels.show();                    // update display
  delay(200+random(300));           //wait a bit

  if(!tmrpcm.isPlaying()){          //music finished
    track=root.openNextFile();
    if(!track){                     //end of tracks
      root.rewindDirectory();
      track=root.openNextFile();
      }else{
      if(!track.isDirectory()){       //play next
        Serial.println();
        Serial.println(track.name());
        tmrpcm.play(track.name());
      }
      track.close();
    }
  }else{
    Serial.write('.');
  }
}

