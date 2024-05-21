#include <LiquidCrystal_I2C.h>
#include <DFRobot_DHT11.h>
#include <Wire.h>

#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4
#define BUTTON4 5
#define BUTTON5 6
#define TEMP_HUMID_SENSOR 7
#define SPRINGCOOLER1 8
#define SPRINGCOOLER2 9
#define FAN 10
#define LED 11
#define LIGHT_SENSOR 0
bool humid_start = false;
char str1[16], str2[16];
int button1 = HIGH, button1_prev = HIGH;
int button2 = HIGH, button2_prev = HIGH;
int button3 = HIGH, button3_prev = HIGH;
int button4 = HIGH, button4_prev = HIGH;
int button5 = HIGH, button5_prev = HIGH;
int light = 0; // 밝을때 50, 어두울때 10
int temp_min = 0, temp_max = 30;
int light_min = 10;
int hydrate_min = 30, hydrate_max = 50;
uint64_t preTime, nowTime;
DFRobot_DHT11 dht;
LiquidCrystal_I2C lcd(0x27, 16, 2);
typedef enum _Mode {
  TEMP,
  HUMID,
  LIGHT,
  HYDRATE
} Mode;
Mode mode = TEMP;

void setup() {
  preTime = millis();
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Farm v1.0");

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(BUTTON5, INPUT_PULLUP);
}

void loop() {
  nowTime = millis();
  sensors_read();
  lcd_print();
  temp_min_check();
  temp_max_check();
  light_min_check();
  hydrate_min_check();

  if(button1_push_check()) { // button1 누를 때
    button1_prev = LOW;
    switch(mode) {
      case TEMP    : temp_min -= 1; break;
      case HUMID   : break;
      case LIGHT   : light_min -= 5; break;
      case HYDRATE : hydrate_min -= 5; break;
    }
  }
  if(button2_push_check()) { // button2 누를 때
    button2_prev = LOW;
    switch(mode) {
      case TEMP    : temp_min += 1; break;
      case HUMID   : break;
      case LIGHT   : light_min += 5; break;
      case HYDRATE : hydrate_min += 5; break;
    }
  }
  if(button3_push_check()) { // button3 누를 때
    button3_prev = LOW;
    switch(mode) {
      case TEMP    : mode = HUMID;   break;
      case HUMID   : mode = LIGHT;   break;
      case LIGHT   : mode = HYDRATE; break;
      case HYDRATE : mode = TEMP;    break;
    }
  }
  if(button4_push_check()) { // button4 누를 때
    button4_prev = LOW;
    switch(mode) {
      case TEMP    : temp_max -= 1; break;
      case HUMID   : break;
      case LIGHT   : break;
      case HYDRATE : hydrate_max -= 5; break;
    }
  }
  if(button5_push_check()) { // button5 누를 때
    button5_prev = LOW;
    switch(mode) {
      case TEMP    : temp_max += 1; break;
      case HUMID   : break;
      case LIGHT   : break;
      case HYDRATE : hydrate_max += 5; break;
    }
  }

  buttons_pull_check();
}

void sensors_read() {
  button1 = digitalRead(BUTTON1);
  button2 = digitalRead(BUTTON2);
  button3 = digitalRead(BUTTON3);
  button4 = digitalRead(BUTTON4);
  button5 = digitalRead(BUTTON5);

  if(nowTime - preTime >= 1000) {
    preTime = nowTime;

    light = analogRead(LIGHT_SENSOR);
    dht.read(TEMP_HUMID_SENSOR);
  }
}

void lcd_print() {
  switch(mode) {
    case TEMP :
      sprintf(str1, "TEMPURATURE : %-2d", dht.temperature);
      lcd.setCursor(0, 0);
      lcd.print(str1);

      sprintf(str2, "MIN: %-2d, MAX: %-2d", temp_min, temp_max);
      lcd.setCursor(0, 1);
      lcd.print(str2);
      break;

    case HUMID :
      if(humid_start == false) {
        humid_start = true;
        
        lcd.setCursor(0, 0);
        lcd.print("HUMID : ...     ");
      }
      if(dht.humidity != 0) {
        sprintf(str1, "HUMID : %-2d      ", dht.humidity);
        lcd.setCursor(0, 0);
        lcd.print(str1);
      }

      sprintf(str2, "                ");
      lcd.setCursor(0, 1);
      lcd.print(str2);
      break;

    case LIGHT :
      humid_start = false;

      sprintf(str1, "LIGHT : %-2d      ", light);
      lcd.setCursor(0, 0);
      lcd.print(str1);

      sprintf(str2, "MIN: %-2d         ", light_min);
      lcd.setCursor(0, 1);
      lcd.print(str2);
      break;

    case HYDRATE :
      sprintf(str1, "HYDRATE : %-2d    ", 0);
      lcd.setCursor(0, 0);
      lcd.print(str1);

      sprintf(str2, "MIN: %-2d, MAX: %-2d", hydrate_min, hydrate_max);
      lcd.setCursor(0, 1);
      lcd.print(str2);
      break;
  }
}

void temp_min_check() {

}
void temp_max_check() {

}
void light_min_check() {
  
}
void hydrate_min_check() {

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
