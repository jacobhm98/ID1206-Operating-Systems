//
// Created by Jacob Malm on 2020-11-13.
//
#include "dlmall.h"

struct head *arena = NULL;
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

    u_int16_t size = ARENA - 2 * HEAD;

    new->bfree = FALSE;
    new->bsize = 0;
    new->free = TRUE;
    new->size = size;

    struct head *sentinel = after(new);
    sentinel->bfree = TRUE;
    sentinel->bsize = size;
    sentinel->free = FALSE;
    sentinel->size = 0;

    arena = (struct head *) new;

    return new;
}

struct head *after(struct head *block) {
    //block after starts at end of this entire block (mem size + header size)
    return (struct head *) ((char *) block + block->size + HEAD);
}

struct head *before(struct head *block) {
    //block before this one starts at address minus entire block previous (blocksize + header)
    return (struct head *) ((char *) block - (block->bsize + HEAD));
}

struct head *split(struct head *block, int size) {
    int rsize = block->size - (HEAD + size);
    block->size = rsize;

    struct head *splt = after(block);
    splt->bsize = rsize;
    splt->bfree = block->free;
    splt->size = size;
    splt->free = FALSE;

    struct head *aft = after(splt);
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
        if (flist == NULL){
            fprintf(stderr, "there are no more entries on the freelist\n");
        }
    }
}

void insert(struct head *block) {
    block->next = flist;
    block->prev = NULL;
    if (flist != NULL)
        flist->prev = block;
    flist = block;
}

struct head *find(int size) {
    struct head *found_block = flist;

    while (found_block != NULL && found_block->size < size){
        found_block = found_block->next;
    }

    //if we have failed to find a block that satisfies requirements in freelist
    if (found_block == NULL){
        return NULL;
    }

    //if we have found a suitable block, detach it
    detach(found_block);

    //if we can split the block in 2 and for both blocks size > MIN_SIZE
    if (found_block->size > LIMIT(size)) {
        struct head *allocated_block = split(found_block, size);
        insert(found_block);
        found_block = allocated_block;
    }
    found_block->free = FALSE;
    struct head *block_after_found_block = after(found_block);
    block_after_found_block->bfree = FALSE;
    return found_block;
}

size_t adjust(size_t request) {
    request = MIN(request);
    return request % ALIGN == 0 ? request : request - (request % ALIGN) + ALIGN;
}

void *dalloc(size_t request) {
    if (request <= 0) {
        return NULL;
    }
    int size = adjust(request);
    struct head *taken = find(size);
    return taken == NULL ? NULL : (char *) taken + HEAD;
}
void dfree(void *memory) {
    if (memory != NULL){
        struct head *block = (char*) memory - HEAD;
        struct head *aft = after(block);
        block->free = TRUE;
        aft->bfree = TRUE;
        insert(block);
    }
    return;
}

