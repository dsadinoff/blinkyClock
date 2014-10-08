/*
A simple clock.

hour is red
min is green 
sec is blue
/60 sec is white
*/
#include "FastLED.h" // http://fastled.io/
#include <Button.h> // http://github.com/virgildisgr4ce/Button

#define NUM_LEDS 60
#define BUTTON_IN    10
#define LED_DATA_LINE 13


/* no clock on the BlinkyTape, so punt */
long epoch =4236000 + 1000000000; /*  arbitrarytime of day of machine start, in ms.  */

/* buffer for LED data */
CRGB leds[NUM_LEDS];  

Button button = Button(BUTTON_IN, BUTTON_PULLUP_INTERNAL, true, 50);
static int stopped =0;

void onPress(Button& b) {
  //advance 1 min.
  epoch +=   60L *1000L;
}

void onHold(Button &b){
    //advance 1 hour
  epoch +=  60 * 60L *1000L;
}


void setup() {
      
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
//   	delay(2000);
        button.pressHandler(onPress);
        button.holdHandler(onHold, 1000); /*hold time */

   	// For safety (to prevent too high of a power draw), the test case defaults to
   	// setting brightness to 25% brightness
   	LEDS.setBrightness(64);
        LEDS.addLeds<WS2812B, LED_DATA_LINE, GRB>(leds, NUM_LEDS);
}

void loop() {
        if( stopped){
          return;
        } 
        long now = millis();
        long curTime = now +epoch;
        long unixTime = curTime / 1000;
        int seconds = unixTime % 60;
        int hours = ((unixTime - (long)seconds ) % (3600L * 12L) )/ 3600L;
        int minutes = ((unixTime - seconds ) % 3600) /60;
        int sixtieths = (curTime * 60L / 1000L) %(60) ;

	memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB)); //clear all

        leds[sixtieths] = CRGB(20,20,20);
        leds[hours].r = 64;
        leds[minutes].g = 64;
        leds[seconds].b = 64;
            
			// and now, show your led array! 
         LEDS.show();
         button.process();
}

