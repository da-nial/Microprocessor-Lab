const byte LED1 = A8;
const byte LED2 = A4;
const byte LED3 = A5;
const byte LED4 = A6;
const byte LED5 = A7;
const byte LED6 = A3;
const byte LED7 = A2;
const byte LED8 = A1;
const byte LED9 = A0;

byte receivedByte;


void setup() {
  // put your setup code here, to run once:
  Serial2.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial2.available() > 0){
    receivedByte = Serial2.read();

    switch (receivedByte) {
      case '1':
        digitalWrite(LED1, HIGH);
        break;

      case '2':
        digitalWrite(LED2, HIGH);
        break;

      case '3':
        digitalWrite(LED3, HIGH);
        break;

      case '4':
        digitalWrite(LED4, HIGH);
        break;

      case '5':
        digitalWrite(LED5, HIGH);
        break;

      case '6':
        digitalWrite(LED6, HIGH);
        break;

      case '7':
        digitalWrite(LED7, HIGH);
        break;

      case '8':
        digitalWrite(LED8, HIGH);
        break;

      case '9':
        digitalWrite(LED9, HIGH);
        break;

      case 'C':
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);
        digitalWrite(LED6, LOW);
        digitalWrite(LED7, LOW);
        digitalWrite(LED8, LOW);
        digitalWrite(LED9, LOW);
        break;
    }
  }

}
