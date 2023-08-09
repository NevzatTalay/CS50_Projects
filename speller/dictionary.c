// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 226;
int dict_length = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor;

    // TODO
    // Büyük Harf Küçük Harf Duyarlılığı olmalı.
    // Foo da FoO da doğru kabul edilmeli.
    // bazen de kesme isareti olabilir kelimelerde
    // valgrind ile memory check yap.
    cursor = table[hash(word)];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            // printf("1: %s, 2: %s\n",cursor->word, word);
            //  printf("You Have Found!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    // printf("1: %s, 2: %s\n",cursor->word, word);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // printf("%lu\n", strlen(word));
    int decreasing_length = LENGTH;
    // max_value is only valid for decreasing_length/30
    double max_value = 7753;
    double sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {

        decreasing_length = decreasing_length - 1;

        // 30 rakamini degistirme islem kolayligi icin oradadir. onu ellersen her sey bozulur.
        if (word[i] - 'a' + 'a' < 96)
        {
            sum = sum + pow(word[i] - 'a' + 'a' + 32, decreasing_length / 30.0);
        }
        else
        {
            sum = sum + pow(word[i] - 'a' + 'a', decreasing_length / 30.0);
        }
    }
    // return value
    int dondur = ((int)round(sum) / max_value) * N;

    // TODO: Improve this hash function
    return dondur;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // true ya da false dönecek.

    // node *n = malloc(sizeof(node));
    // strcpy(n->word,"Hello");
    // n->next = NULL;
    char words[LENGTH] = "";
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    while (fscanf(inptr, "%s", words) != EOF)
    {
        dict_length++;
        node *n = malloc(sizeof(node));
        // add malloc null check
        strcpy(n->word, words);
        // n->next = NULL;
        int current_hash_value = hash(words);
        if (table[current_hash_value] == NULL)
        {
            table[current_hash_value] = n;
        }
        else
        {
            // printf("%p\n",n->next);
            (n->next) = table[current_hash_value];
            table[current_hash_value] = n;
        }
    }
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // printf("Size of Dictionary%i\n", dict_length);
    return dict_length;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor;
    node *temp;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        table[i] = NULL;
    }


    return true;
}
