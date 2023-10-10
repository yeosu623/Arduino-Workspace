/*
예제 2.1.
Arduino에서 컴퓨터로 변수와 문자열 전송하기
*/

int number = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(number);
  Serial.print(" sec\n");
  delay(1000);
  number = number + 1;
}
