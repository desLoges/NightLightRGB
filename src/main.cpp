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

uint16_t loop_n=0;
uint16_t randNumber=0;
uint8_t r_array[3];
uint8_t segment_i=0;
uint8_t change_intensity=110;


struct color {
  uint8_t r;
  bool r_canup;
  bool r_candown;
  uint8_t r_rand;
  uint8_t g;
  bool g_canup;
  bool g_candown;
  uint8_t g_rand;
  uint8_t b;
  bool b_canup;
  bool b_candown;
  uint8_t b_rand;
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

  Serial.begin(19200);
  printf_begin();
  printf("RGB Night Light v0.2");

  pinMode(LED_BUILTIN, OUTPUT);

  strip.begin(); // This initializes the NeoPixel library.

  digitalWrite(LED_BUILTIN, HIGH);

  randomSeed(analogRead(0));

  led[0].r=random(0, 30);
  led[0].g=random(100, 256);
  led[0].b=random(0, 100);

  led[1].r=0; //random(0, 256);
  led[1].g=random(0, 50);
  led[1].b=random(0, 256);

  led[2].r=random(100, 256);
  led[2].g=random(0, 50);
  led[2].b=random(0, 100);
}


void loop() {

  for(int segment_i=0;segment_i<NUMPIXELS;segment_i++){

    if (loop_n%change_intensity==0){
      randomSeed(analogRead(0));
      randNumber=random(111, 1000);


      uint8_t n=0;
      while (randNumber > 0) {
        r_array[n]=(randNumber % 10);
        randNumber = randNumber / 10;
        n++;
      }
    }


    //iteration throught RGB
    for(int color_i=0;color_i<3;color_i++){ //3 due to RGB

      switch (color_i) {
        case 0:
        if (loop_n%change_intensity==0) led[segment_i].r_rand = r_array[color_i]%2;


        //Red
        if (led[segment_i].r<255) led[segment_i].r_canup=true;
        else led[segment_i].r_canup=false;

        if (led[segment_i].r>0) led[segment_i].r_candown=true;
        else led[segment_i].r_candown=false;

        if (led[segment_i].r_canup && led[segment_i].r_rand==1) led[segment_i].r++;
        if (led[segment_i].r_candown && led[segment_i].r_rand==0) led[segment_i].r--;

        break;

        case 1:
        if (loop_n%change_intensity==0) led[segment_i].g_rand = r_array[color_i]%2;

        //printf("loop_n %d, segment: %d, G rand %d R: %d, G: %d, B: %d \n", loop_n, segment_i, led[segment_i].g_rand, led[segment_i].r, led[segment_i].g, led[segment_i].b);
        //Green
        if (led[segment_i].g<255) led[segment_i].g_canup=true;
        else led[segment_i].g_canup=false;

        if (led[segment_i].g>0) led[segment_i].g_candown=true;
        else led[segment_i].g_candown=false;

        if (led[segment_i].g_canup && led[segment_i].g_rand==1) led[segment_i].g++;
        if (led[segment_i].g_candown && led[segment_i].g_rand==0) led[segment_i].g--;

        break;

        case 2:
        if (loop_n%change_intensity==0) led[segment_i].b_rand = r_array[color_i]%2;

        //printf("loop_n %d, segment: %d, B rand %d R: %d, G: %d, B: %d \n", loop_n, segment_i, led[segment_i].b_rand, led[segment_i].r, led[segment_i].g, led[segment_i].b);
        //Blue
        if (led[segment_i].b<255) led[segment_i].b_canup=true;
        else led[segment_i].b_canup=false;

        if (led[segment_i].b>0) led[segment_i].b_candown=true;
        else led[segment_i].b_candown=false;

        if (led[segment_i].b_canup && led[segment_i].b_rand==1) led[segment_i].b++;
        if (led[segment_i].b_candown && led[segment_i].b_rand==0) led[segment_i].b--;

        break;
      }
    }

    printf("loop_n %d, segment: %d, Rrand %d, Grand %d, Brand %d, R: %d, G: %d, B: %d \n", loop_n, segment_i,led[segment_i].r_rand, led[segment_i].g_rand, led[segment_i].b_rand, led[segment_i].r, led[segment_i].g, led[segment_i].b);


    strip.setPixelColor(segment_i, strip.Color(led[segment_i].r,led[segment_i].g,led[segment_i].b)); // Moderately bright green color.
    strip.show(); // This sends the updated pixel color to the hardware.
  }
  loop_n++;
  delay(50); // Delay for a period of time (in milliseconds).
}
