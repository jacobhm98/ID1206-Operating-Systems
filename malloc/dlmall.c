//
// Created by Jacob Malm on 2020-11-13.
//
#include "dlmall.h"

struct head *after(struct head *block){
    return (struct head*)((char*)block + block->size + HEAD);
}

struct head *before(struct head *block){
    return (struct head*)((char*)block - block->bsize - HEAD);
}

struct head *split(struct head *block, int size){
    int rsize = block->size - (HEAD + size);
    block->size = rsize;

    struct head *splt = after(block);
    splt->bsize = rsize;
    splt->bfree = block->free;
    splt->size = size;
    splt->free = TRUE;

    struct head *aft = block->next;
    //why dont we update next and previous pointers here?
    aft->bsize = size;
    return splt;
}
void * dalloc(size_t size){

}

void dfree(){


}

