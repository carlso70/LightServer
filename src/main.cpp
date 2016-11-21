#include <Arduino.h>
#include <String>
#include "FastLED.h"
#include "networkManager.h"
#include "lightManager.h"

/*
#include "ArduinoJson.h"
#include "ESP8266WiFi.h"
*/
/*
// How many leds in your strip?
#define NUM_LEDS 100
#define DATA_PIN 3

#define BRIGHTNESS         255

// Define the array of leds
CRGB leds[NUM_LEDS];

//WiFiServer server(80);
int numLit(0);
*/

// Managers
NetworkManager* networkManager;
LightManager* lightManager;

void setup() {
  Serial.begin(115200);
  Serial.print("testing");

  networkManager = new NetworkManager();
  networkManager->startConnection();
  lightManager = new LightManager();
  networkManager->setLightManager(lightManager);
}

void loop() {
  networkManager->checkHttpServer();
  //checkHttpServer();
}
