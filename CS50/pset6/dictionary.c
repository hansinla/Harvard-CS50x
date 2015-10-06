/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 *
 * Hans van Riet
 *
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"

// global variables
node* root;
int wordCount = 0;

node* newNode(void)
{
    node* newNode = malloc(sizeof(node));
    newNode->is_word = false;
    for (int i = 0 ; i < 27 ; i++)
    {
        newNode->children[i] = NULL;
    }
    return newNode;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* current_node = root;
    
    for (int i = 0 ; i < strlen(word) ; i++)
    {
        int index = (int) tolower(word[i]) - OFFSET;
        if (current_node->children[index] == NULL)
        {  
            return false;
        }
        else
        {
            current_node = current_node->children[index];
        }
    }
    if (current_node->is_word)
        {
            return true;
        }
        else
        {
            return false;
        }
    return true;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // create root node
    root = newNode();
   
    // open dict file
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    char word[LENGTH];
    while (fgets(word, LENGTH, fp) != NULL)
    {
        node* current_node = root;
        for (int i = 0 ; i < strlen(word) - 1 ; i++)
        {
            int index = (int) word[i] - OFFSET;
            if (current_node->children[index] == NULL)
            {   
                // create a new node
                node* newnode =  newNode();
                current_node->children[index] = newnode;
                current_node = current_node->children[index];
            }
            else
            {
                // traverse a node
                current_node = current_node->children[index];
            } 
        }
        // end of word
        wordCount++;
        current_node->is_word = true;   
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordCount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    destroy(root);
    return true;
}

/*
 * Recursively destroy the trie.
 */
void destroy(node* root)
{
    if (root == NULL)
    {
        return;
    }

    for (int i = 0 ; i < 27 ; i++)
    {
        destroy(root->children[i]);
    }

    free(root);
}

