// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "printf.h"

extern HardwareSerial Serial;

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      3

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

uint8_t r_array[]={80,175,0};
///////////////////////////////////////////////////////////////


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;

  if(WheelPos < 85) {

    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;

    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;

  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

//uint32_t RandomDimmer(void){


  //return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  uint32_t randNumber;
  randNumber = random(1, 5);
  Serial.print(F("\n rand:"));
  Serial.print(randNumber);

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {

      strip.setPixelColor(i, Wheel((i+j)));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint16_t wait) {
  uint16_t i, j;
  uint32_t color;


  for(j=0; j<256; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      uint8_t randNumber;
      randNumber = random(0, 2);
      Serial.print(F("\n rand:"));
      Serial.print(randNumber);
      color = Wheel(((i * 256 / strip.numPixels()) + j+r_array[randNumber]) & 255);
      strip.setPixelColor(i, color);
      //Serial.print(F("\n color:"));
      //Serial.print(color);
    }
    strip.show();
    delay(wait);
  }
}


///////////////////////////////////////////////////////////////////////




void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  Serial.begin(19200);
  Serial.println(F("RGB Night Light v0.2"));

  pinMode(LED_BUILTIN, OUTPUT);

  strip.begin(); // This initializes the NeoPixel library.

  digitalWrite(LED_BUILTIN, HIGH);
}


void loop() {

  //rainbow(200);
  rainbowCycle(100);
  //rainbow(100);

  //theaterChaseRainbow(100);
}
