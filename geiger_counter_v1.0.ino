// LCD -> Wemos D1 R2
// GND -> GND
// VCC -> 3.3V
// SDA -> SDA/D2
// SCL -> SCL/D1
//
// RadiationD Cajoe V1.1 -> Wemos D1 R2
// GND -> GND
// 5V  -> 5V
// VIN -> D6(GPIO12)

// Arduino IDE esp8266 2.4.2 Version

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 20 chars and 4 line display

#define ONE_MINUTE 60000
#define COUNTDOWN_SECONDS 60

const float cpm_constant = 0.0057;
const int geiger_pin = 12;
unsigned long impulse_counter;
unsigned long previousMillis;
unsigned long countdownMillis;
bool countdownFinished = false;

void impulse() {
  impulse_counter++;
}

void setup() {
  impulse_counter = 0;
  pinMode(geiger_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(geiger_pin), impulse, FALLING);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.home();
  countdownMillis = millis() + ONE_MINUTE;
}

void loop() {
  unsigned long currentMillis = millis();

  if (!countdownFinished) {
    long remainingSeconds = (countdownMillis - currentMillis) / 1000;
    if (remainingSeconds < 0) {
      remainingSeconds = 0;
    }
    char countdownStr[4];
    sprintf(countdownStr, "%2lu", remainingSeconds);
    lcd.setCursor(17, 0);
    lcd.print(countdownStr);

    if (remainingSeconds == 0) {
      countdownFinished = true;
    }
  }

  if (currentMillis - previousMillis > ONE_MINUTE) {
    previousMillis = currentMillis;

    char buffer[10];
    sprintf(buffer, "CPM: %d", impulse_counter);
    
    lcd.setCursor(2, 1);
    lcd.print(buffer);
    lcd.setCursor(0, 2);
    lcd.print("uSv/h:  ");
    lcd.print(impulse_counter * cpm_constant, 4);


    countdownFinished = false;
    countdownMillis = millis() + ONE_MINUTE;
    impulse_counter = 0;
  }
}
