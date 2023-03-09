#include "DHT.h"

#define DHTPIN 27 // what digital pin we're connected to
#define DHTTYPE DHT11 // DHT 11
// #define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

  int i;
  int b;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("DHTxx test!");
  
  dht.begin();
}

float h,t,f;

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  

  Serial.print(h);
  Serial.print(" %\t");
  Serial.print(t);
  Serial.print("  C\t");
  Serial.print(f);
  Serial.println("  F\t"); 
  delay(3000);
}
