// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
#define N 26

// Count for number of words
unsigned int word_count = 0;

// Dictionary loaded
bool dict_loaded = false;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Unsigned int for result;
    unsigned int res;

    // Hash value
    int hash_val = hash(word);

    // assign node
    node *n = table[hash_val];

    // If table value with that hash does not exist.
    if (n == NULL)
    {
        return false;
    }
    else
    {
        // Loop through the linked list
        while (n != NULL)
        {
            res = strcasecmp(n->word, word);

            // If word is in dictionary.
            if (res == 0)
            {
                return true;
            }
            else
            {
                // Check next in list
                n = n->next;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // N again = total size of table
    // Create table
    for (int i = 0; i < N; i++)
    {
        // Each index will be NULL to start
        table[i] = NULL;
    }

    // Assign the dictionay
    FILE *file = fopen(dictionary, "r");

    // If the file is empty
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer each char
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {

        // Allocate memory for each node.
        node *n = malloc(sizeof(node));

        // If the allocated memory is not possible
        if (n == NULL)
        {
            unload();
            return false;
        }

        // Scince memory was allocated.

        // Copy dictionary word to node.
        strcpy(n->word, word);

        // Set next node to null
        n->next = NULL;

        // Create hash
        int hash_val = hash(n->word);

        // Create the head node.
        node *head = table[hash_val];

        // Check if head node is pointing to a valid empty spot in memory.
        if (head == NULL)
        {
            // If it is then assign the table its new node.
            table[hash_val] = n;
        }
        else
        {
            n->next = table[hash_val];
            table[hash_val] = n;
        }

        // Increment count for a single iteration
        word_count++;
    }

    // Dictionary now has been loaded.
    dict_loaded = true;

    // Close dictionary.
    fclose(file);

    // Done
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // If the dictionary has been loaded.
    if (dict_loaded == true)
    {
        // Return the the number of words counted.
        return word_count;
    }
    else
    {
        // Dictionary has not been loaded yet.
        return 0;
    }


}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n != NULL)
        {
            node *t = n;
            n = n->next;
            free(t);
        }
    }
    return true;
}
