#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numberStack[50];
int numberStackTop = -1;
int operatorStack[50];
int operatorStackTop = -1;

int evaluateExpression(char expression[]);
void calculate();
int operatorPrecedence(char operator);
int isDigit(char character);
int isSpace(char character);

int main()
{
    char expression[80];
    int result = 0;
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0';
    if (strlen(expression) == 0)
    {
        printf("Error: Invalid expression.\n");
        return 0;
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
            int number = 0;
            while (isDigit(character))
            {
                number = number * 10 + (character - '0');
                index++;
                if (index < strlen(expression))
                {
                    character = expression[index];
                }
                else
                {
                    break;
                }
            }
            index--;
            if (numberStackTop >= 49)
            {
                printf("Error: Invalid expression.\n");
                exit(0);
            }
            numberStack[++numberStackTop] = number;
        }
        else if (character == '+' || character == '-' || character == '/' || character == '*')
        {
            while (operatorStackTop != -1 && operatorPrecedence(character) <= operatorPrecedence(operatorStack[operatorStackTop]))
            {
                calculate();
            }
            if (operatorStackTop >= 49)
            {
                printf("Error: Invalid expression.\n");
                exit(0);
            }
            operatorStack[++operatorStackTop] = character;
        }
        else if (!isSpace(character))
        {
            printf("Error: Invalid expression.\n");
            exit(0);
        }
    }
    while (operatorStackTop != -1)
    {
        calculate();
    }
    return numberStack[numberStackTop];
}

void calculate()
{
    if (numberStackTop < 1 || operatorStackTop < 0)
    {
        printf("Error: Invalid expression.\n");
        exit(0);
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
            printf("Error: Division by zero.\n");
            exit(0);
        }
        result = leftOperand / rightOperand;
        break;
    default:
        printf("Error: Invalid expression.\n");
        exit(0);
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
