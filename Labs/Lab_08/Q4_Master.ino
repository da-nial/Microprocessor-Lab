#include <SPI.h>

#define MESSAGE_MAX 20

#define SS1 45
#define SS2 46

int LDR_OUT, LM35_OUT;
int light, temperature;

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
  Serial.print("Sending Lights Intensity: ");
  LDR_OUT = analogRead(A0);
  light = map(LDR_OUT, 0, 684, 0, 101);
  Serial.println(light);
  sendInt(light, SS1);
  delay(500);

  Serial.print("Sending Temperature: ");
  LM35_OUT = analogRead(A1);
  temperature = map(LM35_OUT, 0, 1023, 0, 500);
  Serial.println(temperature);
  sendInt(temperature, SS2);
  delay(500);
}


void sendStr(String data, int SS_pin){
  // take the SS pin low to select the chip:
  digitalWrite(SS_pin, LOW);
  delay(100);
  //  send in the address and value via SPI:
  //  char data_arr[MESSAGE_MAX];
  //  strcpy(data_arr, data);
  SPI.transfer(data.c_str(), data.length() + 1);
  delay(100);
  // take the SS pin high to de-select the chip:
  digitalWrite(SS_pin, HIGH);
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
}
