#include "FastLED.h"

#define DATA_PIN 5
#define NUM_LEDS 13

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    Serial.begin(9600);

    leds[3] = CRGB::Blue;
    FastLED.show();
}

void loop() {
    FastLED.clear();

    for (int i = 1; i < NUM_LEDS; i++) {
        Serial.println(i);
        leds[i] = (i%2) ? CRGB::Magenta : CRGB::Cyan;;
        FastLED.show();
        delay(100);
    }
}
