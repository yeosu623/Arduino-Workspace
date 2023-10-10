/* 
예제 4.1
LED 점멸
*/

int i;
const int ledA = 3; // RED
const int ledB = 5; // GREEN

void setup() {
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {
  digitalWrite(ledA, HIGH);
  digitalWrite(ledB, LOW);
  delay(1000);
  digitalWrite(ledA, LOW);
  digitalWrite(ledB, HIGH);
  delay(1000);

  // for(i = 0; i <= 255; i++) {
  //   analogWrite(ledA, i);
  //   analogWrite(ledB, 255-i);
  //   delay(3);
  // }
  // for(i = 0; i <= 255; i++) {
  //   analogWrite(ledB, i);
  //   analogWrite(ledA, 255-i);
  //   delay(3);
  // }

}
