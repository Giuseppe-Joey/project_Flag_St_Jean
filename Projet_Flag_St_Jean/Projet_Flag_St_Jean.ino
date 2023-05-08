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

#define LED_TYPE        WS2812B
#define COLOR_ORDER     GRB

#define NUM_LEDS        24
#define DATA_PIN        6
//#define BRIGHTNESS      50


// creating the led array
CRGB leds[NUM_LEDS];



unsigned long delayPeriod = 100;
uint8_t brightness = 50;

uint8_t hue = 0;  // to make sure  (0 <= hue <= 255)

uint8_t paletteIndex = 0;
uint8_t colorIndex[NUM_LEDS];




DEFINE_GRADIENT_PALETTE( heatmap_gp )  {
    0,    0,    0,    0,        //black
  128,  255,    0,    0,        //red
  200,  255,  255,    0,        //bright yellow
  255,  255,  255,  255         //full white  
};

CRGBPalette16 myPal = heatmap_gp;










uint8_t palIndex[NUM_LEDS];

DEFINE_GRADIENT_PALETTE( greenblue_gp )  {
      0,      0,      255,    245,        //Cyan
    46,   0,      21,    255,        //dark blue
    179,    12,   250,    0,        //green
      255,      0,      255,    245,        //Cyan
};

CRGBPalette16 greenBlue = greenblue_gp;










DEFINE_GRADIENT_PALETTE( stjean_gp )  {
      0,      0,      255,    245,        //Cyan
    46,   0,      21,    255,        //dark blue
    179,    255,   255,    255,        //white
      255,      0,      255,    245,        //Cyan
};

CRGBPalette16 stJean = stjean_gp;










CRGBPalette16 purplePalette = CRGBPalette16 (
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,

  CRGB::Magenta,
  CRGB::Magenta,
  CRGB::Linen,
  CRGB::Linen,

  CRGB::Magenta,
  CRGB::Magenta,
  CRGB::DarkViolet,
  CRGB::DarkViolet,

  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::Linen,
  CRGB::Linen
);










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
      leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(myPal, random8(), 255, LINEARBLEND);
    }

    // Fade all LEDS down by 1 in brightness each time this is called
    fadeToBlackBy(leds, NUM_LEDS, 1);

    FastLED.show();





    




    

}
// ****************************************************************************





















// /////////////////////////////////////////////////////////////////////////////////
void blueHueRandomFunction()  {
    // create a new pixel for led[0]
    leds[0] = CHSV(160, random8(), random8(100, 255));
  

    // copy each pixel to the next one, starting at the far end
    // thereby moving the pattern along the strip
    for (int i = NUM_LEDS-1; i > 0; i--)  {
      leds[i] = leds[i - 1];
    }
}
// /////////////////////////////////////////////////////////////////////////////////










// /////////////////////////////////////////////////////////////////////////////////
void LED_MOVING_BACK_AND_FORTH(float ledColor, unsigned long delayPeriod, int totalLed)    {
  
  FastLED.clear();
  
  for (int i = 0; i < totalLed; i++) {
    leds[i] = ledColor;
    FastLED.show();
    delay(delayPeriod);
    leds[i] = CRGB::Black;
  }  

  for (int i = totalLed-1; i >= 0; i--) {
    leds[i] = ledColor;
    FastLED.show();
    delay(delayPeriod);
    leds[i] = CRGB::Black;
  }  
}
// /////////////////////////////////////////////////////////////////////////////////















// /////////////////////////////////////////////////////////////////////////////////
void LED_MOVING_ALONG(float ledColor, unsigned long delayPeriod, int totalLed)    {
  
  FastLED.clear();
  
  for (int i = 0; i < totalLed; i++) {
    leds[i] = ledColor;
    FastLED.show();
      
    leds[i] = CRGB::Black;;
    delay(delayPeriod);
  }  
}
// /////////////////////////////////////////////////////////////////////////////////















