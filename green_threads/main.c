#include <stdio.h>
#include "green.h"

void *test_cond(void *arg);

void *test_yield(void *arg);

void *increment_counter(void *arg);

void *mutex_test(void *arg);

void *consumer(void *arg);

void *producer(void *arg);

void first_small_test();

int flag = 0;
green_cond_t cond;
green_mutex_t mutex;
long counter = 0;


green_cond_t empty;
green_cond_t full;
int resource = 0;
#define EMPTY 0
#define FULL 1

void *producer(void *arg) {
    while (1) {
        green_mutex_lock(&mutex);
        if (resource == EMPTY) {
            //produce
            resource = FULL;
            printf("PRODUCE");
            green_cond_signal(&full);
        }
        else{
            green_cond_wait(&empty, &mutex);
        }
        green_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg){
    while(1){
        green_mutex_lock(&mutex);
        if (resource == FULL){
            //consume
            resource = EMPTY;
            printf("CONSUMING\n");
            green_cond_signal(&empty);
        }
        else{
            green_cond_wait(&full, &mutex);
        }
        green_mutex_unlock("&mutex");
    }
}

void *test_yield(void *arg) {
    int i = *(int *) arg;
    int loop = 4;
    while (loop > 0) {
        printf("thread %d: %d\n", i, loop);
        loop--;
        green_yield();
    }
}

void first_small_test() {
    green_t g0, g1, g2, g3;
    int a0 = 0;
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    green_create(&g0, producer, &a0);
    green_create(&g1, consumer, &a1);
    //green_create(&g2, mutex_test, &a2);
    //green_create(&g3, mutex_test, &a3);
    green_join(&g0, NULL);
    green_join(&g1, NULL);
    //green_join(&g2, NULL);
    //green_join(&g3, NULL);
    printf("value of counter %d\n", counter);
}

void *mutex_test(void *arg) {
    int id = *(int *) arg;
    int loop = 1000;
    green_mutex_lock(&mutex);
    while (loop > 0) {
        loop--;
        printf("thread %d is here\n", id);
    }
    green_mutex_unlock(&mutex);
    return NULL;
}

void *increment_counter(void *arg) {
    int id = *(int *) arg;
    int loop = 100000000;
    while (loop > 0) {
        //printf("thread %d: %d\n", id, loop);
        loop--;
        green_mutex_lock(&mutex);
        counter++;
        green_mutex_unlock(&mutex);
    }
}


void *test_cond(void *arg) {
    int id = *(int *) arg;
    int loop = 100000;
    while (loop > 0) {
        green_mutex_lock(&mutex);
        if (flag == id) {
            printf("thread %d: %d\n", id, loop);
            loop--;
            flag = (id + 1) % 2;
            green_cond_signal(&cond);
        } else {
            green_cond_wait(&cond, &mutex);
        }
        green_mutex_unlock(&mutex);
    }
}

int main() {
    green_cond_init(&empty);
    green_cond_init(&full);
    green_mutex_init(&mutex);
    first_small_test();
    return 0;
}
