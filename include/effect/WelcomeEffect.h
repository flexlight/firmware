#ifndef WelcomeEffect_h
#define WelcomeEffect_h

#include <FastLED.h>

void WelcomeEffect() {
    fadeToBlackBy(leds, LEDS_PER_SEGMENT * LED_SEGMENTS, gHue);
    int pos = beatsin16( 13, 0, LEDS_PER_SEGMENT * LED_SEGMENTS - 1 );
    leds[pos] += CHSV(gHue, 255, 192);
}

#endif