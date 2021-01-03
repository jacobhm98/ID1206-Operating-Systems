//
// Created by Jacob Malm on 2020-11-13.
//

#ifndef MALLOC_DLMALL_H
#define MALLOC_DLMALL_H

#include <stdio.h>
#include <sys/mman.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

//error handling
extern int errno;

//a block
struct head {
    uint16_t bfree;
    uint16_t bsize;
    uint16_t free;
    uint16_t size;
    uint32_t next;
    uint32_t prev;
};

//a taken block
//struct taken {
//    uint16_t bfree;
//    uint16_t bsize;
//    uint16_t free;
//    uint16_t size;
//};
//useful macros
#define TRUE 1
#define FALSE 0
#define HEAD (sizeof(struct head))
#define MIN(size) (((size) > (16)) ? (size) : (16))
#define LIMIT(size) (MIN(0) + HEAD + size)
#define MAGIC(memory) ((struct head*) memory - 1)
#define HIDE(block) (void*)((struct head*) block + 1)
#define ALIGN 8
#define ARENA (64 * 1024)

//datastructures
struct head *flist;

//function declarations
struct head* new();
struct head* after(struct head*);
struct head* before(struct head*);
struct head *split(struct head *block, int size);
size_t adjust(size_t request);
struct head *find(int size);
struct head *merge(struct head*);
uint32_t getOffset(struct head*);
struct head* getBlock(uint32_t);
void *dalloc(size_t size);
void dfree();

#endif //MALLOC_DLMALL_H