// /////////////////////////////////////////////////////////////////////////////////
void LED_STACKING(float ledColor, unsigned long delayPeriod, int totalLed)    {
  
  FastLED.clear();
  
  for (int i = 0; i < totalLed; i++) {
    leds[i] = ledColor;
    FastLED.show();
    delay(delayPeriod);
    leds[i] = CRGB::Black;

    if (i == totalLed)  {
      leds[i] = ledColor; 
      FastLED.show();  
      delay(delayPeriod);
    }
  }  

  
}
// /////////////////////////////////////////////////////////////////////////////////











// /////////////////////////////////////////////////////////////////////////////////
void MULTIPLE_LED_MOVING_ALONG(unsigned long delayPeriod, int totalLed)  {

   for (int i = 0; i < totalLed; i++) {
    leds[i]  = CRGB::Red;
    if (i >= 5) {
      leds[i - 5] = CRGB::Yellow;
    }
    if (i >= 10) {
      leds[i - 10] = CRGB::Green;
    }
    if (i >= 15) {
      leds[i - 15] = CRGB::Cyan;
    }
    if (i >= 20) {
      leds[i - 20] = CRGB::Blue;
    }
    if (i >= 25) {
      leds[i - 25] = CRGB::Magenta;
    }
    FastLED.show();
    leds[i] = CRGB::Black;
    
    if (i >= 5) {
      leds[i - 5] = CRGB::Black;
    }
    if (i >= 10) {
      leds[i - 10] = CRGB::Black;
    }
    if (i >= 15) {
      leds[i - 15] = CRGB::Black;
    }
    if (i >= 20) {
      leds[i - 20] = CRGB::Black;
    }
    if (i >= 25) {
      leds[i - 25] = CRGB::Black;
    }
    delay(delayPeriod);
  }

}
// /////////////////////////////////////////////////////////////////////////////////













// /////////////////////////////////////////////////////////////////////////////////
byte r = 0; //start positions
byte g = 4;
byte b = 9;


void TEST(byte maxCount)
{
  
  /* ---------------------
 *  SECTION IN SETUP()
 *  --------------------
 * Serial.begin(115200);
 * while (!Serial);
 * Serial.println("r\tg\tb");
 * ---------------------
 */

 
 
  Serial.print(r);
  Serial.print("\t");
  Serial.print(g);
  Serial.print("\t");
  Serial.println(b);
  r++;
  if (r > maxCount)
  {
    r = 0;
  }
  g++;
  if (g > maxCount)
  {
    g = 0;
  }
  b++;
  if (b > maxCount)
  {
    b = 0;
  }
  delay(1000);
}
// /////////////////////////////////////////////////////////////////////////////////












// /////////////////////////////////////////////////////////////////////////////////
//Leds chase forwards along strip
int ledCount = 0;


void LED_CHASING()  {
  
  bool ledsAllOff = true;
  
  //shift the entire LED strip one LED position towards the end of the strip
  for (int i = NUM_LEDS - 1; i > 0; i--) {
    leds[i] = leds[i - 1];
    //check to see if the current LED is off (Black)
    if ((leds[i].red != 0) || (leds[i].green != 0) || (leds[i].blue != 0)) {
      ledsAllOff = false;  //this will be set false if any LED is not Black
    }
  }
  
  if (r == ledCount) {
    leds[0] = CRGB::Red;
    ledsAllOff = false;
  }
  
  else if (g == ledCount) {
    leds[0] = CRGB::Green;
    ledsAllOff = false;
  }
  
  else if (b == ledCount) {
    leds[0] = CRGB::Blue;
    ledsAllOff = false;
  }
  
  else {
    leds[0] = CRGB::Black;
  }
  
  FastLED.show();
  
  //restart the pattern when it has completely shifted through the LED strip
  if (ledsAllOff == true) {
    ledCount = 0;
  } else {
    ledCount++;
  }
  
  delay(delayPeriod);
}
// /////////////////////////////////////////////////////////////////////////////////
