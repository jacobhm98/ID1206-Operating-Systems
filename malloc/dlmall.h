//
// Created by Jacob Malm on 2020-11-13.
//

#ifndef MALLOC_DLMALL_H
#define MALLOC_DLMALL_H

#include <stdio.h>
#include <sys/mman.h>
#include <stdint.h>
#include <errno.h>

//error handling
extern int errno;

//a block
struct head {
    uint16_t bfree;
    uint16_t bsize;
    uint16_t free;
    uint16_t size;
    struct head *next;
    struct head *prev;
};
//useful macros
#define TRUE 1
#define FALSE 0
#define HEAD (sizeof(struct head))
#define MIN(size) (((size) > (8) ? (size) : (8)))
#define LIMIT(size) (MIN(0) + HEAD + size)
#define MAGIC(memory) ((struct head*) memory - 1)
#define HIDE(block) (void*)((struct head*) block + 1)
#define ALIGN 8
#define ARENA (64 * 1024)

//function declarations
struct head* after(struct head*);
struct head* before(struct head*);
struct head *split(struct head *block, int size);
void *dalloc(size_t size);
void dfree();

#endif //MALLOC_DLMALL_H
