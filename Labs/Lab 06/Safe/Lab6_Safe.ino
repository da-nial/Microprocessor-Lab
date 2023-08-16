// LCD Setup
#include <LiquidCrystal.h>

#define RS_PIN 11
#define EN_PIN 10
#define D4_PIN 9
#define D5_PIN 8
#define D6_PIN 7
#define D7_PIN 6


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

byte rowPins[ROWS] = {26, 27, 28, 29};
byte colPins[COLS] {22, 23, 24, 25};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);




// LED Setup
const byte LED_RED = 52;
const byte LED_GREEN = 51;



// Buzzer Setup
const byte BUZZER = 53;



// Servo Setup
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position



// Safe configurations
String PASSCODE = "1234"; // CORRECT CODE
int state; // 0 for closed, 1 for open, 2 for open/ main display, 3 for menu, 4 for changing passcode, 5 for changing timer
long max_openning = 10000; // Maximum amount of time im milliseconds that safe can stay open

String inputCode = ""; // input code of user, maximum 4 characters
unsigned long delayStart = 0; // the time delay started

void setup() {
  // put your setup code here, to run once:
  
  // Start the timer
//  delayStart = millis();
  state = 0;

  // LCD Start
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Closed!");

  // LED setup
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);

  // Buzzer setup
  pinMode(BUZZER, OUTPUT);

  // Servo attachment
  myservo.attach(13, 1000, 2000);  // attaches the servo on pin 9 to the servo object
}


void loop() {
  // put your main code here, to run repeatedly:
  
  // check if delay has timed out after 10secs == 10000ms
  if (state > 0 && ((millis() - delayStart) >= 10000)){
    closeDoor();
    state = 0;
  }

  // Update the timer value on screen, if necessary.
  if (state == 1){
    lcd.setCursor(6, 1);
    String time_spent_open = String((millis() - delayStart) / 1000);
    lcd.print(time_spent_open);
  }

  char key = keypad.getKey();

  if (key){
    if (key == '='){
      if (state == 0){
        if (inputCode == PASSCODE){ // Correct Input
            openDoor();
            state = 1;
          }
          else { // Incorrect Input
            lcd.clear();
            lcd.print("Wrong Password!");
          }
        
      }
      else if (state == 1){
        // In Main Display
        // Nothing
      }
      
      else if (state == 2){
        // In Menu
        if (inputCode == "1"){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Set New Passcode");
          state = 3;
        }
        else if (inputCode == "2"){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter New Timer");
          lcd.setCursor(0, 1);
          lcd.print("in seconds ");
          state = 4;
        }
      }
      else if (state == 3){
        // In changing passcode
        changePasscode();
        state = 1;
      }
      else if (state == 4){
        changeTimer();
      }
      inputCode = "";
    }
    else if (key == '*'){
      if (state == 1){
        showMenu();
        state = 2;
      }
    }
    else if (key == '/'){
      closeDoor();
      state = 0;
    }
    else if (key == 'C'){
      inputCode = "";
    }
    else{
      inputCode += key;
      lcd.setCursor(12, 1);
      lcd.print(inputCode);

    }
  }
}



void openDoor(){
  lcd.clear();
  lcd.print("Correct Password!");
  
  myservo.write(180);
  delay(500);
  
  delayStart = millis();
  
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);
    
  lcd.print("Opened");
  lcd.setCursor(0, 1);
  String time_spent_open = String((millis() - delayStart) / 1000);
  String time_allowed_open = String(max_openning / 1000);
  lcd.print("Spent " + time_spent_open + " / " + time_allowed_open);
}

void closeDoor(){
  myservo.write(0);
  delay(500);

  // Turn the LED RED & Buzzer
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);

  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);

  // Change the state to closed, and restart the timer
  delayStart = millis();

  // Update the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Closed");
}

void showMenu(){
  lcd.clear();
  lcd.print("Set Passcode: 1");
  lcd.setCursor(0, 1);
  lcd.print("Set Timer: 2");
  inputCode = "";
}

void changePasscode(){
  PASSCODE = inputCode;
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Passcode Changed!");
}

void changeTimer(){
  max_openning = inputCode.toInt() * 1000;
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Timer Changed!");
  
  state = 1;
}
