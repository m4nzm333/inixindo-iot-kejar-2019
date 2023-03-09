#include <WiFi.h>
#include <PubSubClient.h>

#define trigPin 14
#define echoPin 12

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
  Serial.begin(115200); 
  delay(1000);
  Serial.println();
//  randomSeed(micros());
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  WiFi.disconnect(true);
  Serial.println(WiFi.localIP());
  
  connectToHotSpot();
  connectToMqttCloud();
  
//  value= random(1,10000);
//  sprintf(str_value,"%05d", value);
//  client.publish("INIX", str_value);
}

void connectToHotSpot() {
  WiFi.begin( SSID, PASSWORD );

 Serial.print("Establishing connection to WiFi");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! to ");
  Serial.println(WiFi.localIP());
}

void connectToMqttCloud() {
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      Serial.println("connected to MQTT Server");  
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

long jarak;
void loop() {
  jarak = cek_sensor(trigPin, echoPin);
  Serial.println(jarak);
  char jarakS[10];
//  client.publish("INIX", ldr);
  delay(1000);
}

float cek_sensor(int out, int in){
  long duration, distance;
  digitalWrite(out, LOW);
  delayMicroseconds(2);
  digitalWrite(out, HIGH);
  delayMicroseconds(10);
  digitalWrite(out, LOW);
  duration = pulseIn(in, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.println(distance);
  return distance;
}
