#include "networkManager.h"
#include "lightManager.h"

#include "wifiKeys.h"

WiFiServer server(80);

NetworkManager::NetworkManager() {
  WiFi.mode(WIFI_AP);
  // WiFi.begin(SSID, Network pass)
  WiFi.begin("Snusdays", "BetaZeta1000!");
  server.begin();
}

void NetworkManager::setLightManager(LightManager* manager) {
  lightManager = manager;
}

void NetworkManager::startConnection() {
  Serial.println("Connecting...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(50);
  }
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void NetworkManager::checkHttpServer() {
  WiFiClient client = server.available();
  if (!client) {
    if (WiFi.status() != WL_CONNECTED) {
      startConnection();
    }
    return;
  }
  String request = client.readString();
  Serial.print("Recieved request: ");
  Serial.println(request);

  requestValues result = parseRequest(request);
  client.write("HTTP/1.0 200 OK\n\nHey you buddy: ");
  client.write(String(result.ledCount).c_str());

  // apply leds
  if (lightManager != 0) {
    lightManager->applyLeds(result);
  }

}

/*
* Parse's the JSON request, and returns a requestValues struct
*/
struct requestValues NetworkManager::parseRequest(String request) {
  StaticJsonBuffer<200> jsonBuffer;

  // Skips header of Json
  char lastChar = 0;
  int bodyIndex = -1;
  for (int i = 3; i < request.length(); i++) {
     String before(request.substring(i - 5, i));
     if (before.endsWith("\r\n\r\n") || before.endsWith("\n\n")) {
       bodyIndex = i;
       break;
     }
  }

//TODO create exceptions for when there is no body found
  if (bodyIndex < 0) {
    Serial.println("NO BODY FOUND");
  }

  String requestStr(request.substring(bodyIndex));
  int jsonIndex = requestStr.indexOf("{");
  Serial.print("JSON ONLY Request: ");
  Serial.print(requestStr.substring(jsonIndex));

  // Extract properties from JSON
  JsonObject& root = jsonBuffer.parseObject(requestStr.substring(jsonIndex));
  int count = root["LedCount"].as<int>();
  int bright = root["Brightness"].as<int>();

  requestValues a;
  a.ledCount = count;
  a.brightness = bright;

  return a;
}

NetworkManager::~NetworkManager() {}
