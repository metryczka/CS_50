// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];
int words_count = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    int index = hash(word);

    //searches linked list at the index
    for (node *search = table[index]; search != NULL; search = search->next)
    {
        if (strcasecmp(word, search->word) == 0)
        {
            return true;
        }
    }
    return false;


}


// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++) != '\0')
    {
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    }

    hash = hash % N;

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    //opening a file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fclose(file);
        return false;
    }
    //reading words & counting them
    char *word = malloc(46);

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }
        int index = hash(word);
        strcpy(n->word, word);

        if (table[index] == NULL)
        {
            n->next = NULL;
            table[index] = n;
            words_count += 1;
        }
        else if (table[index] != NULL)
        {
            n->next = table[index];
            table [index] = n;
            words_count += 1;
        }
    }

    free(word);
    fclose(file);

    if (words_count != 0)
    {
        return true;
    }
    else
    {

        return false;
    }

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

    }
    return true;
}
