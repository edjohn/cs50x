#include <stdio.h>
#include <cs50.h>
#include <math.h>

float getChange(void)
{
    float change = get_float("Change: ");
    if (change >= 0.001)
    {
        return change;
    }
    else
    {
        return getChange();
    }
}

int main(void)
{
    float change = getChange();
    int cents = round(change * 100);
    int coins = 0;
    while (cents / 25 >= 1)
    {
        coins += 1;
        cents -= 25;
    }
    while (cents / 10 >= 1)
    {
        coins += 1;
        cents -= 10;
    }
    while (cents / 5 >= 1)
    {
        coins += 1;
        cents -= 5;
    }
    while (cents / 1 >= 1)
    {
        coins += 1 ;
        cents -= 1;
    }
    printf("%i \n", coins);
}
