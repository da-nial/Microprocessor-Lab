#include <SPI.h>

#define BUFFER_SIZE 20

int i = 0;

char receivedData[BUFFER_SIZE] = {'1'};
boolean isReceived;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MISO, OUTPUT);

  digitalWrite(MISO,LOW);
  isReceived = false;

  SPCR |= _BV(SPE);
  SPI.attachInterrupt(); // allows SPI interrupt
}

void loop() {
  // put your main code here, to run repeatedly:
  if (receivedData[i - 1] == '\0' && i != 0){
    Serial.println(receivedData);
    Serial.println("=================");
    i = 0;
    delay(50);
  }
}


ISR (SPI_STC_vect){
  receivedData[i++] = (char) SPDR; 
  isReceived = true;
}
