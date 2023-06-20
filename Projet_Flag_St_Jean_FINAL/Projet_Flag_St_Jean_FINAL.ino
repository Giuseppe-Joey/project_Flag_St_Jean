/*
   Created on     :   Mai 4, 2023
   Last Update    :   Juin 20, 2023

   Program Name   :
   Program File   :   Projet_Flag_St_Jean.ino
   Author         :   Giuseppe Lomonaco

   For            :   5@8 Génie: St-Jean-Baptiste
   Github         :   https://github.com/Giuseppe-Joey/project_Flag_St_Jean

   Program Description  :
   This project is based on the FASTLed Library for Arduino and it is used to 
   controll leds on a 

      HEX CODES:
   
   CH-  : FFA25D
   CH   : FF629D  
   CH+  : FFE21D
   PREV : FF22DD
   NEXT : FF02FD
   PLAY : FFC23D
   VOL- : FFE01F
   VOL+ : FFA857
   EQ   : FF906F
   0    : FF6897
   100+ : FF9867
   200+ : FFB04F
   1    : FF30CF
   2    : FF18E7
   3    : FF7A85
   4    : FF10EF
   5    : FF38C7
   6    : FF5AA5
   7    : FF42BD
   8    : FF4AB5
   9    : FF52AD
       

*/




#include <FastLED.h>
#include <Wire.h> 
#include <IRremote.h>

#define LED_TYPE        WS2812B
#define COLOR_ORDER     GRB
#define LED_PIN        3
#define NUM_LEDS        24

// IR REMOTE CONTROLL SECTION
const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

// define variable to store the last code received
unsigned long lastCode;

// nominal speed for ramdom palette function
unsigned long n_milliseconds = 5;

// nominal LEDs brightness
uint8_t brightness = 50;

// creating the led array
CRGB leds[NUM_LEDS];


DEFINE_GRADIENT_PALETTE( heatmap_gp )  {
    0,    0,    0,    0,        //black
  128,  255,    0,    0,        //red
  200,  255,  255,    0,        //bright yellow
  255,  255,  255,  255         //full white  
};

DEFINE_GRADIENT_PALETTE( stjeanOLD_gp )  {
      0,      0,      255,    245,        //Cyan
    46,   0,      21,    255,        //dark blue
    179,    255,   255,    255,        //white
      255,      0,      255,    245,        //Cyan
};

DEFINE_GRADIENT_PALETTE( stjeanNEW_gp )  {
      0,   0,      21,    255,        //dark blue
      46,      0,      255,    245,        //Cyan
    179,    255,   255,    255,        //white
      255,      0,      21,    255,        //Dark Blue
};

DEFINE_GRADIENT_PALETTE( red2blue_gp )  {
      0,      255,      0,    0,        //red
   46,   255,      0,    239,        //purple
    179,    0,   26,    255,        //blue
    255,  255,  255,  255,        //white
};

DEFINE_GRADIENT_PALETTE( green420_gp )  {
      0,    0,    255,    137,        //light green
      46,      0,      255,    0,        //green
   179,   255,      255,    0,        //yellow
    255,    255,   255,    255,        //white
};


// creating palettes
CRGBPalette16 stJeanOLD_palette = stjeanOLD_gp;
CRGBPalette16 stJeanNEW_palette = stjeanNEW_gp;
CRGBPalette16 heat_palette = heatmap_gp;
CRGBPalette16 red2blue_palette = red2blue_gp;
CRGBPalette16 green420_palette = green420_gp;

CRGBPalette16 choice_palette = stJeanNEW_palette;
String choice_palette_string = "St-Jean New";



// ////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  
    Serial.begin(9600);
    
    irrecv.enableIRIn();
    irrecv.blink13(true);

    Serial.println("########################");
    Serial.println("Initialization...");
    
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 50);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);  
    FastLED.setBrightness(brightness);
    FastLED.setCorrection(UncorrectedColor);
    FastLED.setTemperature(DirectSunlight);

    delay(1000);
}









// /////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {


  // reading the IR receiver
  if (irrecv.decode(&results)){  
    if (results.value == 0xFFFFFFFF){
      results.value = lastCode;
    }  

    // store received code from remote
    lastCode = results.value;
          
    // resume reading IR sensor ???
    irrecv.resume();






    switch(lastCode){
  
      // ***** FIRST ROW *****
      // CH- button
      case 0xFFA25D:
      Serial.println("CH- button pressed!");
//      if (n_milliseconds >= 2)
//        n_milliseconds = n_milliseconds - 1;
//      else if (n_milliseconds == 1)
        n_milliseconds = 1;
      break;
  
      // CH button
      case 0xFF629D:
      Serial.println("CH button pressed!");
      n_milliseconds = 5;
      break;
  
      // CH+ button
      case 0xFFE21D:
      Serial.println("CH+ button pressed!");
//      if (n_milliseconds < 100)
//        n_milliseconds = n_milliseconds + 1;
      n_milliseconds = 10;
      break;
  
  
      // ***** SECOND ROW *****
      // PREV button
      case 0xFF22DD:
      Serial.println("PREV button pressed!");
      choice_palette = heat_palette;
      choice_palette_string = "Heat";
      break;
  
      // NEXT button
      case 0xFF02FD:
      Serial.println("NEXT button pressed!");
      choice_palette = red2blue_palette;
      choice_palette_string = "Red to Blue";
      break;
  
      // PLAY/PAUSE button
      case 0xFFC23D:
      Serial.println("PLAY/PAUSE button pressed!");
      choice_palette = green420_palette;
      choice_palette_string = "Green 420";
      break;
  
  
      // ***** THIRD ROW *****
      // VOL- button
      case 0xFFE01F:
      Serial.println("VOL- button pressed!");
      if (brightness > 10)
        brightness = brightness - 5;
      else if ((brightness <= 10) && (brightness >= 2))
        brightness = brightness - 1;
      else if (brightness == 1)
        brightness = 1; 
      break;
  
      // VOL+ button
      case 0xFFA857:
      Serial.println("VOL+ button pressed!");
      if (brightness < 240)
        brightness = brightness + 5;
      else if ((brightness >= 240) && (brightness <= 253))
        brightness = brightness + 1;
      else if (brightness == 254)
        brightness = 254; 
      break;
  
      // EQ button
      case 0xFF906F:
      Serial.println("EQ button pressed!");
      brightness = 50;
      break;


      // ***** FOURTH ROW *****
      // 0 button
      case 0xFF6897:
      Serial.println("0 button pressed!");
      break;
  
      // 100+ button
      case 0xFF9867:
      Serial.println("100+ button pressed!");
      break;
  
      // 200+ button
      case 0xFFB04F:
      Serial.println("200+ button pressed!");
      break;

      }

      
    }
   














      

   
    EVERY_N_MILLISECONDS(n_milliseconds)  {
      // switch on an LED at random, choosing a random color from the palette
      leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(choice_palette, random8(), 255, LINEARBLEND);
    }
      // Fade all LEDS down by 1 in brightness each time this is called
      fadeToBlackBy(leds, NUM_LEDS, 1);

      FastLED.setBrightness(brightness);
      FastLED.show(); 






    Serial.print("Run Time: ");
    Serial.print(millis() / 1000);
    Serial.print(" s;       ");
    
    Serial.print("IR: ");
    Serial.print(lastCode, HEX);   
    
    Serial.print(";        Brightness: ");  
    Serial.print(brightness); 
    Serial.print(" / 255");  
    
    Serial.print(";        n_milliseconds: ");  
    Serial.print(n_milliseconds); 

    Serial.print(";        Palette: ");  
    Serial.println(choice_palette_string); 
      
}
