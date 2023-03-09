#define d0 23
#define a0 34
#define lampu 19

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(a0, INPUT);
  pinMode(d0, INPUT);
  pinMode(lampu, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int AnalogValue, DigitalValue;
  AnalogValue = analogRead(a0);
  DigitalValue =digitalRead(d0);
  Serial.print(AnalogValue);
  Serial.print(" & ");
  Serial.println(DigitalValue);
  
  delay(1000);


  if(AnalogValue>2000)
   digitalWrite(lampu,HIGH);
  else digitalWrite(lampu,LOW);
}
