#define trigPin 15
#define echoPin 5
long jarak;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   jarak = cek_jarak(trigPin, echoPin);
   Serial.println(jarak);
   delay(3000);
}

long cek_jarak(int out, int in){
  long duration, distance;
  digitalWrite(out, LOW);
  delayMicroseconds(2);
  digitalWrite(out, HIGH);
  delayMicroseconds(10);
  digitalWrite(out, LOW);
  duration = pulseIn(in, HIGH);
  distance = (duration/2) / 29.1;
  return distance; 
  
}
