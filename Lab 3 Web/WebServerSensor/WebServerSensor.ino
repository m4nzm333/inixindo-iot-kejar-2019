#include <WiFi.h>
#include "DHT.h"
#define DHTPIN 27 // what digital pin we're connected to

#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);


#define PORT 8080


const char * SSID = "MikrotikMakassar.id";
const char * PASSWORD = "inix_mk5";

String header = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
String tailer = "</body></html>";

WiFiServer server(PORT);
WiFiClient client;
String s;
String cmd;
int value;
void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("Web Server active: ");
  Serial.println(WiFi.localIP());
  server.begin();
  dht.begin();
}

float h,t,f;
void loop() {
  client = server.available(); //tunggu client
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  if (client) { // dapat client baru
    Serial.println("got a new client");
    while (client.connected()) {
      if (client.available()) {
        //Serial.println("Data can be read");
        s = client.readString();
        cmd = getCommand(s);
        if (cmd.equals("")) {
          refresh(0,0,0);
        } else if (cmd.equals("refresh?")) {
          refresh(h,t,f); // min max
        } else {
          refresh(0,0,0);
          client.stop();
        }
        Serial.println(cmd);
        delay(100);
      } else {
        client.stop();
      }

    }
    //client.stop();
  } else {
    //Serial.println("No client yet ");
  }

  delay(1000);
}
void refresh(float hum, float temp, float far) {
  client.println(header);
  client.print("<html><head><title>Sensor</title>");
  client.print("<meta name='viewport' content='width=device-width,initial - scale = 1.0 '>");
  client.print("</head>");
  client.print("<body><h1>Data Sensor</h1>");
  client.printf("<p>Nilai Data Humidity adalah : %.2f </p>", hum);
  client.printf("<p>Nilai Data Temperature adalah : %.2f C</p>", temp);
  client.printf("<p>Nilai Data Farenheit adalah : %.2f  F</p>", far);
  client.print("<p><form action='/refresh'><input type='submit' value = 'Refresh' > </p>");
  client.print("<script>setInterval(function(){window.location.href = ''}, 3000);</script>");
  client.println(tailer);
}
String getCommand(String s) {
  int i;
  i = s.indexOf(' ', 5);
  return (s.substring(5, i));
}
