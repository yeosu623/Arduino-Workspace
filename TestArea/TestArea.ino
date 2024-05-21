#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#define FAN 10 
#define LED 11
#define MOTOR1 8
#define MOTOR2 9

Servo sv1;
Servo sv2;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // // put your setup code here, to run once:
  // pinMode(FAN, OUTPUT);
  // pinMode(LED, OUTPUT);
  // // digitalWrite(FAN, HIGH);
  // // digitalWrite(LED, HIGH);
  // sv1.attach(8);
  // sv2.attach(9);

  // lcd.begin();
  // lcd.noBacklight();
  // lcd.setCursor(0, 0);
  // lcd.print("Smart Farm v1.0");
}

void loop() {
  // int angle = 0;

  // for(angle = 0; angle < 180; angle++) {
  //   sv1.write(angle);
  //   sv2.write(angle);
  //   delay(20);
  // }
  // for(angle = 180; angle > 0; angle--) {
  //   sv1.write(angle);
  //   sv2.write(angle);
  //   delay(20);
  // }
}