//
// Created by Jacob Malm on 2021-01-03.
//

#ifndef GREEN_THREADS_GREEN_H
#define GREEN_THREADS_GREEN_H

#define _XOPEN_SOURCE 600
#include <ucontext.h>

typedef struct green_t {
    ucontext_t *context;
    void *(*fun) (void*);
    void *arg;
    struct green_t *next;
    struct green_t *join;
    void *retval;
    int zombie;
} green_t;

int green_create(green_t *thread, void *(*fun)(void*), void *arg);
int green_yield();
int green_join(green_t *thread, void** val);


#endif //GREEN_THREADS_GREEN_H
