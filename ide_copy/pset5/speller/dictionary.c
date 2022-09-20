// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
// *table[N] is just a POINTER to a struct node.
// It itself does not have attributes like word
// and node.
node *table[N];

// Maintain count of words in linked list
bool flag = false;
int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int i, l = strlen(word);
    char s[l];
    strcpy(s, word);
    for (i = 0; i < l; i++)
    {
        s[i] = tolower(s[i]);
    }
    unsigned int index = hash(s);
    if (table[index] != NULL)
    {
        for (node *ptr = table[index]; ptr != NULL; ptr = (*ptr).next)
        {
            if (strcmp((*ptr).word, s) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // Based on YouTube video by Deliberate Think
    // https://www.youtube.com/watch?v=ZEPDBlVFpso
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
        {
            n = word[i] - 'a' + 1;
        }
        else
        {
            n = 27;
        }
        hash = ((hash << 3) + n) % N;
    }
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Initialise table and count
    count = 0;
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Create a char array to store words temporarilly
    char word[LENGTH + 1];

    int index;

    while (fscanf(file, "%s", word) != EOF)
    {
        count ++;

        // Create a temporary node for the word
        //mallocing so that node is available until unload
        node *temp;
        while (true)
        {
            temp = malloc(sizeof(node));
            if (temp != NULL)
            {
                break;
            }
        }
        strcpy((*temp).word, word);
        (*temp).next = NULL;

        // Calculate hash code
        index = hash(word);

        // Insert to hash table
        //*table[index].next is NULL if index
        //encounterd for first time

        (*temp).next = table[index];
        table[index] = temp;
    }
    fclose(file);
    flag = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    if (flag == false)
    {
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *crs = table[i];

            while (crs != NULL)
            {
                node *tmp = crs;
                crs = (*crs).next;
                free(tmp);
            }
        }
    }
    return true;

}
