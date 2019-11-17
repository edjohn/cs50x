#include <cs50.h>
#include <stdio.h>

int getInput(void)
{
    int userInput = get_int("Height: ");
    if (userInput >= 1 && userInput <= 8)
    {
        return userInput;
    }
    else
    {
        return getInput();
    }
}

int main(void)
{
    int userInput = getInput();
    int n = userInput;
    for (int i = 1; i <= userInput; i++)
    {
        for (int h = n; h > 1; h--)
        {
            printf(" ");
        }
        n -= 1;
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
