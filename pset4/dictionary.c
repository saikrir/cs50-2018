// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

unsigned dictWordCnt = 0;

// Represents a trie
node *root;

int char_to_index(char letter) {
    if(letter == '\''){
        return N-1;
    }
    else return tolower(letter) -'a';
}

node* newNode() {
    node *node = malloc(sizeof(node));
    
    node->is_word = false;
    for (int i = 0; i < N; i++)
    {
        node->children[i] = NULL;
    } 

    return node;
}


void insertWordIntoTrie(char *word) {
    node *mainNode = root;
    for (int i = 0; i < strlen(word); i++) {
        char ch = word[i];
        node *child = mainNode->children[char_to_index(ch)];
        if(child == NULL) {
            child = malloc(sizeof(node));
            child->is_word = false;
            for (int i = 0; i < N; i++)
            {
                child->children[i] = NULL;
            } 
        }
        mainNode->children[char_to_index(ch)] = child;
        mainNode = child; 
    }
    dictWordCnt++;
    mainNode->is_word = true;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
		insertWordIntoTrie(word);
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictWordCnt;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    bool isValid = false;
    node *currentNode = root;
    for (int i=0; i < strlen(word); i++) {
        char ch = word[i];
        node *nextNode = currentNode->children[char_to_index(ch)];
        if(nextNode == NULL) {
            return false;
        }
        else {
            currentNode = nextNode;
        }
    }
    
    return (currentNode!=NULL && currentNode->is_word);
}


bool is_terminalnode (node *pNode) {
    for(int i=0; i < N; i++) {
        if(pNode == NULL) return true;
        node *cNode = pNode->children[i];
        if(cNode!= NULL) {
            return false;
        }
    }
    return true;
}

void freeNode(node *pNode) {
    if(is_terminalnode(pNode)) {
        free(pNode);
    }else{
        for(int i =0; i < N; i++) {
            freeNode(pNode->children[i]);
        }
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    freeNode(root);
    return true;
}

