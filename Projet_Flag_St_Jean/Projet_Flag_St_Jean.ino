/*
   Created on     :   Mai 4, 2023
   Last Update    :   Mai 4, 2023

   Program Name   :
   Program File   :   Projet_Flag_St_Jean.ino
   Author         :   Giuseppe Lomonaco

   For            :   5@8 Génie: St-Jean-Baptiste
   Github         :   https://github.com/Giuseppe-Joey/project_Flag_St_Jean

   Program Description  :
   This project is based on the FASTLed Library for Arduino and it is used to 
   controll leds on a 

*/



// adding test line for github



#include <FastLED.h>
//#include "functions.h"
//#include "color_palettes.h"



#define LED_TYPE        WS2812
#define COLOR_ORDER     GRB


#define DATA_PIN        6
//#define BRIGHTNESS      50
#define NUM_LEDS        50 



// creating the led array
CRGB leds[NUM_LEDS];



unsigned long delayPeriod = 100;
uint8_t brightness = 50;

uint8_t hue = 0;  // to make sure  (0 <= hue <= 255)

//uint8_t paletteIndex = 0;
uint8_t colorIndex[NUM_LEDS];
//uint8_t palIndex[NUM_LEDS];


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


//// including palette from color_palettes.h
//CRGBPalette16 greenBlue = greenblue_gp;
CRGBPalette16 stJean = stjean_gp;
CRGBPalette16 myPal = heatmap_gp;



//
//CRGBPalette16 purplePalette = CRGBPalette16 (
//  CRGB::DarkViolet,
//  CRGB::DarkViolet,
//  CRGB::DarkViolet,
//  CRGB::DarkViolet,
//
//  CRGB::Magenta,
//  CRGB::Magenta,
//  CRGB::Linen,
//  CRGB::Linen,
//
//  CRGB::Magenta,
//  CRGB::Magenta,
//  CRGB::DarkViolet,
//  CRGB::DarkViolet,
//
//  CRGB::DarkViolet,
//  CRGB::DarkViolet,
//  CRGB::Linen,
//  CRGB::Linen
//);










// ****************************************************************************
void setup() {
  
    Serial.begin(115200);
    
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 50);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  
    FastLED.setBrightness(brightness);
    FastLED.setCorrection(UncorrectedColor);
    FastLED.setTemperature(DirectSunlight);

    // Fill the colorIndex array with random numbers
    for (int i = 0; i < NUM_LEDS; i++)  {
      colorIndex[i] = random8();
    }
    
    delay(1000);
}
// ****************************************************************************













// ****************************************************************************
void loop() {

  float red = CRGB::Red;
  float white = CRGB::White;
  float blue = CRGB::Blue;


    EVERY_N_MILLISECONDS(50)  {
      // switch on an LED at random, choosing a random color from the palette
      leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(stJean, random8(), 255, LINEARBLEND);
    }

    // Fade all LEDS down by 1 in brightness each time this is called
    fadeToBlackBy(leds, NUM_LEDS, 1);




    //blueHueRandomFunction(leds, NUM_LEDS);



    FastLED.show(); 

}
// ****************************************************************************
