#include <SPI.h>

#define BUFFER_SIZE 100

//volatile int i = 0;
//byte dataReceived[BUFFER_SIZE];

uint8_t receivedData;
boolean isReceived;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  pinMode(SS, INPUT_PULLUP);
  pinMode(MISO, OUTPUT);
//  pinMode(SCK, INPUT);

  digitalWrite(MISO,LOW);
  isReceived = false;

  SPCR |= _BV(SPE);
  SPI.attachInterrupt(); // allows SPI interrupt
}

void loop() {
  // put your main code here, to run repeatedly:
//  if (i == 11){
//    char sentence[12];
//    for (int j = 0; j < 12; j++){
//      sentence[j] = (char) dataReceived[i];
//    }
//    Serial.println(sentence);
//    Serial.println("=================");
//    i = 0;
//  }
    if (isReceived){
      Serial.println(receivedData);
    }
    delay(50);
}


//ISR (SPI_STC_vect) {
//  dataReceived[i++] = SPDR;
//}


ISR (SPI_STC_vect){
  receivedData = SPDR; 
  isReceived = true;
}
