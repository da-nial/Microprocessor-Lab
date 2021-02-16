#include "pitches.h"
#include "imperialMarch.h"


const int buttonPin = 22;
int buttonState = 0;

const int sounderPin = 5;

float scale;

int tempo = 120;
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int baseNote = (60000 * 4) / tempo;
int divider = 0;


void setup() {
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
      for(int locationNote = 0; locationNote < sizeof(melody) / sizeof(melody[0]); locationNote += 2){
        if(digitalRead(buttonPin) == LOW){
            break;
        }
        else{
          divider = melody[locationNote + 1];
          int noteDuration = (baseNote) / abs(divider);
          if (divider < 0)
            noteDuration = noteDuration * 1.5;
          scale = analogRead(A1)/512.0;
          tone(sounderPin, (int) (melody[locationNote] * scale), noteDuration);
          delay((int)(noteDuration * 1.2));
        }
      }
  }
  if(buttonState == LOW){
    noTone(sounderPin);
  }

}
