//
// Created by Jacob Malm on 2020-11-13.
//
#include "dlmall.h"

struct head *arena = NULL;
struct head *flist;

struct head *new() {
    if (arena != NULL) {
        printf("one arena already allocated \n");
        return NULL;
    }

    struct head *new = mmap(NULL, ARENA, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (new == MAP_FAILED) {
        printf("mmap failed: error %d\n", errno);
        return NULL;
    }

    new->bfree = FALSE;
    new->bsize = 0;
    new->free = TRUE;
    new->size = ARENA - HEAD;

    struct head *sentinel = after(new);
    sentinel->bfree = TRUE;
    sentinel->bsize = ARENA - HEAD;
    sentinel->free = FALSE;
    sentinel->size = 0;

    return new;
}

struct head *after(struct head *block) {
    return (struct head *) ((char *) block + block->size + HEAD);
}

struct head *before(struct head *block) {
    return (struct head *) ((char *) block - block->bsize - HEAD);
}

struct head *split(struct head *block, int size) {
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

void detach(struct head *block) {
    if (block->next != NULL)
        block->next->prev = block->prev;

    if (block->prev != NULL)
        block->prev->next = block->next;

    else {
        flist = block->next;
    }
}

void insert(struct head *block) {
    block->next = flist;
    block->prev = NULL;
    if (flist != NULL)
        flist->prev = block;
    flist = block;
}

void *dalloc(size_t size) {

}

void dfree() {


}

