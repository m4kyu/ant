#include <stdlib.h>


#define TABLE_SIZE 100
#define CHUNK_SIZE 32





typedef struct {
    int x, y;
    int data[CHUNK_SIZE][CHUNK_SIZE];
} Chunk;


typedef struct HTNode {
    struct HTNode *next;
    Chunk *val;
} HTNode;


typedef struct {
    HTNode *items[TABLE_SIZE];
} HashTable;




extern Chunk cached[TABLE_SIZE];


Chunk* getChunk(int x, int y);


static Chunk* createChunk(int x, int y);
static void addChunk(Chunk *chunk);
static Chunk* getEl(int x, int y);

static unsigned int cantorFunc(unsigned int x, unsigned int y);
static unsigned int hash(int x, int y);

