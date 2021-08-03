#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int letters_count(string sentences);
int word_count(string sentences);
int sentences_count(string sentences);

int main(void)
{
    //ask the user for text to check
    string tekst = get_string("Text: ");

    int letters = letters_count(tekst);
    int words = word_count(tekst);
    int sentences = sentences_count(tekst);


    float L = letters * 100.00 / words;
    float S = sentences * 100.00 / words;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);
    if (index >= 1 && index <= 16)
    {
        printf("Grade %i\n", grade);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }

}

int letters_count(string sentences)
{
    int counter = 0;
    for (int i = 0, n = strlen(sentences); i < n; i++)
    {
        if (sentences[i] >= 'a' && sentences[i] <= 'z')
        {
            counter = counter + 1;
        }

        else if (sentences[i] >= 'A' && sentences[i] <= 'Z')
        {
            counter = counter + 1;
        }

    }
    return counter;
}

int word_count(string sentences)
{
    int counter = 0;
    for (int i = 0, n = strlen(sentences); i < n; i++)
    {
        if (sentences[i] == ' ')
        {
            counter = counter + 1;
        }

    }
    return counter + 1;
}

int sentences_count(string sentences)
{
    int counter = 0;
    for (int i = 0, n = strlen(sentences); i < n; i++)
    {
        if (sentences[i] == '.' || sentences[i] == '?' || sentences[i] == '!')
        {
            counter = counter + 1;
        }


    }
    return counter;
}