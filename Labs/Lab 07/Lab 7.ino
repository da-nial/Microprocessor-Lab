// LCD Setup
#include <LiquidCrystal.h>

#define RS_PIN 13
#define EN_PIN 12
#define D7_PIN 11
#define D6_PIN 10
#define D5_PIN 9
#define D4_PIN 8

LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);


// Keypad Setup 
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] {26, 27, 28, 29};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);


// LED Setup
const byte LED1 = 4;
const byte LED2 = 5;
const byte LED3 = 6;
const byte LED4 = 7;


// Washing Machine configurations
#include <Wire.h>
#define DEV_ADDR 0b1010000 
int state; // 0 for idle, 1 for working.
int current_mode = 0; // Defualt mode is set to 1.
int working_time[4] = {6, 6, 6, 6}; // Each element shows the time needed for each working mode. default is set to 6 seconds.
String input = "";

unsigned long delayStart = 0; // the time delay started

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Starting...");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Loading...");
  
  state = 0;
  current_mode = eepromRead("mode", -1);
  if (current_mode < 0 || current_mode > 3){
    current_mode = 0;
    eepromWrite(0, "mode", -1);
    eepromWrite(working_time[0], "time", 0);
    eepromWrite(working_time[1], "time", 1);
    eepromWrite(working_time[2], "time", 2);
    eepromWrite(working_time[3], "time", 3);
  }
  else{
    working_time[0] = eepromRead("time", 0);
    working_time[1] = eepromRead("time", 1);
    working_time[2] = eepromRead("time", 2);
    working_time[3] = eepromRead("time", 3);
  }
  delay(500); // Wait for writing in the eeprom to finnish.  

  // LCD Start
  lcd.begin(16, 2);
  updateLCD();
  
  // LED setup
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
}


void loop() {
  // put your main code here, to run repeatedly:
  if (state == 1){
    // check if delay has timed out after 6secs == 10000ms
    if ((millis() - delayStart) >= (working_time[current_mode] * 1000)){
      stopWorking();
    }
    // Update the timer value on screen, if necessary.
    else{
      lcd.setCursor(4, 1);
      String time_spent = String((millis() - delayStart) / 1000);
      String working_time_str = String(working_time[current_mode]);
      lcd.print(time_spent + " / " + working_time_str); // WHY THE FUCKKKK DOES IT ADD THREE ZEROS????
    }
  }

  char key = keypad.getKey();

  if (key){
    if (key == '+'){
      if (state == 0){
        Serial.println("+ Pressed");
        startWorking();
        input = "";
      }
    }
    else if (key == '-'){
      if (state == 1){
        stopWorking();
        input = "";
      }
    }
    else if (key == '/'){
      int newWorkingTime = (input.substring(0, 2)).toInt();
      changeWorkingTime(newWorkingTime);
      input = "";
    }
    else if (key == '*'){
      int newMode = (input.substring(0, 1)).toInt();
      changeMode(newMode);
      input = "";
    }
    else if (key == 'C'){
      reset();
      input = "";
    }
    else{
      input += key;
      lcd.setCursor(12, 1);
      lcd.print(input);
    }
  }
}

void eepromWrite(int data, String write_t, int mode){
  Serial.println("For Mode " + String(mode) + " Writing " + String(data) + " To Change " + write_t);
  uint16_t mem_addr;
  if (write_t == "mode"){
    mem_addr = 0x0000; 
  }
  else if (write_t == "time"){
    switch (mode){
      case 0:
        mem_addr = 0x0001;
        break;
      case 1:
        mem_addr = 0x0002;
        break;
      case 2: 
        mem_addr = 0x0003;
        break;
       case 3:
        mem_addr = 0x0004;
        break;
    }
  }
  Wire.beginTransmission(DEV_ADDR);
  Wire.write((uint8_t)((mem_addr & 0xFF00) >> 8));
  Wire.write((uint8_t)((mem_addr & 0x00FF) >> 0));
  Wire.write(data);
  Wire.endTransmission();
  delay(300);
  Serial.println("Writing Done");
}

int eepromRead(String read_t, int mode){
  Serial.println("For Mode " + String(mode) + " Reading, To Change " + read_t);
  int readData;
  uint16_t mem_addr;
  if (read_t == "mode"){
    mem_addr = 0x0000; 
  }
  else if (read_t == "time"){
    switch (mode){
      case 0:
        mem_addr = 0x0001;
        break;
      case 1:
        mem_addr = 0x0002;
        break;
      case 2:
        mem_addr = 0x0003;
        break;
       case 3:
        mem_addr = 0x0004;
        break;
    }
  }
  Wire.beginTransmission(DEV_ADDR);
  Wire.write((uint8_t)((mem_addr & 0xFF00) >> 8));
  Wire.write((uint8_t)((mem_addr & 0x00FF) >> 0));
  Wire.endTransmission();
  Wire.requestFrom(DEV_ADDR, 1);
  readData = Wire.read();
  delay(300);

  Serial.println("Read Data is " + String(readData));
  return readData;
}

void updateLCD(){
  if (state == 0){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mode: " + String(current_mode) + " Idle");
    lcd.setCursor(0, 1);
    lcd.print("+ to Start");
  }
  else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mode: " + String(current_mode) + " Working");    
  }
}


void startWorking(){
  state = 1;
  updateLCD();
  delayStart = millis();
  
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  switch (current_mode){
    case 0:
      digitalWrite(LED1, HIGH);
      break;

     case 1:
      digitalWrite(LED2, HIGH);
      break;
      
     case 2:
      digitalWrite(LED3, HIGH);
      break;

     case 3:
      digitalWrite(LED4, HIGH);
      break;
  }
  
  lcd.setCursor(4, 1);
  String time_spent_open = String((millis() - delayStart) / 1000);
  lcd.print(time_spent_open + " / " + String(working_time[current_mode]));
}

void stopWorking(){
  state = 0; // change state back to idle
  updateLCD();

  // Turn all the LEDs on.
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
}


void changeMode(int newMode){
  current_mode = newMode;
  eepromWrite(newMode, "mode", -1);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("New Mode: " + String(newMode));
  
  delay(1000);

  updateLCD();
}

void changeWorkingTime(int newWorkingTime){
  working_time[current_mode] = newWorkingTime;
  eepromWrite(newWorkingTime, "time", current_mode);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time of mode" + String(current_mode));
  lcd.setCursor(0, 1);
  lcd.print("Is: " + String(newWorkingTime));

  delay(1000);
  updateLCD();
}

void reset(){
  state = 0; // 0 for idle, 1 for working.
  stopWorking();
  current_mode = 0; // Defualt mode is set to 1.
  eepromWrite(0, "mode", -1);
  for (int i = 0; i < 4; i++){
    working_time[i] = 6;
    eepromWrite(6, "time", i);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RESET COMPLETE");
  
  delay(1000);
  updateLCD();
}
