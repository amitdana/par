#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 101
int isBalanced(char[], int, int);
int isRegular(char[]);

int isRegular(char line[])
{
    int i;
    int par = 0;
    char parchar;

    for (i = 0; i < strlen(line); i++)
    {
        if (line[i] != ' ')
        {
            if (line[i] == '{' || line[i] == '}')
            {
                par++;
                parchar = line[i];
            }
            else
            {
                return 1;
            }
        }
        if (par > 1)
        {
            return 1;
        }
    }
    if (par == 1)
    {
        if (parchar == '{')
        {
            return 2;
        }
        return 0;
    }
    return 1;
}
int isBalanced(char line[], int comment, int openTotal)
{
    char stack[MAX_LINE];
    int retparams;
    int i = 0;
    int allbalncednocurly = 1;
    int stack_index = 0;
    int balanced = 1;
    for (i = 0; i < strlen(line); i++)
    {
        if (line[i] == '"' && comment == 0)
        {
            i++;
            while (line[i] != '"')
            {
                i++;
            }
        }
        else if (line[i] == '/' && line[i + 1] == '*' && comment == 0)
        {
            comment = 1;
            i++;
        }
        else if (line[i + 1] == '/' && line[i] == '*')
        {
            comment = 0;
        }
        else if (line[i] == '[' || line[i] == '{' || line[i] == '(')
        {
            stack[stack_index] = line[i];
            stack_index++;
            if (line[i] == '{')
            {
                openTotal++;
            }
        }
        else if (stack_index != 0)
        {
            if (line[i] == ']')
            {
                if (stack[stack_index - 1] == '[')
                {
                    stack_index--;
                }
                else
                {
                    allbalncednocurly = 0;
                    balanced = 0;
                }
            }
            else if (line[i] == '}')
            {
                if (stack[stack_index - 1] == '{')
                {
                    stack_index--;
                    openTotal--;
                }
                else
                {
                    balanced = 0;
                }
            }
            else if (line[i] == ')')
            {
                if (stack[stack_index - 1] == '(')
                {
                    stack_index--;
                }
                else
                {
                    allbalncednocurly = 0;
                    balanced = 0;
                }
            }
        }
        else if (line[i] == ']' || line[i] == '}' || line[i] == ')')
        {
            balanced = 0;
            if (line[i] == '}')
            {
                openTotal--;
            }
        }
    }
    retparams = comment;
    if (balanced == 1)
    {
        printf("%d\n",stack_index);
        if (stack_index != 0)
        {
            balanced = 0;
            for (i = 0; i < stack_index; i++)
            {
                if (line[i] == '[' || line[i] == '(')
                {
                    allbalncednocurly = 0;
                }
            }
        }
    }
    retparams += 10 * balanced;
    retparams += 100 * allbalncednocurly;
    retparams += 1000 * openTotal;
    return retparams;
}

int main()
{
   
    char curInput;
    int params;
    int balanced = 1;
    int allbalncednocurly = 1;
    int comment = 0;
    int regular = 1;
    int openTotal = 0;
    char line[MAX_LINE]; 
    int index = 0;
    printf("\n please write your c program here. use ctrl+D\n");
    curInput = getchar();
    while (curInput != EOF)
    {
        if (curInput == '\n')
        {
            line[index] = '\0';
            printf("%s\n ", line);
            {
                regular = isRegular(line);
            }
            if (regular == 1)
            {
                params = isBalanced(line, comment, openTotal);
                comment = params % 10;
                params /= 10;
                balanced = params % 10;
                params /= 10;
                allbalncednocurly = params % 10;
                params /= 10;
                openTotal = params;
                if (balanced == 1)
                {
                    printf("is a balanced line\n");
                }
            }
            if (regular != 1 || balanced == 0)
            {
                printf("is an unbalanced line\n");
            }
            if (regular == 0)
            {
                openTotal--;
            }
            if (regular == 2) 
            {
                openTotal++;
            }
            index = 0;
        }
        else
        {
            line[index] = curInput;
            index++;
        }
        curInput = getchar();
        regular = 1;
    }
    if (allbalncednocurly == 1 && openTotal == 0)
    {
        printf("all text is balanced!\n");
    }
    else
    {
        printf("all text is unbalanced!\n");
    }
    return 0;
}


