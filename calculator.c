#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numberStack[50];
int numberStackTop = -1;
int operatorStack[50];
int operatorStackTop = -1;

int evaluateExpression(char expression[]);
int processNumber(const char expression[], int index);
void processOperator(char character);
void calculate();
int operatorPrecedence(char operator);
int isDigit(char character);
int isSpace(char character);
void errorHandler(const char *errorMessage);

int main()
{
    char expression[80];
    int result = 0;
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0';
    if (strlen(expression) == 0)
    {
        errorHandler("Error: Invalid expression.\n");
    }
    result = evaluateExpression(expression);
    printf("%d\n", result);
    return 0;
}

int evaluateExpression(char expression[])
{
    for (int index = 0; index < strlen(expression); index++)
    {
        char character = expression[index];
        if (isDigit(character))
        {
            index = processNumber(expression, index);
        }
        else if (character == '+' || character == '-' || character == '/' || character == '*')
        {
            processOperator(character);
        }
        else if (!isSpace(character))
        {
            errorHandler("Error: Invalid expression.\n");
        }
    }
    // Process Remaining Operators
    while (operatorStackTop != -1)
    {
        calculate();
    }
    return numberStack[numberStackTop];
}

int processNumber(const char expression[], int index)
{
    int number = 0;
    char character = expression[index];
    while (isDigit(character))
    {
        number = number * 10 + (character - '0');
        index++;
        character = expression[index];
    }
    index--; // Step back since the loop increments `index` one extra time
    if (numberStackTop >= 49)
    {
        errorHandler("Error: Stack overflow.\n");
    }
    numberStack[++numberStackTop] = number;
    return index;
}

void processOperator(char character)
{
    while (operatorStackTop != -1 && operatorPrecedence(character) <= operatorPrecedence(operatorStack[operatorStackTop]))
    {
        calculate();
    }
    if (operatorStackTop >= 49)
    {
        errorHandler("Error: Stack overflow.\n");
    }
    operatorStack[++operatorStackTop] = character;
}

void calculate()
{
    if (numberStackTop < 1 || operatorStackTop < 0)
    {
        errorHandler("Error: Invalid expression.\n");
    }
    int rightOperand = numberStack[numberStackTop--];
    int leftOperand = numberStack[numberStackTop--];
    char operator= operatorStack[operatorStackTop--];
    int result;
    switch (operator)
    {
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
        if (rightOperand == 0)
        {
            errorHandler("Error: Division by zero.\n");
        }
        result = leftOperand / rightOperand;
        break;
    default:
        errorHandler("Error: Invalid expression.\n");
    }
    numberStack[++numberStackTop] = result;
}

int operatorPrecedence(char operator)
{
    if (operator== '*' || operator== '/')
        return 2;
    if (operator== '+' || operator== '-')
        return 1;
    return 0;
}

int isDigit(char character)
{
    return character >= '0' && character <= '9';
}

int isSpace(char character)
{
    return character == ' ' || character == '\t';
}

void errorHandler(const char *errorMessage)
{
    printf("%s\n", errorMessage);
    exit(EXIT_FAILURE);
}