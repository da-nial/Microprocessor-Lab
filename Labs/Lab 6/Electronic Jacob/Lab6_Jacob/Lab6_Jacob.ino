// Jacob Setup
String PASSCODE = "1234567";
String inputCode = "";





// LCD Setup
#include <LiquidCrystal.h>

#define RS_PIN 7
#define EN_PIN 6
#define D4_PIN 5
#define D5_PIN 4
#define D6_PIN 3
#define D7_PIN 2

LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);






// Keypad Setup 
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {25, 26, 27, 28};
byte colPins[COLS] {22, 23, 24};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);







// Servo & LEDs Setup
#include <Servo.h>

Servo myservo_1;  // create servo object to control a servo
int pos_1 = 0;    // variable to store the servo position
const byte LED_1_R = 52;
const byte LED_1_G = 53;
bool item1_isFull;


Servo myservo_2;  // create servo object to control a servo
int pos_2 = 0;    // variable to store the servo position
const byte LED_2_R = 50;
const byte LED_2_G = 51;
bool item2_isFull;


Servo myservo_3;  // create servo object to control a servo
int pos_3 = 0;    // variable to store the servo position
const byte LED_3_R = 48;
const byte LED_3_G = 49;
bool item3_isFull;


Servo myservo_4;  // create servo object to control a servo
int pos_4 = 0;    // variable to store the servo position
const byte LED_4_R = 46;
const byte LED_4_G = 47;
bool item4_isFull;






void setup() {
  // put your setup code here, to run once:

  // LCD Start
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);

  // Servo attachment & LED setup
  myservo_1.attach(13, 1000, 2000);  // attaches the servo on pin 9 to the servo object
  pinMode(LED_1_R, OUTPUT);
  pinMode(LED_1_G, OUTPUT);
  digitalWrite(LED_1_R, HIGH);
  digitalWrite(LED_1_G, LOW);
  item1_isFull = false;

  myservo_2.attach(12, 1000, 2000);  // attaches the servo on pin 9 to the servo object
  pinMode(LED_2_R, OUTPUT);
  pinMode(LED_2_G, OUTPUT);
  digitalWrite(LED_2_R, HIGH);
  digitalWrite(LED_2_G, LOW);
  item2_isFull = false;

  myservo_3.attach(11, 1000, 2000);  // attaches the servo on pin 9 to the servo object
  pinMode(LED_3_R, OUTPUT);
  pinMode(LED_3_G, OUTPUT);
  digitalWrite(LED_3_R, HIGH);
  digitalWrite(LED_3_G, LOW);
  item3_isFull = false;

  myservo_4.attach(10, 1000, 2000);  // attaches the servo on pin 9 to the servo object
  pinMode(LED_4_R, OUTPUT);
  pinMode(LED_4_G, OUTPUT);
  digitalWrite(LED_4_R, HIGH);
  digitalWrite(LED_4_G, LOW);
  item4_isFull = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.waitForKey();

  if (key == '#'){
    if (inputCode == PASSCODE){
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.print("Correct Passcode!");
      lcd.setCursor(0, 1);
      lcd.print("Any Key to Back");
      lcd.setCursor(0, 0);
      
      digitalWrite(LED_1_R, LOW);
      digitalWrite(LED_1_G, LOW);
      myservo_1.write(0);
      delay(500);
      item1_isFull = true;

      digitalWrite(LED_2_R, LOW);
      digitalWrite(LED_2_G, LOW);
      myservo_2.write(0);
      delay(500);
      item2_isFull = true;
      
      digitalWrite(LED_3_R, LOW);
      digitalWrite(LED_3_G, LOW);
      myservo_3.write(0);
      delay(500);
      item3_isFull = true;
      
      
      digitalWrite(LED_4_R, LOW);
      digitalWrite(LED_4_G, LOW);
      myservo_4.write(0);
      delay(500);
      item4_isFull = true;


      key = keypad.waitForKey();
      
      digitalWrite(LED_1_R, LOW);
      digitalWrite(LED_1_G, HIGH);

      digitalWrite(LED_2_R, LOW);
      digitalWrite(LED_2_G, HIGH);

      digitalWrite(LED_3_R, LOW);
      digitalWrite(LED_3_G, HIGH);

      digitalWrite(LED_4_R, LOW);
      digitalWrite(LED_4_G, HIGH);
    }
    
    else if (inputCode == "11"){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Item 11 Selected");
      
      digitalWrite(LED_1_R, HIGH);
      digitalWrite(LED_1_G, LOW);
      
      myservo_1.write(180);
      delay(1500);
      myservo_1.write(90); 
      
      item1_isFull = false;
    }
    else if (inputCode == "12"){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Item 12 Selected");
      
      digitalWrite(LED_2_R, HIGH);
      digitalWrite(LED_2_G, LOW);
      
      myservo_2.write(180);
      delay(1500);
      myservo_2.write(90); 
      
      item2_isFull = false;
    }
    else if (inputCode == "21"){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Item 21 Selected");
      
      digitalWrite(LED_3_R, HIGH);
      digitalWrite(LED_3_G, LOW);

      myservo_3.write(180);
      delay(1500);
      myservo_3.write(90); 
      
      item3_isFull = false;
    }
    else if (inputCode == "22"){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Item 22 Selected");
      
      digitalWrite(LED_4_R, HIGH);
      digitalWrite(LED_4_G, LOW);

      myservo_4.write(180);
      delay(1500);
      myservo_4.write(90); 
      
      item4_isFull = false;
    }
    else{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Invalid Option!");
      delay(1500);
    }
      inputCode = "";
      lcd.setCursor(0, 0);
      lcd.clear();

  }
  else if (key == '*'){
    inputCode = "";
    lcd.clear();
  }
  else{
    inputCode += key;
    lcd.print(key);
  }

}
