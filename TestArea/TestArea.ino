#include <DFRobot_DHT11.h> // 이 라이브러리를 사용하겠다. 
DFRobot_DHT11 DHT;
#define DHT11_PIN 7

void setup(){
  Serial.begin(9600); // UART 통신 시적
}

void loop(){
  DHT.read(DHT11_PIN);
  Serial.print(DHT.temperature); //온도를 출력하겠다.
  Serial.print(",");
  Serial.println(DHT.humidity); //습도를 출력하겠다.
  delay(1000);
}