#include "LightManager.h"
#include "networkManager.h"

LightManager::LightManager() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
  FastLED.setBrightness(BRIGHTNESS);

  isChanging = false;
}

void LightManager::applyLeds(struct requestValues request) {
  isChanging = true;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 == 0) {
      leds[i] = i < request.ledCount ? CRGB::Red : CRGB::Black;
    } else {
      leds[i] = i < request.ledCount ? CRGB::Green : CRGB::Black;
    }
  }

  FastLED.setBrightness(request.brightness);
  FastLED.show();
}

void LightManager::cylon() {
  static uint8_t hue = 0;
  Serial.print("x");
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  Serial.print("x");

  // Now go in the other direction.
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
}

void LightManager::fadeall() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(250);
  }
}

void LightManager::applyColor(int red, int green, int blue, int count) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = i < count ? CRGB(red,green,blue) : CRGB::Black;
  }
}

LightManager::~LightManager() {}
