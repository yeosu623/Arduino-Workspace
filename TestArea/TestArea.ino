

void setup(){
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
}

void loop(){
  digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(10, LOW);
  delay(1000);
}