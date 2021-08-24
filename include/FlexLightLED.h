#ifndef FlexLightLED_h
#define FlexLightLED_h

#include <Arduino.h>
#include <FastLED.h>


// LED configuration
#define LED_PIN           22
#define LED_TYPE          WS2812B
#define LED_COLOR_ORDER   GRB
#define LED_SEGMENTS      3
#define LEDS_PER_SEGMENT  19
#define LED_BRIGHTNESS    64
#define FRAMES_PER_SECOND 120

#define EFFECT_SPEED_SLOW   120
#define EFFECT_SPEED_MIDDLE 70
#define EFFECT_SPEED_FAST   20
#define EFFECT_SPEED        EFFECT_SPEED_FAST

CRGB leds[LED_SEGMENTS * LEDS_PER_SEGMENT];
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

#include "effect/WelcomeEffect.h"

typedef void (*EffectList[])();
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
EffectList effects = { WelcomeEffect };
uint8_t currentEffectIndex = 0; // Index number of which pattern is current

void nextEffect() {
  // add one to the current pattern number, and wrap around at the end
  currentEffectIndex = (currentEffectIndex + 1) % ARRAY_SIZE(effects);
  Serial.println("Playing effect " + currentEffectIndex);
}

CHSV hsv;
int current_led = 0;

void setupLED() {
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(leds, LED_SEGMENTS * LEDS_PER_SEGMENT);
    FastLED.setBrightness(LED_BRIGHTNESS);

    hsv.hue = gHue;
    hsv.val = 255;
    hsv.sat = 240;

    Serial.println("LED setup complete");
}



int prev_led(int pos) {
  if (pos == 0) {
    return LED_SEGMENTS * LEDS_PER_SEGMENT - 1;
  }

  return pos - 1;
}

int next_led(int pos) {
  if (pos == LED_SEGMENTS * LEDS_PER_SEGMENT - 1) {
    return 0;
  }

  return pos + 1;
}

void LED_ring() {

  for (int led = 0; led < LEDS_PER_SEGMENT * LED_SEGMENTS; led++) {
    int p = prev_led(current_led);
    int n = next_led(current_led);

    if (led == current_led) {


      leds[p].nscale8(100);
      leds[n] = HUE_PURPLE;
    } else {

    }

  }
  //FastLED.show();

  current_led = next_led(current_led);

/*
  for (int led = 0; led < LEDS_PER_SEGMENT; led++) {

    for (int segment = 0; segment < LED_SEGMENTS; segment++) {
    int offset = segment * LEDS_PER_SEGMENT;
    
      int pos = offset + led;
      
      //leds[pos] = CRGB::Blue;
      leds[pos] = hsv;
      hsv.hue += 7;
      // clear this led for the next time around the loop
      FastLED.show();

      leds[pos] = CRGB::Black;
      delay(EFFECT_SPEED);
    }
    //delay(EFFECT_SPEED * 0.6);
  }
*/  
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, LEDS_PER_SEGMENT * LED_SEGMENTS, gHue, 7);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, LEDS_PER_SEGMENT * LED_SEGMENTS, 20);
  int pos = beatsin16( 13, 0, LEDS_PER_SEGMENT * LED_SEGMENTS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}


void loopLED() {
    // Call the current pattern function once, updating the 'leds' array
    effects[currentEffectIndex]();
    FastLED.show();
    FastLED.delay(1000/FRAMES_PER_SECOND); 

    EVERY_N_MILLISECONDS( 20 ) { gHue++ ; } // slowly cycle the "base color" through the rainbow
    EVERY_N_SECONDS( 10 ) { nextEffect(); } // change patterns periodically
}

#endif 
