//
// Created by Jacob Malm on 2020-11-13.
//

#ifndef MALLOC_DLMALL_H
#define MALLOC_DLMALL_H

#include <stdio.h>

struct head {
    u_int16_t bfree;
    u_int16_t bsize;
    u_int16_t free;
    u_int16_t size;
    struct head *next;
    struct head *prev;
};
#define TRUE 1
#define FALSE 0
#define HEAD (sizeof(struct head))
#define MIN(size) (((size) > (8) ? (size) : (8)))
#define LIMIT(size) (MIN(0) + HEAD + size)
#define MAGIC(memory) ((struct head*) memory - 1)
#define HIDE(block) (void*)((struct head*) block + 1)

void *dalloc(size_t size);

void dfree();

#endif //MALLOC_DLMALL_H
