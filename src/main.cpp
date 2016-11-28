#include <Arduino.h>
#include <String>
#include "FastLED.h"
#include "networkManager.h"
#include "lightManager.h"

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
