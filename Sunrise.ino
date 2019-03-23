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

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

void StageOne();
void StageTwo();
void StageThree();
void StageFour();
void StageFive();

unsigned char  red, green, blue;
int waitVal = 18000;
unsigned char brigtness;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

 // Serial.println("START");
    if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
  //   rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

}

void loop() {

  
  
  // put your main code here, to run repeatedly:
  
  brigtness = 3;

    if(AlarmCheck() == true)
    {
      StageOne();
      StageTwo();
    //  StageThree();
      StageFour();
      StageFive();
    }

   //DateTime now = rtc.now();

  //  Serial.print(now.year(), DEC);
  //  Serial.print('/');
  //  Serial.print(now.month(), DEC);
  //  Serial.print('/');
  //  Serial.print(now.day(), DEC);
  //  Serial.print(" (");
  //  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
 //   Serial.print(") ");
 //   Serial.print(now.hour());
 //   Serial.print(':');
 //   Serial.print(now.minute());
 //   Serial.print(':');
  //  Serial.print(now.second());
 //   Serial.println();
    
    delay(10000);
  
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
void StageOne()
{


strip.setBrightness(brigtness);

      red = 55;
      green = 63;
      blue = 135;

      for( int i = 0; i < 10; i++ ) {

        //equations for the 28-led loop
        red = red + 13;  // bringing up the red value by 13 for 10 steps to end up at desired color for next animation cycle
        green = green + 2;    // bringing up the green value by 2 for 10 steps to end up at desired color for next animation cycle
        blue = blue - 1;  // bringing down the blue value by 1 for 10 steps to end up at desired color for next animation cycle
        brigtness = brigtness + 1;
        
        // Sets the color for the top loop of 28 leds
        loadStrip(strip.Color(red, green, blue, 0));
        strip.setBrightness(brigtness);
        strip.show();
        //18 second delay between color change. Remember you're waking up slowly here!
        delay(waitVal);
        delay(waitVal);
        }
}

//second cycle. A little more brightness and moving colors more toward daylight. Works just like the previous animation
void StageTwo() {
    //increment brightness for second cycle
  // strip.setBrightness(13);

//change for git test heelo why isn't this working hehehehehe
  
    red = 185; 
    green = 83;  
    blue = 125;  
  
    for( int i = 0; i < 10; i++ ) {
  
        red = red + 5;  
        green = green - 4;  
        blue = blue - 8;  
        brigtness = brigtness + 3;
        
        loadStrip(strip.Color(red, green, blue, 0));
        strip.setBrightness(brigtness);
        strip.show(); 
 
        delay(waitVal);
        delay(waitVal);

    } //second for loop
}

void StageThree() {

 //  strip.setBrightness(23);

  
    red = 235; 
    green = 43;  
    blue = 15;

    for( int i = 0; i < 10; i++ ) {
    

        red = red - 18;  // Full Redness
        green = green + 20;    // Step up to yellow by adding green
        blue = blue + 11;  // Blue starts at full and goes down to zero
  
        // Now loop though each of the LEDs and set each one to the current color
     
        
        loadStrip(strip.Color(red, green, blue, 0));
        strip.setBrightness(brigtness);
        strip.show(); 
        
        delay(waitVal);
        delay(waitVal);
  
    } //second for loop
  
}

void StageFour() {

 //  strip.setBrightness(33);


  
    red = 235; 
    green = 43;  
    blue = 45;
  
    for( int i = 0; i < 10; i++ ) {


       // red = red + 14;  // Full Redness
        green = green + 8;    // Step up to yellow by adding green
      //  blue = blue + 1;  // Blue starts at full and goes down to zero
      brigtness = brigtness + 10;
      
        strip.setBrightness(brigtness);
        
        // Now loop though each of the LEDs and set each one to the current color
   
        
          loadStrip(strip.Color(red, green, blue, 0));
        strip.show(); 
        
        delay(waitVal);
        delay(waitVal);
  
    } //second for loop
}

void StageFive()
{
   for( int i = 0; i < 10; i++ )
   {
    brigtness = brigtness + 10;
    strip.setBrightness(brigtness);
    strip.show(); 
    delay(waitVal);
    delay(waitVal);
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

