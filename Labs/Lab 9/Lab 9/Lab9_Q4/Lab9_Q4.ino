#include "pitches.h"
#include "odeToJoy.h"


const int buttonPin = 22;
int buttonState = 0;

const int sounderPin = 5;

float scale;


void setup() {
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
      for(int locationNote = 0; locationNote < sizeof(melody)/sizeof(int); locationNote++){
        if(digitalRead(buttonPin) == LOW){
            break;
        }
        else{
          scale = analogRead(A1)/512.0;
          int noteDuration = (int) (0.5 *  1000/noteDurations[locationNote]);
          tone(sounderPin, (int) (melody[locationNote] * scale), noteDuration);
          delay((int)(noteDuration * 1.2));
        }
      }
  }
  if(buttonState == LOW){
    noTone(sounderPin);
  }

}
