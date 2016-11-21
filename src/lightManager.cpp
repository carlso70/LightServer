#include "LightManager.h"
#include "networkManager.h"

LightManager::LightManager() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
  FastLED.setBrightness(BRIGHTNESS);
}

void LightManager::applyLeds(int request) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = i < numLit ? CRGB::Red : CRGB::Black;
  }
  FastLED.show();
}


LightManager::~LightManager() {}
