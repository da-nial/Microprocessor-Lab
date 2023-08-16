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
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
String input = "";


// LCD Setup
#include <LiquidCrystal.h>

#define RS 10
#define E 9
#define D4 8
#define D5 7
#define D6 6
#define D7 5

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

// Servo Setup
#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
int pos1 = 0;    // variable to store the servo position
int step1 = 45;  // Servo motor step, after each iteration

Servo myservo2;  // create servo object to control a servo
int pos2 = 0;    // variable to store the servo position
int step2 = 45;  // Servo motor step, after each iteration

Servo myservo3;  // create servo object to control a servo
int pos3 = 0;    // variable to store the servo position
int step3 = 45;  // Servo motor step, after each iteration

// SPI Setup
#include <SPI.h>

#define MESSAGE_MAX 20
#define SS1 45
#define SS2 46

// Reaction Settings
int duration = 50;
int threshTemp = 155; // Temperature threshhold
int roomTemp = 25;
int max_q = 3; // Maximum q
int temp1, temp2, temp3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Temperature controller starting...");
  
  // LCD Start
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Duration:" + String(duration) + "ms");
  lcd.setCursor(0, 1);
  lcd.print("NewDuration:");

  // Temperature Setup
  temp1 = 30;
  temp2 = 35;
  temp3 = 37;

  // Servo attachment
  myservo1.attach(13, 1000, 2000);  // attaches the first servo on pin 13 to the servo object
  myservo2.attach(12, 1000, 2000);  // attaches the second servo on pin 12 to the servo object
  myservo3.attach(11, 1000, 2000);  // attaches the third servo on pin 11 to the servo object


  // SPI
  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop() {
  // put your main code here, to run repeatedly:
  reaction1();
  reaction2();
  reaction3();

  if ((temp1 > threshTemp) || (temp2 > threshTemp) || (temp3 > threshTemp)){
    // Notify other Arduinos to stop their work
    Serial.println("Sending Alarm to SS1");
    sendInt(1, SS1);
    delay(25);
    
    Serial.println("Sending Alarm to SS2");
    sendInt(1, SS2);
    delay(25);
  }
  else {
    // Send 0 to other arduinos, meaning everything is fine
    sendInt(0, SS1);
    delay(25);
    sendInt(0, SS2);
    delay(25);
  }

  char key = keypad.getKey();
  if (key){
    Serial.println("New Key: " + String(key));
    if (key == '='){
      duration = input.toInt();
      input = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Duration:" + String(duration) + "ms");
      lcd.setCursor(0, 1);
      lcd.print("NewDuration:");
    }
    else{
      input += key;
      lcd.print(key);
    }
  }

  Serial.println();
  delay(duration);
}

// Do Reaction 1, Update Temperature and Servo Motor Position for Reaction 1
void reaction1(){
  // generating energy
  double q = ((double) pos1 / 180) * max_q;
  temp1 = temp1 + temp1 * q;
  
  // releasing energy
  if (temp1 > roomTemp){
    temp1 -= ((double) (temp1 - roomTemp) / 100) * 30;
  }
  Serial.println("Reaction 1 Temperature: " + String(temp1));
  
  if (temp1 > threshTemp){
    Serial.println("    Reaction 1 Temperature too High! Decreasing Servo Angle");
    pos1 = 0;
  }
  else{
    Serial.println("    Reaction 1 Temperature OK, Increasing Servo Angle");
    pos1 = pos1 + step1;
    if (pos1 > 180){
      pos1 = 180;
    }
  }
  myservo1.write(pos1);
}

// Update Temperature and Servo Motor Position for Reaction 2
void reaction2(){
  // generating energy
  double q = ((double) pos2 / 180) * max_q;
  temp2 = temp2 + temp2 * q;
  
  // releasing energy
  if (temp2 > roomTemp){
    temp2 -= ((double) (temp2 - roomTemp) / 100) * 30;
  }
  Serial.println("Reaction 2 Temperature: " + String(temp2));

  if (temp2 > threshTemp){
    Serial.println("    Reaction 2 Temperature too High! Decreasing Servo Angle");
    pos2 = 0;
  }
  else{
    Serial.println("    Reaction 2 Temperature OK, Increasing Servo Angle");
    pos2 = pos2 + step2;
    if (pos2 > 180){
      pos2 = 180;
    }
  }  

  myservo2.write(pos2);
}

// Update Temperature and Servo Motor Position for Reaction 3
void reaction3(){
  // generating energy
  double q = ((double) pos3 / 180) * max_q;
  temp3 = temp3 + temp3 * q;
  // releasing energy
  if (temp3 > roomTemp){
    temp3 -= ((double) (temp3 - roomTemp) / 100) * 30;
  }
  Serial.println("Reaction 3 Temperature: " + String(temp3));

  if (temp3 > threshTemp){
    Serial.println("    Reaction 3 Temperature too High! Decreasing Servo Angle");
    pos3 = 0;
  }
  else{
    Serial.println("    Reaction 3 Temperature OK, Increasing Servo Angle");
    pos3 = pos3 + step3;
    if (pos3 > 180){
      pos3 = 180;
    }
  }
  
  myservo3.write(pos3);
}

// Send an integer to the chosen slave
void sendInt(int data, int SS_pin){
  // take the SS pin low to select the chip:
  digitalWrite(SS_pin, LOW);
  delay(100);
  //  send in the address and value via SPI:
  SPI.transfer(data);
  delay(100);
  // take the SS pin high to de-select the chip:
  digitalWrite(SS_pin, HIGH);
}
