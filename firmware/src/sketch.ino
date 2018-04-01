#include <math.h>
#include "FastLED.h"

#define DATA_PIN 5
#define NUM_LEDS 13

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    Serial.begin(9600);
    FastLED.setBrightness(10); // Remember to change this for demo
    leds[3] = CRGB::Blue;
    FastLED.clear();
    FastLED.show();
}

void loop() {
    double lat1 = 33.4;
    double lat2 = 34.4;
    double lon1 = 118.27;
    double lon2 = 118.27;
    double dir = getDir(lat1,lat2,lon1,lon2);
    while(true) {
        updateLEDs(dir, 100);
    }
}

// Calculates which LEDs should light up differently
void updateLEDs(double dir, double dist) {
    // 0 is is front of skateboard, goes CCW (can be changed depending on how lights are set up)

    dir = (dir >=0 && dir <= 360) ? dir : ((int) dir) % 360; // make sure dir is in range [0,360]
    int cLED = (int) floor((dir/360.0)*NUM_LEDS); // LED pointing towards destination most accurately
    int spread =log10f(1000/dist); // Larger distance = Less LEDs
    int sLED = (cLED - spread) % NUM_LEDS; // start LED for array

    int range = (spread*2)+1;
    int j;
    // Light direction
    for(int i = 0; i <= range; i++) {
        j = (i+sLED)%NUM_LEDS;
        leds[j] = CRGB::Red;
        FastLED.show();
    }
    // Neutral light
    for (int i = 0; i < NUM_LEDS - range; i++) {
        // Serial.println(i);
        leds[(j++)%NUM_LEDS] = CRGB::DodgerBlue;
        FastLED.show();
    }    
    FastLED.delay(250);
}

double getDir(double lat1, double lat2, double lon1, double lon2) {
    double radians = atan2((lon2 - lon1), (lat2 - lat1));
    double compassReading = radians * (180/PI);
    return compassReading;
}