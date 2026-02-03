// Implements a dictionary's functionality using a hash table of linked lists

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// ---------------------------------------------------------------------------
// Data structures
// ---------------------------------------------------------------------------

// A single node in a hash-table bucket's linked list
typedef struct node
{
    char        word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets — a large prime keeps chains short
#define N 104729

// The hash table itself: an array of N pointers to linked-list heads
node *table[N];

// Running count of words loaded
unsigned int word_count = 0;

// ---------------------------------------------------------------------------
// hash
// ---------------------------------------------------------------------------
// Maps a word to a bucket index in [0, N).
// Uses djb2-style polynomial hashing (case-insensitive).
unsigned int hash(const char *word)
{
    unsigned long hash_value = 5381;

    for (int i = 0; word[i] != '\0'; i++)
    {
        // Multiply by 33 and add the lowercase character value
        hash_value = hash_value * 33 + tolower((unsigned char)word[i]);
    }

    return (unsigned int)(hash_value % N);
}

// ---------------------------------------------------------------------------
// load
// ---------------------------------------------------------------------------
// Opens the dictionary file, reads every word, inserts each into the hash table.
// Returns true on success, false on failure.
bool load(const char *dictionary)
{
    // Open the dictionary file for reading
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Buffer to hold each word as it is read
    char word[LENGTH + 1];

    // Read words one per line until EOF
    while (fscanf(file, "%s", word) == 1)
    {
        // Allocate a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy the word into the node
        strcpy(new_node->word, word);

        // Compute this word's bucket
        unsigned int index = hash(word);

        // Insert at the head of the bucket's linked list (O(1))
        new_node->next = table[index];
        table[index]   = new_node;

        // Increment word counter
        word_count++;
    }

    // Close file before returning
    fclose(file);

    return true;
}

// ---------------------------------------------------------------------------
// check
// ---------------------------------------------------------------------------
// Returns true if 'word' is in the dictionary (case-insensitive), else false.
bool check(const char *word)
{
    // Hash the word to find its bucket
    unsigned int index = hash(word);

    // Walk the linked list in that bucket
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // strcasecmp does a case-insensitive comparison
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// ---------------------------------------------------------------------------
// size
// ---------------------------------------------------------------------------
// Returns the number of words in the dictionary (i.e. loaded so far).
unsigned int size(void)
{
    return word_count;
}

// ---------------------------------------------------------------------------
// unload
// ---------------------------------------------------------------------------
// Frees every node in every bucket, then returns true.
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            // Save pointer to current node before we advance
            node *tmp = cursor;
            // Move cursor to next node
            cursor = cursor->next;
            // Free the saved node
            free(tmp);
        }

        // Null out the bucket head (good practice)
        table[i] = NULL;
    }

    return true;
}
