// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

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

///////////////////////////////////////////////////////////////


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 90) {
    return strip.Color(250 - WheelPos * 3, 5, WheelPos * 3);
  }
  if(WheelPos < 165) {
    WheelPos -= 90;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 165;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

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

  for(j=0; j<256; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i * 256 / strip.numPixels()) + j));
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

 pinMode(LED_BUILTIN, OUTPUT);

  strip.begin(); // This initializes the NeoPixel library.

  digitalWrite(LED_BUILTIN, HIGH);
}


// // the loop function runs over and over again forever
// void loop() {
//   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//   delay(1000);                       // wait for a second
//   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//   delay(1000);                       // wait for a second
// }

// void loop() {
//
//   // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
//
//   for(int i=0;i<NUMPIXELS;i++){
//
//     // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//     pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.
//
//     pixels.show(); // This sends the updated pixel color to the hardware.
//
//     delay(delayval); // Delay for a period of time (in milliseconds).
//     digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//   }
// }

void loop() {

  //rainbow(200);
  rainbowCycle(100);
  //theaterChaseRainbow(100);
}
