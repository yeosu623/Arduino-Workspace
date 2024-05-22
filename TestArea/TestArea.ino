#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo sv1;
Servo sv2;
bool angleReverse = false;
int angle = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Farm v1.0");

  sv1.attach(8);
  sv2.attach(9);
}

void loop() {
  int data = analogRead(1);
  Serial.println(data);

  // sv1.write(angle);
  // sv2.write(angle);
  // delay(22);

  // if(angleReverse) angle--;
  // else angle++;

  // if(angle == 0 || angle == 180) angleReverse = !angleReverse;
}