#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int index = 0;
char receivedAngle[3];

void setup() {
  myservo.attach(13, 1000, 2000);  // attaches the servo on pin 9 to the servo object

  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0) {

    char inputChar = Serial.read();
    
    if (inputChar == '='){
        int angle = atoi(receivedAngle);
  //      angle = map(angle, 0, 180, -90, 90);
        myservo.write(angle);                  // sets the servo position according to the scaled value
        delay(2000);                           // waits for the servo to get there

        index = 0;
    }
      else {
         receivedAngle[index] = inputChar;
         index++;
     }

  }
}
