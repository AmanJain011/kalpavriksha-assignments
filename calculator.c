#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int operatorStackSize = 0;
int numberStackSize = 0;

int isDigit(char character);
int isSpace(char character);
int isOperator(char character);
int isValidCharacter(char character);
int validateExpression(const char *string);
int getStringLength(const char *string);
char *readDynamicString(const char *prompt);
int operatorPrecedence(char operator);
int evaluateExpression(const char *expression, int *result);

int main() {
  while (1){
    char *expression = readDynamicString("Enter a expression: ");
    if(expression == NULL){
      continue;
    }
    int result;
    if(evaluateExpression(expression, &result)){
      free(expression);
      continue;
    }

    printf("Result is: %d\n", result);
    free(expression);
  }
  return 0;
}

int isDigit(char character) {
  return character >= '0' && character <= '9'; 
}

int isSpace(char character) {
  return character == ' ' || character == '\t';
}

int isOperator(char character){
  if(character == '+' || character == '-' || character == '/' || character == '*'){
    return 1;
  }
  return 0;
}

int isValidCharacter(char character){
  if(isDigit(character) || isOperator(character)){
    return 1;
  }
  return 0;
}

int getStringLength(const char *string){
  if (string == NULL) {
    return 0;
  }

  int currentIndex = 0;
  while(string[currentIndex] != '\0'){
    currentIndex++;
  }
  return currentIndex;
}

int validateExpression(const char *string) {
  int stringLength = getStringLength(string);
  
  if (stringLength == 0) {
    printf("Error: Empty input.\n");
    return 1;
  }
  
  if (isOperator(string[0]) || isOperator(string[stringLength - 1])) {
    printf("Error: Expression cannot start or end with an operator.\n");
    return 1;
  }

  for (int i = 0; i < stringLength - 1; i++) {
    if (isOperator(string[i]) && isOperator(string[i + 1])) {
      printf("Error: Consecutive operators are not allowed.\n");
      return 1;
    }
  }

  for (int i = 0; i < stringLength; i++) {
    if (!isValidCharacter(string[i])) {
      printf("Error: Invalid input.\n");
      return 1;
    }
  }

  return 0;
}

char *readDynamicString(const char *prompt){
  printf("%s", prompt);
  operatorStackSize = 0;

  char *string = NULL;
  int input, counter = 0;
  while ((input = getchar()) != '\n'){
    char character = (char)input;

    if(isSpace(character)){
      continue;
    }

    if(isOperator(character)){
      operatorStackSize++;
    }

    counter++;
    char *temp = realloc(string, (counter + 1)*sizeof(char));
    if (temp == NULL) {
      free(string);
      printf("Error: Memory allocation failed.\n");
      return NULL;
    }
    string = temp;
    string[counter-1] = character;
  }

  if(string != NULL){
    string[counter] = '\0';
  }
  
  if(validateExpression(string)){
    free(string);
    return NULL;
  }
  
  numberStackSize = operatorStackSize + 1;
  return string;
}

int operatorPrecedence(char operator) {
  if (operator== '*' || operator== '/')
    return 2;
  if (operator== '+' || operator== '-')
    return 1;
  return 0;
}

int processOperator(int *numberStack, int *numberStackTop, char *operatorStack, int *operatorStackTop) {
  int rightOperand = numberStack[(*numberStackTop)--];
  int leftOperand = numberStack[(*numberStackTop)--];
  char operator = operatorStack[(*operatorStackTop)--];
  int result;
  switch (operator) {
    case '+':
      result = leftOperand + rightOperand;
      break;
    case '-':
      result = leftOperand - rightOperand;
      break;
    case '*':
      result = leftOperand * rightOperand;
      break;
    case '/':
      if (rightOperand == 0) {
        printf("Error: Division by zero.\n");
        return 1;
      }
      result = leftOperand / rightOperand;
      break;
    default:
      printf("Error: Unsupported operator '%c'.\n", operator);
      return 1;
  }
  numberStack[++(*numberStackTop)] = result;
  return 0;
}

int evaluateExpression(const char *expression, int *result) {
    int numberStack[numberStackSize];
    int numberStackTop = -1;

    char operatorStack[operatorStackSize];
    int operatorStackTop = -1;

    int currentIndex = 0;

    while (expression[currentIndex] != '\0') {
      char character = expression[currentIndex];

      if (isDigit(character)) {
        int currentNumber = 0;
          while (isDigit(character)) {
            currentNumber = currentNumber * 10 + (character - '0');
            character = expression[++currentIndex];
          }
          numberStack[++numberStackTop] = currentNumber;
          continue;
        }

      if(isOperator(character)) {
        while (operatorStackTop != -1 && 
          operatorPrecedence(character) <= operatorPrecedence(operatorStack[operatorStackTop])) {
          int status = processOperator(numberStack, &numberStackTop, operatorStack, &operatorStackTop);
          if(status){
            return 1;
          }
        }
        operatorStack[++operatorStackTop] = character;
      }
      currentIndex++;
    }

    while (operatorStackTop != -1) {
      int status = processOperator(numberStack, &numberStackTop, operatorStack, &operatorStackTop);
      if(status){
        return 1;
      }
    }

    *result = numberStack[numberStackTop];
    return 0;
}
