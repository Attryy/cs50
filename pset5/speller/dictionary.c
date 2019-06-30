// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>


// global variable for tracking dictionary size
unsigned int dict_size = 0;

// global boolean for tracking load/unload dictionary operations
bool loaded = false;

// define the node in the linked list
typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
}
node;

// declare the hashtable, i.e. an array of pointer to the starting node of the linked list
// here MAX is the number of alphabets
node *ptr[MAX];

int hash_function(const char *input)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *input++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % MAX;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r"); //Returns a pointer to the file
    if (file == NULL)
    {
        printf("Could not open %s. \n", dictionary);
        return false;
    }

    // make all hash table elements NULL
    for (int i = 0; i < MAX; i++)
    {
        ptr[i] = NULL;
    }
    while (!feof(file))
    {
        node *new_node = malloc(sizeof(node)); // allocate memory for the new words (node)
        if (new_node == NULL)
        {
            printf("Could not allocate memory for the node.");
            loaded = false;
            return loaded;
        }
        fscanf(file, "%s", new_node->word);
        new_node->next = NULL;
        dict_size++;

        int hashed = hash_function(new_node->word);

        node *head;
        head = ptr[hashed]; //take out the pointer at the location of the array

        if(head == NULL) // the bucket is empty for this entry, we can put our new word into it
        {
            ptr[hashed] = new_node;
        }
        else
        {// there is a pointer pointing to some node already, we'll link the new node to the front of the list
            new_node->next = head;
            ptr[hashed] = new_node;
        }
    }

    fclose(file);
    loaded = true;
    return loaded;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int word_length = strlen(word);
    char word_normal[word_length+1];
    for (int i = 0; i< word_length; i++)
    {
        word_normal[i]= tolower(word[i]);
    }
    word_normal[word_length] = '\0';

    int hashed = hash_function(word_normal);

    node *head;
    head = ptr[hashed];
    while(head != NULL)
    {
        if(strcmp(head->word, word_normal) == 0)
        {
            return true;
        }
        else
        {
            head = head->next;
        }
    }
    return false;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return dict_size;
    }
    else
    {
       return 0;
    }

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i=0;i<MAX; i++)
    {
        node* head;
        head = ptr[i];
        while(head != NULL)
        {
            node* temp;
            temp = head;
            head = head->next;
            free(temp);

        }
        return true;
    }
    return false;
}
