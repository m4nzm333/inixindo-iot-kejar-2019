#include <WiFi.h>
#define PORT 8080
#define LED_BUILTIN 2
const char *SSID = "MikrotikMakassar.id";
const char *PASSWORD = "inix_mk5";
String header = "HTTP/1.1 200 OK\n Content-Type: text/html\n\n<html><head><style>.btn-green{padding:30px;width:250px;background-color:green;color:white;}.btn-red{padding:30px;width:250px;background-color:red;color:white;}</style></head><body>";
String tailer = "</body></htmL>";
WiFiServer server(8080);
WiFiClient client;

bool blinking = false;
bool ledOn = false;

String s;
String cmd;

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.begin(SSID, PASSWORD);
  pinMode(LED_BUILTIN, OUTPUT);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Web server active: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  String stringResponse = "";
  
          
  client = server.available();
  if(client){
    while(client.connected()){
      
      if(client.available()){
        s = client.readString();
        cmd = getCommand(s);
        if(cmd.equals("")){
          Serial.println("HOMEPAGE");
          
          stringResponse += "<br><br><p><a href=\"blink\" class=\"btn-green\">LED Blinking </a></p>";
          stringResponse += "<br><br><p><a href=\"on\" class=\"btn-green\">HIDUPKAN LED</a></p>";
          response(stringResponse);
          
          
        } else if(cmd.equals("blink")){
          blinking = true;
          ledOn = false;
          
          stringResponse += "<br><br><p><a href=\"blink\" class=\"btn-red\">LED Blinking </a></p>";
          stringResponse += "<br><br><p><a href=\"off\" class=\"btn-red\">Matikan LED</a></p>";
          response(stringResponse);

          
        } else if(cmd.equals("on")){
          blinking = false;
          ledOn = true;
          
          stringResponse += "<br><br><p><a href=\"blink\" class=\"btn-green\">LED Blinking </a></p>";
          stringResponse += "<br><br><p><a href=\"off\" class=\"btn-red\">Matikan LED</a></p>";
          response(stringResponse);
          
        } else if(cmd.equals("off")){
          blinking = false;
          ledOn = false;
          
          stringResponse += "<br><br><p><a href=\"blink\" class=\"btn-green\">LED Blinking </a></p>";
          stringResponse += "<br><br><p><a href=\"on\" class=\"btn-green\">Hidupkan LED</a></p>";
          response(stringResponse);

        } else {
          response(s);
          client.stop();
        }
      } else {
        client.stop();
      }
      
    }
  }

  if(blinking || ledOn){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
  }
  if(blinking || !ledOn){
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
}

void response(String konten){
  client.println(header);
  client.println(konten);
  client.println(tailer);
}

String getCommand(String s){
  return (s.substring(5, s.indexOf(' ', 5)));
}
