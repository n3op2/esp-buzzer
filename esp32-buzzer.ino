#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

WebServer server(80);
WiFiMulti WiFiMulti;
HTTPClient http;
WiFiClient client;

int sine[] = { 128, 131, 134, 137, 141, 144, 147, 150, 153, 156, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 188, 191, 194, 196, 199, 202, 204, 207, 209, 212, 214, 216, 219, 221, 223, 225, 227, 229, 231, 233, 234, 236, 238, 239, 241, 242, 244, 245, 246, 247, 249, 250, 250, 251, 252, 253, 254, 254, 255, 255, 255, 256, 256, 256, 256, 256, 256, 256, 255, 255, 255, 254, 254, 253, 252, 251, 250, 250, 249, 247, 246, 245, 244, 242, 241, 239, 238, 236, 234, 233, 231, 229, 227, 225, 223, 221, 219, 216, 214, 212, 209, 207, 204, 202, 199, 196, 194, 191, 188, 186, 183, 180, 177, 174, 171, 168, 165, 162, 159, 156, 153, 150, 147, 144, 141, 137, 134, 131, 128, 125, 122, 119, 115, 112, 109, 106, 103, 100, 97, 94, 91, 88, 85, 82, 79, 76, 73, 70, 68, 65, 62, 60, 57, 54, 52, 49, 47, 44, 42, 40, 37, 35, 33, 31, 29, 27, 25, 23, 22, 20, 18, 17, 15, 14, 12, 11, 10, 9, 7, 6, 6, 5, 4, 3, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 3, 4, 5, 6, 6, 7, 9, 10, 11, 12, 14, 15, 17, 18, 20, 22, 23, 25, 27, 29, 31, 33, 35, 37, 40, 42, 44, 47, 49, 52, 54, 57, 60, 62, 65, 68, 70, 73, 76, 79, 82, 85, 88, 91, 94, 97, 100, 103, 106, 109, 112, 115, 119, 122, 125 };

void handleSuccess() {
  for (int j = 0; j < 100; j++) {
    for (int i = 0; i < 255; i++) {
      dacWrite(25, sine[i]);
    }
    delay(3);
  }
  server.send(200, "text\t/plain", "sine wave, ye!");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("hatushka", "aaaaaaaa");
  server.on("/success", HTTP_GET, handleSuccess);
  server.begin();
}

void loop() {
  int val = 0;

  if (WiFiMulti.run() == WL_CONNECTED) {
    server.handleClient();
    val = analogRead(34);
    delay(100);
    if (val > 2048) {
      if (client, http.begin("http://192.168.0.100/open")) {
        int status = http.GET();
        delay(5000);
        http.end();
        Serial.println(status);
      }
    }
  }
}