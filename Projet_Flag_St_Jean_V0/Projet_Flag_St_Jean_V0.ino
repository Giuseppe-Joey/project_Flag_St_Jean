/*
   Created on     :   Mai 4, 2023
   Last Update    :   Mai 10, 2023

   Program Name   :
   Program File   :   Projet_Flag_St_Jean.ino
   Author         :   Giuseppe Lomonaco

   For            :   5@8 Génie: St-Jean-Baptiste
   Github         :   https://github.com/Giuseppe-Joey/project_Flag_St_Jean

   Program Description  :
   This project is based on the FASTLed Library for Arduino and it is used to 
   controll leds on a 

*/


#include <FastLED.h>

#define LED_TYPE        WS2812B
#define COLOR_ORDER     GRB
#define DATA_PIN        3
#define NUM_LEDS        200

unsigned long n_milliseconds = 5;
uint8_t brightness = 50;

// creating the led array
CRGB leds[NUM_LEDS];
int colorIndex[NUM_LEDS];


DEFINE_GRADIENT_PALETTE( heatmap_gp )  {
    0,    0,    0,    0,        //black
  128,  255,    0,    0,        //red
  200,  255,  255,    0,        //bright yellow
  255,  255,  255,  255         //full white  
};

DEFINE_GRADIENT_PALETTE( stjean_gp )  {
      0,      0,      255,    245,        //Cyan
    46,   0,      21,    255,        //dark blue
    179,    255,   255,    255,        //white
      255,      0,      255,    245,        //Cyan
};

// creating palettes
CRGBPalette16 stJean_palette = stjean_gp;
CRGBPalette16 heat_palette = heatmap_gp;



// ////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  
    Serial.begin(57600);
    
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 100);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  
    FastLED.setBrightness(brightness);
    FastLED.setCorrection(UncorrectedColor);
    FastLED.setTemperature(DirectSunlight);

//    // Fill the colorIndex array with random numbers
//    for (int i = 0; i < NUM_LEDS; i++)  {
//      colorIndex[i] = random8();
//    }
    
    delay(1000);
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {

    EVERY_N_MILLISECONDS(n_milliseconds)  {
      // switch on an LED at random, choosing a random color from the palette
      leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(stJean_palette, random8(), 255, LINEARBLEND);
    }

    // Fade all LEDS down by 1 in brightness each time this is called
    fadeToBlackBy(leds, NUM_LEDS, 1);

    FastLED.show(); 
}
