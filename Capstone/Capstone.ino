#include <LiquidCrystal_I2C.h>
#include <DFRobot_DHT11.h>
#include <Wire.h>

#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4
#define BUTTON4 5
#define BUTTON5 6
#define TEMP_HUMID_SENSOR 7
#define LIGHT_SENSOR 0
int button1 = HIGH, button1_prev = HIGH;
int button2 = HIGH, button2_prev = HIGH;
int button3 = HIGH, button3_prev = HIGH;
int button4 = HIGH, button4_prev = HIGH;
int button5 = HIGH, button5_prev = HIGH;
int light = 0; // 밝을때 50, 어두울때 10
DFRobot_DHT11 dht;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int second_clock = 0;

void setup() {
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello World");
  lcd.setCursor(0, 1);
  lcd.print("Arduino CLCD");

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(BUTTON5, INPUT_PULLUP);
}

void loop() {
  sensors_read();

  if(button1_push_check()) { // button1 누를 때
    button1_prev = LOW;

    lcd.setCursor(0, 1);
    lcd.print("button1         ");
  }
  if(button2_push_check()) { // button2 누를 때
    button2_prev = LOW;

    lcd.setCursor(0, 1);
    lcd.print("button2         ");
  }
  if(button3_push_check()) { // button3 누를 때
    button3_prev = LOW;

    lcd.setCursor(0, 1);
    lcd.print("button3         ");
  }
  if(button4_push_check()) { // button4 누를 때
    button4_prev = LOW;

    lcd.setCursor(0, 1);
    lcd.print("button4         ");
  }
  if(button5_push_check()) { // button5 누를 때
    button5_prev = LOW;

    lcd.setCursor(0, 1);
    lcd.print("button5         ");
  }

  buttons_pull_check();
}

void sensors_read() {
  button1 = digitalRead(BUTTON1);
  button2 = digitalRead(BUTTON2);
  button3 = digitalRead(BUTTON3);
  button4 = digitalRead(BUTTON4);
  button5 = digitalRead(BUTTON5);

  light = analogRead(LIGHT_SENSOR);
  dht.read(TEMP_HUMID_SENSOR);
}

int button1_push_check() {
  return button1 == LOW && button1_prev == HIGH;
}
int button2_push_check() {
  return button2 == LOW && button2_prev == HIGH;
}
int button3_push_check() {
  return button3 == LOW && button3_prev == HIGH;
}
int button4_push_check() {
  return button4 == LOW && button4_prev == HIGH;
}
int button5_push_check() {
  return button5 == LOW && button5_prev == HIGH;
}

void buttons_pull_check() {
  if(button1 == HIGH && button1_prev == LOW) { // button1 땔 때
    button1_prev = HIGH;
    delay(10);
  }
  if(button2 == HIGH && button2_prev == LOW) { // button2 땔 때
    button2_prev = HIGH;
    delay(10);
  }
  if(button3 == HIGH && button3_prev == LOW) { // button3 땔 때
    button3_prev = HIGH;
    delay(10);
  }
  if(button4 == HIGH && button4_prev == LOW) { // button4 땔 때
    button4_prev = HIGH;
    delay(10);
  }
  if(button5 == HIGH && button5_prev == LOW) { // button5 땔 때
    button5_prev = HIGH;
    delay(10);
  }
}
