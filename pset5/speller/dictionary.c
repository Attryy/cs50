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

// define the node in tries
typedef struct node
{
    bool end_of_word;
    struct node *children[MAX+1]; //defines an array of the specified size and each element in the array is a pointer to a node
}
node;

typedef struct node *node_ptr;

int hash_function(const char letter)
{
    if (letter == '\'')
    {
    return MAX;
    }
    else
    {
        return tolower(letter)-97;
    }
}

node_ptr create_node(void)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("Error when allocating memory for the node.");
        return NULL;
    }
    for (int i = 0; i< MAX; i++)
    {
        new_node->children[i] = NULL;
    }
    new_node->end_of_word = false;

    return new_node;
}

node_ptr root = NULL;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r"); //Returns a pointer to the file
    if (file == NULL)
    {
        printf("Could not open %s. \n", dictionary);
        return false;
    }

    root = create_node();

    while (!feof(file))
    {
        char word[LENGTH];
        fscanf(file, "%s", word);
        dict_size++;
        node *ptr;
        ptr = root;

        for (int j = 0; j < strlen(word); j++)
        {
            int hashed = hash_function(word[j]);
            if (ptr->children[hashed] == NULL)
            {
                node_ptr new_node = create_node();
                ptr->children[hashed] = new_node;
            }

            ptr = ptr->children[hashed];

            if (ptr == NULL)
            {
                printf("Cannot allocate memory for a new node");
                return false;
            }
        }
        ptr->end_of_word = true;
    }

    fclose(file);
    loaded = true;
    return loaded;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *ptr = root;
    for(int i = 0; i < strlen(word); i++)
    {
        int hashed = hash_function(word[i]);
        if(ptr->children[hashed] == NULL)
        {
            return false;
        }
        else
        {
            ptr = ptr->children[hashed];
        }
    }
    return ptr->end_of_word;
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
bool trie_free(node *ptr)
{
    if (ptr == NULL)
    {
        return false;
    }

    for (int i = 0; i < MAX; i++)
    {
        trie_free(ptr->children[i]);
    }

    free(ptr);
    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    return trie_free(root);
}
