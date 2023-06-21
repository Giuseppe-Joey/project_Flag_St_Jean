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


   *******
   *how to reduce RAM utilization
   *1) use F statement::::   lcd.print(F("----- Motor "));
*/


#include <FastLED.h>
#include <IRremote.h>

// code working with 24 leds...crash with 137 (whole flag)
const int LED_PIN = 3;
const int NUM_LEDS = 132;


uint8_t brightness = 50;            // nominal leds brightness
unsigned long n_milliseconds = 25;   // nominal leds switching speed
unsigned long lastCode;             //store the last IR code received from remote

const int RECV_PIN = 2;           //IR remote controll receiver pin
IRrecv irrecv(RECV_PIN);
decode_results results;

CRGB leds[NUM_LEDS];    // creating the led array

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
CRGBPalette16 heat_palette = heatmap_gp;
CRGBPalette16 red2blue_palette = red2blue_gp;
CRGBPalette16 green420_palette = green420_gp;

CRGBPalette16 choice_palette = stJeanOLD_palette;
String choice_palette_string = "St-Jean OLD";








// ////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  
    Serial.begin(9600);
    Serial.println("#####################################");
    Serial.println("Initialization...");
    Serial.println("#####################################");
    
    irrecv.enableIRIn();
    irrecv.blink13(true);
    
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 50);
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);  
    FastLED.setBrightness(brightness);
    FastLED.setCorrection(UncorrectedColor);
    FastLED.setTemperature(DirectSunlight);

    delay(3000);
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
        n_milliseconds = 10;
      break;
  
      // CH button
      case 0xFF629D:
        Serial.println("CH button pressed!");
        n_milliseconds = 25;
      break;
  
      // CH+ button
      case 0xFFE21D:
        Serial.println("CH+ button pressed!");
        n_milliseconds = 50;
      break;

  
  
      // ***** SECOND ROW *****
      // PREV button
      case 0xFF22DD:
        Serial.println("PREV button pressed!");
      break;
  
      // NEXT button
      case 0xFF02FD:
        Serial.println("NEXT button pressed!");
      break;
  
      // PLAY/PAUSE button
      case 0xFFC23D:
        Serial.println("PLAY/PAUSE button pressed!");
      break;
  

  
      // ***** THIRD ROW *****
      // VOL- button
      case 0xFFE01F:
        Serial.println("VOL- button pressed!");
        if (brightness > 20)
          brightness = brightness - 5;
        else if ((brightness <= 20) && (brightness >= 2))
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
        choice_palette = stJeanOLD_palette;
        choice_palette_string = "St-Jean OLD";
      break;
  
      // 100+ button
      case 0xFF9867:
        Serial.println("100+ button pressed!");    
        n_milliseconds = 250; 
      break;
  
      // 200+ button
      case 0xFFB04F:
        Serial.println("200+ button pressed!");
        n_milliseconds = 500;
      break;



      // ***** FIFTH ROW *****
      // 1 button
      case 0xFF30CF:
        Serial.println("1 button pressed!");
        choice_palette = heat_palette;
        choice_palette_string = "Heat";
      break;
  
      // 2 button
      case 0xFF18E7:
        Serial.println("2 button pressed!");
        choice_palette = red2blue_palette;
        choice_palette_string = "Red to Blue";
      break;
  
      // 3 button
      case 0xFF7A85:
        Serial.println("3 button pressed!");
        choice_palette = green420_palette;
        choice_palette_string = "Green 420";      
      break;



      // ***** SIXTH ROW *****
      // 4 button
      case 0xFF10EF:
        Serial.println("4 button pressed!");
      break;
  
      // 5 button
      case 0xFF38C7:      
        Serial.println("5 button pressed!");
      break;
  
      // 6 button
      case 0xFF5AA5:
        Serial.println("6 button pressed!");
      break;




      // ***** SEVENTH ROW *****
      // 7 button
      case 0xFF42BD:
        Serial.println("7 button pressed!");
      break;
  
      // 8 button
      case 0xFF4AB5:
        Serial.println("8 button pressed!");
      break;
  
      // 9 button
      case 0xFF52AD:
        Serial.println("9 button pressed!");
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
    Serial.println(n_milliseconds); 

    // remote is 50% less accurate if we add delay......mystery...
    //delay(10);
      
}
