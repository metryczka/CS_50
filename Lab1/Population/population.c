#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start = 8;
    do
    {
        start = get_int("Please give the size of population: ");
    }

    while (start < 9);

    // TODO: Prompt for end size

    int end = 8;
    do
    {
        end = get_int("Please give the final size: ");
    }

    while (end < start);



    // TODO: Calculate number of years until we reach threshold

    int years = 0;
    int population = start;
    if (start < end)
    {
        do
        {
            population = population + population / 3 - population / 4 ;
            years ++;
        }

        while (population < end);
    }

    // TODO: Print number of years
    printf("Years: %i \n", years);

}