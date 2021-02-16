#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};

byte rowPins[ROWS] = {23, 24, 25, 26};
byte colPins[COLS] {28, 29, 30, 31};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String inputAngle = "";

#include <Servo.h>

Servo myservo;  // create servo object to control a servo


void setup() {
  myservo.attach(13, 1000, 2000);  // attaches the servo on pin 9 to the servo object

  Serial.begin(9600);
}

void loop() {
  char key = keypad.waitForKey();

  if (key == '='){
      int angle = inputAngle.toInt();
//      angle = map(angle, 0, 180, -90, 90);
      myservo.write(angle);                  // sets the servo position according to the scaled value
      delay(2000);                           // waits for the servo to get there
      
  }
    else if (key == 'C'){
      inputAngle = "";
    }
    else {
      inputAngle += key;
   }
}
