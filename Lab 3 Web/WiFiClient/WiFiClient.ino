#include <WiFi.h>
const char *SSID = "MikrotikMakassar.id";
const char *PASSWORD = "inix_mk5";

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.disconnect(true);
  connectToHotspot();
}

void connectToHotspot() {
  WiFi.begin(SSID, PASSWORD);
  Serial.print("trying to establish connection to WiFi Router");
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected! IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("\nMAC Address : ");
  Serial.println(WiFi.macAddress());
}
void loop(){
  
}
