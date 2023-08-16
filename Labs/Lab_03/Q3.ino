#include <LiquidCrystal.h>

#define RS_PIN 13
#define EN_PIN 12
#define D4_PIN 11
#define D5_PIN 10
#define D6_PIN 9
#define D7_PIN 8


LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};

byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] {26, 27, 28, 29};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String inputExpression = "";

String operand_1;
String operand_2;
char my_operator;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  char key = keypad.waitForKey();

  if (key == '='){
      parser(inputExpression);
      String answer = String(calculate(operand_1, operand_2, my_operator));
      lcd.print(key);
      lcd.print(answer);
      inputExpression = "";
  }
  
   else if (key == 'C'){
      inputExpression = "";
      lcd.clear();
   }

   else{
      inputExpression += key;
      lcd.print(key);
   }

}

double calculate(String operand_1, String operand_2, char my_operator){
  int operand_1_int = operand_1.toInt();
  int operand_2_int = operand_2.toInt();
  
  switch (my_operator){
    case '+':
      return operand_1_int + operand_2_int;
    case '-':
      return operand_1_int - operand_2_int;
    case '*':
      return operand_1_int * operand_2_int;
    case '/':
      return operand_1_int / operand_2_int;
  }
}


void parser(String expression){
  int operatorPos = 0;
  for (int i = 0; i < expression.length(); i++){
    if (
        (expression[i] == '+') || 
        (expression[i] == '-') ||
        (expression[i] == '*') ||
        (expression[i] == '/')
      ){
        operatorPos = i;
        break;
      }
  }
  
  operand_1 = expression.substring(0, operatorPos);
  my_operator = expression.charAt(operatorPos);
  operand_2 = expression.substring(operatorPos + 1, expression.length());
  
}
