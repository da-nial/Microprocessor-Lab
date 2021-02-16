const int led1_pin = 6;
const int led2_pin = 5;
const int led3_pin = 4;
const int led4_pin = 3;
const int led5_pin = 2;
const int led6_pin = 1;
const int led7_pin = 0;


const int input1_pin = 10;
const int input2_pin = 11;
const int input3_pin = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(led1_pin, OUTPUT);
  pinMode(led2_pin, OUTPUT);
  pinMode(led3_pin, OUTPUT);
  pinMode(led4_pin, OUTPUT);
  pinMode(led5_pin, OUTPUT);
  pinMode(led6_pin, OUTPUT);
  pinMode(led7_pin, OUTPUT);

  pinMode(input1_pin, INPUT);
  pinMode(input2_pin, INPUT);
  pinMode(input3_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(input1_pin) == HIGH){
    digitalWrite(led1_pin, HIGH);
    delay(1000);

    digitalWrite(led2_pin, HIGH);
    delay(1000);

    digitalWrite(led3_pin, HIGH);
    delay(1000);

    digitalWrite(led4_pin, HIGH);
    delay(1000);

    digitalWrite(led5_pin, HIGH);
    delay(1000);

    digitalWrite(led6_pin, HIGH);
    delay(1000);

    digitalWrite(led7_pin, HIGH);
    delay(1000);

  }
  else if (digitalRead(input2_pin) == HIGH){
    digitalWrite(led7_pin, HIGH);
    delay(1000);

    digitalWrite(led6_pin, HIGH);
    delay(1000);

    digitalWrite(led5_pin, HIGH);
    delay(1000);

    digitalWrite(led4_pin, HIGH);
    delay(1000);

    digitalWrite(led3_pin, HIGH);
    delay(1000);

    digitalWrite(led2_pin, HIGH);
    delay(1000);

    digitalWrite(led1_pin, HIGH);
    delay(1000);

  }
  else if (digitalRead(input3_pin) == HIGH){
    digitalWrite(led1_pin, LOW);
    digitalWrite(led2_pin, LOW);
    digitalWrite(led3_pin, LOW);
    digitalWrite(led4_pin, LOW);
    digitalWrite(led5_pin, LOW);
    digitalWrite(led6_pin, LOW);
    digitalWrite(led7_pin, LOW);
  }

}
