#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //Ask the user for amount of change (only positive)
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);
    // change dollars for cents
    int cents = round(change * 100);
    // define the coins that can be used
    int penys = 1;
    int nickels = 5;
    int dimes = 10;
    int quarters = 25;

    int rounds = 0;
    // number of quarters
    while (cents >= 25)
    {
        cents = cents - quarters;
        rounds++;
    }
    // number of dimes
    while (cents >= 10)
    {
        cents = cents - dimes;
        rounds++;
    }
    // number of nickels
    while (cents >= 5)
    {
        cents = cents - nickels;
        rounds++;
    }
    // number of penys
    while (cents > 0)
    {
        cents = cents - penys;
        rounds++;
    }

    printf("%i \n", rounds);
}