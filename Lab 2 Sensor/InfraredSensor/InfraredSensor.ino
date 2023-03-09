#define lampu 19

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(14, INPUT);
  pinMode(lampu, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int AnalogValue, DigitalValue;

  DigitalValue=digitalRead(14);
  Serial.println(DigitalValue);
  delay(1000);
  if(DigitalValue == 1)
    digitalWrite(lampu,HIGH);
  else digitalWrite(lampu, LOW);
}
