#include <LiquidCrystal_I2C.h>
#include <DFRobot_DHT11.h>
#include <Servo.h>
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
#define HYDRATE_SENSOR 1
bool humid_start = false;
bool angleReverse = false;
char str1[16], str2[16];
int button1 = HIGH, button1_prev = HIGH;
int button2 = HIGH, button2_prev = HIGH;
int button3 = HIGH, button3_prev = HIGH;
int button4 = HIGH, button4_prev = HIGH;
int button5 = HIGH, button5_prev = HIGH;
int light = 0; // 밝을때 50, 어두울때 10
int hydrate = 0; // 수분 없을 때 100, 있을 때 60
int temp_min = 24, temp_max = 30;
int light_min = 10;
int hydrate_min = 99, hydrate_max = 120;
int angle = 0;
uint64_t sensorClockPreTime, sensorClockNowTime;
uint64_t servoClockPreTime, servoClockNowTime;
Servo sv1, sv2;
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
  sensorClockPreTime = millis();

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Farm v1.0");

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(BUTTON5, INPUT_PULLUP);

  // sv1.deattach(SPRINGCOOLER1);
  // sv2.deattach(SPRINGCOOLER2);

  pinMode(FAN, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(FAN, HIGH);
  digitalWrite(LED, HIGH);
}

void loop() {
  sensorClockNowTime = millis();
  sensors_read();
  environment_check();
  lcd_print();

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

  if(sensorClockNowTime - sensorClockPreTime >= 1000) {
    sensorClockPreTime = sensorClockNowTime;

    light = analogRead(LIGHT_SENSOR);
    hydrate = analogRead(HYDRATE_SENSOR) / 10;
    dht.read(TEMP_HUMID_SENSOR);
  }
}

void environment_check() {
  if(dht.temperature < temp_min || light < light_min) digitalWrite(LED, LOW);
  else                                                digitalWrite(LED, HIGH);

  if(dht.temperature > temp_max) digitalWrite(FAN, LOW);
  else                           digitalWrite(FAN, HIGH);

  if(hydrate < hydrate_min) {
    sv1.write(angle);
    sv2.write(angle);

    if(angleReverse) angle--;
    else angle++;

    if(angle == 0 || angle == 180) angleReverse = !angleReverse;
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
      sprintf(str1, "HYDRATE : %-2d    ", hydrate);
      lcd.setCursor(0, 0);
      lcd.print(str1);

      sprintf(str2, "MIN: %-2d, MAX: %-2d", hydrate_min, hydrate_max);
      lcd.setCursor(0, 1);
      lcd.print(str2);
      break;
  }
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
