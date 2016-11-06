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

uint8_t loop_n=0;
uint8_t randNumber=0;
uint8_t r_array[]={80,175,0};



struct color {
  uint8_t r;
  bool r_canup;
  bool r_candown;
  uint8_t g;
  bool g_canup;
  bool g_candown;
  uint8_t b;
  bool b_canup;
  bool b_candown;
};

color led[3];
///////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  led[0].r=10;
  led[0].g=0;
  led[0].b=0;

  led[1].r=0;
  led[1].g=50;
  led[1].b=0;

  led[2].r=0;
  led[2].g=0;
  led[2].b=150;

  Serial.begin(19200);
  printf_begin();
  printf("RGB Night Light v0.2");

  pinMode(LED_BUILTIN, OUTPUT);

  strip.begin(); // This initializes the NeoPixel library.

  digitalWrite(LED_BUILTIN, HIGH);
}


void loop() {

  //RGB iteration
  for(int i=0;i<3;i++){ //3 due to RGB

    switch (i) {
      case 0:
      if (loop_n%40==0) randNumber = random(0, 2);
      //Red
      if (led[0].r<255) led[0].r_canup=true;
      else led[0].r_canup=false;

      if (led[0].r>0) led[0].r_candown=true;
      else led[0].r_candown=false;

      if (led[0].r_canup && randNumber==1) led[0].r++;
      if (led[0].r_candown && randNumber==0) led[0].r--;
      break;

      case 1:
      if (loop_n%40==0) randNumber = random(0, 2);
      //Green
      if (led[0].g<255) led[0].g_canup=true;
      else led[0].g_canup=false;

      if (led[0].g>0) led[0].g_candown=true;
      else led[0].g_candown=false;

      if (led[0].g_canup && randNumber==1) led[0].g++;
      if (led[0].g_candown && randNumber==0) led[0].g--;

      break;

      case 2:
      if (loop_n%40==0) randNumber = random(0, 2);
      //Blue
      if (led[0].b<255) led[0].b_canup=true;
      else led[0].b_canup=false;

      if (led[0].b>0) led[0].b_candown=true;
      else led[0].b_candown=false;

      if (led[0].b_canup && randNumber==1) led[0].b++;
      if (led[0].b_candown && randNumber==0) led[0].b--;

      break;
    }

    strip.setPixelColor(0, strip.Color(led[0].r,led[0].g,led[0].b)); // Moderately bright green color.
    strip.show(); // This sends the updated pixel color to the hardware.

    printf("loop_n %d, randNumber %d \n", loop_n, randNumber);
    printf("led[0] R: %d, G: %d, B: %d \n", led[0].r, led[0].g, led[0].b);

    loop_n++;
  }
  delay(80); // Delay for a period of time (in milliseconds).

}
