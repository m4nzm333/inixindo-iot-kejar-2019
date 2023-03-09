#include <WiFi.h>
#include <PubSubClient.h>
#define BUILTIN_LED 2
// lolin led 5
// doit led 2

const char* SSID = "MikrotikMakassar.id";
const char* PASSWORD =  "inix_mk5";
const char* mqttServer = "tailor.cloudmqtt.com";
const int   mqttPort = 15074;
const char* mqttUser = "uxhoypgu";
const char* mqttPassword = "2AYsS8__K7_b";

WiFiClient espClient;
PubSubClient client(espClient);

int value;
char str_value[8];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  delay(1000);
  Serial.println();


  WiFi.disconnect(true);
  Serial.println(WiFi.localIP());

  connectToHotSpot();
  connectToMqttCloud();
//  toBlink(6);
}

void connectToHotSpot() {
  WiFi.begin( SSID, PASSWORD );

  Serial.print("Establishing connection to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! to ");
  Serial.println(WiFi.localIP());

}

void connectToMqttCloud() {
  String topic = "INIX";
  client.setServer(mqttServer, mqttPort);
  client.setCallback(receiveMessage);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      Serial.println("connected to MQTT Server");
      client.subscribe("INIX");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void receiveMessage(char*topic, byte*payload, unsigned int length) {
  int ntimes;
  // hanya tertarik pada byte pertama saja --> payload[0]
  // konversi bytes jd int
  ntimes = (int) ((char)payload[0] - '0'); //input harus karakter '0' sd '9'
  
  Serial.println(payload[0]);
  toBlink(ntimes);
}

void toBlink(int n) { // blink sebanyak n kali .....
  if (n < 0 || n > 20) n = 1; { // jika nilai input kacau, maka jadikan n=1
    for (int i = 0; i < n; i++) {
      digitalWrite(BUILTIN_LED, HIGH);
      delay(200);
      digitalWrite(BUILTIN_LED, LOW);
      delay(200);
    }
  }
}

void loop() {
  client.loop();
  if (! client.connected() ) {
    reconnect();
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe
      // setiap subscribe diisi "Topik"
      client.subscribe("INIX");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
