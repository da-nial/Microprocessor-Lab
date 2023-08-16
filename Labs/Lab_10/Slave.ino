// SPI Setup
#include <SPI.h>

#define BUFFER_SIZE 100

uint8_t receivedData;
boolean isReceived;


// LED Setup
#define LED_GREEN 44
#define LED_RED 45


// Buzzer Setup
#define BUZZER 46


void setup() {
  // put your setup code here, to run once:
  // Serial Setup
  Serial.begin(9600);

  // SPI Setup
  pinMode(MISO, OUTPUT);
  digitalWrite(MISO,LOW);
  isReceived = false;
  SPCR |= _BV(SPE);
  SPI.attachInterrupt(); // allows SPI interrupt

  // LED Setup
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);

  // Buzzer setup
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (isReceived){
      Serial.println(receivedData);
      if (receivedData == 1){
          alarm();
      }
      else if (receivedData == 0){
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_RED, LOW);
      }
    }
    // isReceived = False?
    delay(50);
}


ISR (SPI_STC_vect){
  receivedData = SPDR; 
  isReceived = true;
}

void alarm(){
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);
  
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);
}
