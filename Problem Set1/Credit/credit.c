#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long card;
    card = get_long("Number: ");
    long number = card;

    int checksum = 0;
    int digit;
    long rest;
    for (int i = 0; i<17; i++)
    {
        digit = number % 10;
        number = number /10;
        if (i%2 == 0)
        {
            checksum = checksum + digit;
        }
        else
        {
            int double_digit = digit*2;
            if (double_digit<10)
            {
                checksum = checksum + double_digit;
            }
            else
            {
                int digitII;

                for (int j = 0; j < 2; j++)
                {
                    digitII = double_digit % 10;
                    double_digit = double_digit /10;
                    checksum = checksum + digitII;

                }

            }
        }

    }
    if (checksum % 10 == 0)
    {
        if (card < (1e17) && card > 999999999999999)
        {
            int first_nu = card / (1e14);

            if (first_nu > 50 && first_nu < 56)
            {
                printf("MASTERCARD\n");
            }

            else if (first_nu > 39 && first_nu < 50)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (card < (1e16) && card > 99999999999999)
        {
            int first_nu = card / (1e13);

                if (first_nu == 34 || first_nu == 37)
                {
                    printf("AMEX\n");
                }

                else
                {
                    printf("INVALID\n");
                }
        }
        else if(card < (1e14) && card > 999999999999)
        {
            int first_nu = card / (1e11);

                if (first_nu > 39 && first_nu < 50)
                {
                    printf("VISA\n");
                }

                else
                {
                    printf("INVALID\n");
                }
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }
}