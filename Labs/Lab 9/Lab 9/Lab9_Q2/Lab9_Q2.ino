#include "pitches.h"
#include "jingleBells.h"


const int buttonPin = 22;
int buttonState = 0;

const int sounderPin = 5;


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
          int noteDuration = (int) (0.5 *  1000/noteDurations[locationNote]);
          tone(sounderPin, melody[locationNote], noteDuration);
          delay((int)(noteDuration * 1.2));
        }
      }
  }
  if(buttonState == LOW){
    noTone(sounderPin);
  }

}
