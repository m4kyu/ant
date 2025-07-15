#include "chunk.h"
#include <stdio.h>
#include <stdlib.h>

static HashTable table;

static int index = 0;
Chunk cached[TABLE_SIZE];



Chunk* getChunk(int x, int y) {
    Chunk *chunk = getEl(x, y);
    if (chunk == NULL) {
       // printf("Creating new\n");
        return createChunk(x, y);
    }

    //printf("Reusing old one\n");
    return chunk;
}


static Chunk* createChunk(int x, int y) {
    // Chunk *chunk = calloc(1, sizeof(Chunk));
    // if (chunk == NULL) 
    //     return NULL;


    Chunk chunk = {0};
    chunk.x = x;
    chunk.y = y;



    int tmp = index % TABLE_SIZE;
    index++;

    cached[tmp] = chunk;
    addChunk(&cached[tmp]);
    return &cached[tmp];
}


static void addChunk(Chunk *chunk) {
    const int HASH = hash(chunk->x, chunk->y);
    //printf("HASH: %d\n", HASH);

    
    if (table.items[HASH] == NULL) {
        table.items[HASH] = malloc(sizeof(HTNode));
        if (table.items[HASH] == NULL)
            return;

        table.items[HASH]->next = NULL;
        table.items[HASH]->val = chunk;
        return;
    }



    
    for (HTNode *node = table.items[HASH]; node != NULL; node = node->next) {
        if (node->val->x == chunk->x && node->val->y == chunk->y) {
//            printf("Freeing\n");
           // free(node->val);
            node->val = chunk;
            return;
        }
    }



    printf("Mallocing node\n");
    HTNode *new_node = malloc(sizeof(HTNode));
    if (new_node == NULL)
        return;


    new_node->next = NULL;
    new_node->val = chunk;

    HTNode *node;
    for (node = table.items[HASH]; node->next != NULL; node = node->next)
        ;
    node->next = new_node;
}

static Chunk* getEl(int x, int y) {
    for (HTNode *node = table.items[hash(x, y)]; node != NULL; node = node->next) 
        if (node->val->x == x && node->val->y == y) 
            return node->val;

    return NULL;
}


static unsigned int cantorFunc(unsigned int x, unsigned int y) {
    return ((x + y) * (x + y + 1)) / 2 + y;
}

static unsigned int hash(int x, int y) {
    return cantorFunc(x, y) % TABLE_SIZE;
}

