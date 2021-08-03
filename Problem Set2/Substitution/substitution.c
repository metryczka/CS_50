cd #include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

string upper(string tekst);
string cipher(string key, string tekst);



int main(int argc, string argv[])
{
    //Checking the key and making it CAPITALIZED
    if (argc == 2)
    {
        string key = upper(argv [1]);

        if (strlen(key) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            for (int i = 0; i < 26; i++)
            {
                if (isalpha(key[i]))
                {
                    for (int n = 0; n < 26; n++)
                    {
                        if (key[i] == key[n] && i != n)
                        {
                            printf("Key must not contain repeated characters.\n");
                            return 1;
                        }
                    }
                }

                else
                {
                    printf("Key musy only contain alphabetic characters\n");
                    return 1;
                }
            }

        }
        //Getting plaintext from user
        string input = get_string("plaintext: ");
        //Ciphering the input (using function called coded)
        string coded = cipher(key, input);
        printf("ciphertext: %s\n", coded);
    }

    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

}

//function that CAPITALIZE
string upper(string tekst)
{
    for (int i = 0, n = strlen(tekst); i < n; i++)
    {
        if (tekst[i] >= 'a' && tekst[i] <= 'z')
        {
            (tekst[i] = tekst[i] - 32);
        }
    }
    return tekst;
}
//Function for ciphering
string cipher(string key, string tekst)
{
    for (int i = 0, n = strlen(tekst); i < n; i++)
    {
        for (int k = 0; k < 26; k++)
        {
            if (tekst[i] == 65 + k)
            {
                tekst[i] =  key [k];
                k = 26;
            }

            if (tekst [i] == 97 + k)
            {
                tekst[i] = key [k] + 32;
                k = 26;
            }
        }
    }

    return tekst;
}