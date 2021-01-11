//
// Created by Jacob Malm on 2021-01-03.
//
#include <assert.h>
#include <stdlib.h>
#include "green.h"
#include <signal.h>
#include <sys/time.h>
#include <zconf.h>
#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define STACK_SIZE 4096
#define PERIOD 100


static ucontext_t main_cntx = {0};
static green_t main_green = {&main_cntx, NULL, NULL, NULL, NULL, NULL, FALSE};
static green_t *running = &main_green;
green_t *readyQueue = NULL;
static sigset_t block;

void timer_handler(int);

static void init() __attribute__((constructor));

void green_thread();

int enqueue(green_t **, green_t *);

green_t *dequeue(green_t **);
int list_length(green_t **);

void init() {
    getcontext(&main_cntx);

    sigemptyset(&block);
    sigaddset(&block, SIGVTALRM);

    struct sigaction act = {0};
    struct timeval interval;
    struct itimerval period;

    act.sa_handler = timer_handler;
    assert(sigaction(SIGVTALRM, &act, NULL) == 0);
    interval.tv_sec = 0;
    interval.tv_usec = PERIOD;
    period.it_interval = interval;
    period.it_value = interval;
    setitimer(ITIMER_VIRTUAL, &period, NULL);
}

void timer_handler(int sig) {
    green_t *susp = running;
    enqueue(&readyQueue, susp);
    green_t *next = dequeue(&readyQueue);
    running = next;

    write(1, "timer interrupt\n", strlen("timer interrupt\n"));
    swapcontext(susp->context, next->context);
}


int green_create(green_t *new, void *(*fun)(void *), void *arg) {
    ucontext_t *cntx = (ucontext_t *) malloc(sizeof(ucontext_t));
    getcontext(cntx);

    void *stack = malloc(STACK_SIZE);

    cntx->uc_stack.ss_sp = stack;
    cntx->uc_stack.ss_size = STACK_SIZE;
    makecontext(cntx, green_thread, 0);

    new->context = cntx;
    new->fun = fun;
    new->arg = arg;
    new->next = NULL;
    new->join = NULL;
    new->retval = NULL;
    new->zombie = FALSE;

    enqueue(&readyQueue, new);

    return 0;
}

void green_thread() {
    green_t *this = running;

    void *result = (*this->fun)(this->arg);

    //place waiting (joining) thread in ready queue
    if (this->join != NULL) {
        enqueue(&readyQueue, this->join);
    }

    this->retval = result;
    this->zombie = TRUE;
    green_t *next = dequeue(&readyQueue);


    running = next;
    setcontext(next->context);
}

int green_yield() {
    sigprocmask(SIG_BLOCK, &block, NULL);
    green_t *susp = running;
    //add susp to ready queue;
    enqueue(&readyQueue, susp);
    //select the next thread for execution
    green_t *next = dequeue(&readyQueue);
    assert(next != NULL);

    running = next;
    swapcontext(susp->context, next->context);
    sigprocmask(SIG_UNBLOCK, &block, NULL);
    return 0;
}

int green_join(green_t *thread, void **res) {
    if (!thread->zombie) {
        green_t *susp = running;
        assert(thread->join == NULL);
        thread->join = susp;

        //select the next thread for execution
        green_t *next = dequeue(&readyQueue);
        assert(next != NULL);
        running = next;
        swapcontext(susp->context, next->context);
    }
    res = thread->retval;
    return 0;
}

int enqueue(green_t **head, green_t *node) {
    if (node == NULL) {
        return 0;
    }
    if (*head == NULL) {
        *head = node;
        return 0;
    }
    green_t *last_node = *head;
    while (last_node->next != NULL) {
        last_node = last_node->next;
    }
    last_node->next = node;
    return 0;
}

green_t *dequeue(green_t **head) {
    printf("entered dequeue\n");
    if (*head == NULL) {
        printf("returning null from deq\n");
        return NULL;
    }
    green_t *node = *head;
    *head = node->next;
    node->next = NULL;
    return node;
}

int contains(green_t **head, green_t *node) {
    if (*head == NULL) {
        return FALSE;
    }
    green_t *curr_node = *head;
    while (curr_node->next != NULL) {
        if (curr_node == node) {
            return TRUE;
        }
        curr_node = curr_node->next;
    }
    if (curr_node == node)
        return TRUE;
    return FALSE;
}
int list_length(green_t **head){
    int count = 0;
    if (*head == NULL){
        return 0;
    }
    green_t *curr_node = *head;
    while (curr_node->next != NULL) {
        curr_node = curr_node->next;
        count++;
    }
    return count;
}

void green_cond_init(green_cond_t *cond) {
    cond->waiting = malloc(sizeof(green_t*));
    *cond->waiting = NULL;
}

void green_cond_wait(green_cond_t *cond, green_mutex_t *mutex) {
    sigprocmask(SIG_BLOCK, &block, NULL);
    green_t *this = running;
    enqueue(cond->waiting, this);
    printf("I am placed on the cond waitlist\n");
    if (mutex != NULL){
        mutex->taken = FALSE;
        enqueue(&readyQueue, *mutex->suspended);
        mutex->suspended = NULL;
    }
    green_t *next = dequeue(&readyQueue);
    running = next;
    printf("i will schedule another thread\n");
    swapcontext(this->context, next->context);
    printf("i have woken up from my slumber\n");
    if (mutex != NULL){
        if (mutex->taken){
            enqueue(mutex->suspended, this);
            running = dequeue(&readyQueue);
            swapcontext(this->context, running->context);
        }
        else{
            mutex->taken = TRUE;
        }
    }
    sigprocmask(SIG_UNBLOCK, &block, NULL);
}

void green_cond_signal(green_cond_t *cond) {
    printf("waking up a thread from cv suspension\n");
    printf("length of cond q: %d\n", list_length(cond->waiting));
    green_t *wake_up = dequeue(cond->waiting);
    assert(wake_up != NULL);
    enqueue(&readyQueue, wake_up);
}

int green_mutex_init(green_mutex_t *mutex) {
    mutex->taken = FALSE;
    mutex->suspended = malloc(sizeof(green_t*));
    *mutex->suspended = NULL;
    return 0;
}

int green_mutex_lock(green_mutex_t *mutex) {
    sigprocmask(SIG_BLOCK, &block, NULL);
    green_t *susp = running;
    if (mutex->taken) {
        enqueue(mutex->suspended, susp);
        green_t *next = dequeue(&readyQueue);
        running = next;
        swapcontext(susp->context, next->context);
    } else {
        mutex->taken = TRUE;
    }
    sigprocmask(SIG_UNBLOCK, &block, NULL);
    return 0;
}

int green_mutex_unlock(green_mutex_t *mutex) {
    sigprocmask(SIG_BLOCK, &block, NULL);
    if (*mutex->suspended != NULL) {
        enqueue(&readyQueue, dequeue(mutex->suspended));
    } else {
        mutex->taken = FALSE;
    }
    sigprocmask(SIG_UNBLOCK, &block, NULL);
    return 0;
}