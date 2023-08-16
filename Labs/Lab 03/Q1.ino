#include <LiquidCrystal.h>

#define RS_PIN 13
#define EN_PIN 12
#define D4_PIN 11
#define D5_PIN 10
#define D6_PIN 9
#define D7_PIN 8


LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

int cursorX = 0;
int cursorY = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(cursorX, cursorY);
  
  lcd.print("Danial Hamdi");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  lcd.scrollDisplayRight();
  cursorX++;
  
  if (cursorX == 5){
    cursorX = 0;
    cursorY++;
    lcd.clear();
    lcd.setCursor(cursorX, cursorY % 2);
    lcd.print("Danial Hamdi");
  }
  delay(1000);
}
