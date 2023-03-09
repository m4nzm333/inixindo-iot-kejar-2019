#define dt 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(dt, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int AnalogValue, DigitalValue;
  AnalogValue = analogRead(dt);
//  DigitalValue =digitalRead(dt);
  Serial.println(AnalogValue);
  
  
  delay(1000);
}
