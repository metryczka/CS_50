#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Ask for length of pyramid
   int len;
   do
   {
       len = get_int("Please type the leangth: ");
   }
   while (len < 1 || len > 8);

   //Drow the pyramid

   for (int i = 1; i <= len; i++)
   {
       for (int j = 0; j < len - i; j++)
       {
           printf(" ");

       }
       for (int k = 0; k < i; k++)
       {
           printf("#");
       }

       printf("  ");

       for (int g = 0; g < i; g++)
       {
           printf("#");
       }

       printf("\n");

   }


}