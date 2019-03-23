#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "RTClib.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

RTC_DS3231 rtc;
#define PIN 6

#define NUM_LEDS 30
#define BRIGHTNESS 10

const int LightSwitchPin = 9; 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

void LEDUpdater (uint8_t RedInc, uint8_t GreenInc, uint8_t BlueInc, uint8_t BrightnessInc);

unsigned char  red, green, blue;
unsigned char brigtness;


void setup() {
 
    Serial.begin(9600);

    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  pinMode(LightSwitchPin, INPUT);
  
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'


    if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    
    // set the time to the time of this compile
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  }
}

void loop() {

    //if the switch is on, run the LEDs based on the pot settings
    if(digitalRead(LightSwitchPin) == 1)
    {
      UserSelectedLED();
    }

    //else, check the alarm
    else if(AlarmCheck() == true)
    {
      //preload the colour values to their starting point
      red = 55;
      green = 63;
      blue = 135;
      brigtness = 3;

      //update the LEDs through a cycle of blue, to red, and then a sun like colour that gets brighter 
      LEDUpdater(13, 2, -1, 1);
      LEDUpdater(5, -4, -8, 3);
      LEDUpdater(0, 8, 1, 10);
      LEDUpdater(0, 0, 0, 10);
     }

    delay(10000); //10 second delay so we don't bother the RTC too much
  
}

void UserSelectedLED()
{
    unsigned int RedPotValue, BluePotValue, GreenPotValue, BrightPotValue;
  
    RedPotValue = analogRead(A1);
    RedPotValue = map(RedPotValue, 0, 1024, 0, 255);
    
    BluePotValue = analogRead(A2);
    BluePotValue = map(BluePotValue, 0, 1024, 0, 255);
    
    GreenPotValue = analogRead(A3);
    GreenPotValue = map(GreenPotValue, 0, 1024, 0, 255);
    
    BrightPotValue = analogRead(A6);
    BrightPotValue = map(BrightPotValue, 0, 1024, 0, 255);
    
    loadStrip(strip.Color(RedPotValue, BluePotValue, GreenPotValue, 0)); //Load the colour to the strip
    strip.setBrightness(BrightPotValue);
    strip.show(); 
    Serial.println(RedPotValue);  
}

bool AlarmCheck()
{
  DateTime now = rtc.now();

  if(now.hour() == 06)
  {
     if(now.minute() == 30)
    {
      Serial.println("ALARM!");
      return true;
    }    
  }
 
  return false;
}

//This function updates the colours based on the values passed into it
void LEDUpdater (uint8_t RedInc, uint8_t GreenInc, uint8_t BlueInc, uint8_t BrightnessInc)
{
      for( int i = 0; i < 10; i++ ) {

       red = red + RedInc;          // Update red
       green = green + GreenInc;    // Update Green
       blue = blue + BlueInc;       // Update Blue
       brigtness = brigtness + BrightnessInc;   // Update the Brightness
      
       strip.setBrightness(brigtness);  //Load the brightness setting to the LED strip
       loadStrip(strip.Color(red, green, blue, 0)); //Load the colour to the strip
       strip.show(); 

       //delay function can't take too big of a value, so call 2
       delay(18000);
       delay(18000);
      }
}

void loadStrip(uint32_t colour)
{
  //load each LED with the colour
  for(uint16_t i=0; i<strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, colour);
  }
}

