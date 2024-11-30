#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numberStack[50];
int nSTop = -1;
int operatorStack[50];
int opSTop = -1;

int evaluateExp(char exp[]);
void calculate();
int operatorPrecedence(char operator);
int custom_isdigit(char ch);
int custom_isspace(char ch);

int main()
{
    char exp[80];
    int result = 0;
    fgets(exp, sizeof(exp), stdin);
    exp[strcspn(exp, "\n")] = '\0';
    if (strlen(exp) == 0)
    {
        printf("Error: Invalid expression.\n");
        return 0;
    }
    result = evaluateExp(exp);
    printf("%d\n", result);
    return 0;
}

int evaluateExp(char exp[])
{
    for (int i = 0; i < strlen(exp); i++)
    {
        char ch = exp[i];
        if (custom_isdigit(ch))
        {
            int num = 0;
            while (custom_isdigit(ch))
            {
                num = num * 10 + (ch - '0');
                i++;
                if (i < strlen(exp))
                {
                    ch = exp[i];
                }
                else
                {
                    break;
                }
            }
            i--;
            if (nSTop >= 49)
            {
                printf("Error: Invalid expression.\n");
                exit(0);
            }
            numberStack[++nSTop] = num;
        }
        else if (ch == '+' || ch == '-' || ch == '/' || ch == '*')
        {
            while (opSTop != -1 && operatorPrecedence(ch) <= operatorPrecedence(operatorStack[opSTop]))
            {
                calculate();
            }
            if (opSTop >= 49)
            {
                printf("Error: Invalid expression.\n");
                exit(0);
            }
            operatorStack[++opSTop] = ch;
        }
        else if (!custom_isspace(ch))
        {
            printf("Error: Invalid expression.\n");
            exit(0);
        }
    }
    while (opSTop != -1)
    {
        calculate();
    }
    return numberStack[nSTop];
}

void calculate()
{
    if (nSTop < 1 || opSTop < 0)
    {
        printf("Error: Invalid expression.\n");
        exit(0);
    }
    int x = numberStack[nSTop--];
    int y = numberStack[nSTop--];
    char op = operatorStack[opSTop--];
    int z;
    switch (op)
    {
    case '+':
        z = y + x;
        break;
    case '-':
        z = y - x;
        break;
    case '*':
        z = y * x;
        break;
    case '/':
        if (x == 0)
        {
            printf("Error: Division by zero.\n");
            exit(0);
        }
        z = y / x;
        break;
    default:
        printf("Error: Invalid expression.\n");
        exit(0);
    }
    numberStack[++nSTop] = z;
}

int operatorPrecedence(char operator)
{
    if (operator== '*' || operator== '/')
        return 2;
    if (operator== '+' || operator== '-')
        return 1;
    return 0;
}

int custom_isdigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

int custom_isspace(char ch)
{
    return ch == ' ' || ch == '\t';
}
