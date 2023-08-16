#include <SPI.h>

#define MESSAGE_MAX 20
#define SS1 45
#define SS2 46


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Master starting...");

  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Sending sentence <Hello World!> to ARD2");
  sendStr("Hello World!", SS1);

  Serial.println("Sending sentence <Hi!> to ARD3");
  sendStr("Hi!", SS2);
  delay(500);
}


void sendStr(String data, int SS_pin){
  // take the SS pin low to select the chip:
  digitalWrite(SS_pin, LOW);
  delay(100);
  //  send the data via SPI:
  char data_arr[data.length() + 1];
  data.toCharArray(data_arr, data.length() + 1);
  for (int i = 0; i < data.length() + 1; i++){
    SPI.transfer(data_arr[i]);
    delay(100);
  }
  // take the SS pin high to de-select the chip:
  digitalWrite(SS_pin, HIGH);
  delay(100);
  Serial.println("Data Sent!");
}


void sendInt(int data, int SS_pin){
  // take the SS pin low to select the chip:
  digitalWrite(SS_pin, LOW);
  delay(100);
  //  send in the address and value via SPI:
  SPI.transfer(data);
  delay(100);
  // take the SS pin high to de-select the chip:
  digitalWrite(SS_pin, HIGH);
  Serial.println("Data Sent!");
}
