#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

string cipher(string plaintext, int key);

int main(int argc, string argv[])
{

    if (argc == 2 && atoi(argv[1]) > 0)
    {
        string tekst = get_string("plaintext: ");
        int key = atoi(argv[1]);
        string ciphered = cipher(tekst, key);
        printf("ciphertext: %s\n", ciphered);

    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

}


string cipher(string plaintext, int key)
{
    int k = strlen(plaintext);
    for (int i = 0; i < k; i++)
    {

        if (isalpha(plaintext[i]))
        {
            if isupper(plaintext[i])
            {
                plaintext[i] = ((plaintext[i] - 65 + key) % 26) + 65;
            }
            else if islower(plaintext[i])
            {
                plaintext[i] = ((plaintext[i] - 97 + key) % 26) + 97;
            }
        }
    }
    return plaintext;
}

