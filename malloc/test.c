#include <stdlib.h>
#include "dlmall.h"

int length_of_list();
float average_size();
size_t generate_random_request_size();
void perform_memory_requests(int);
void print_status();
void perform_memory_frees(int);
void sanity();

#define MAX_REQ_SIZE 5000
#define MIN_REQ_SIZE 20
#define SEED 0
#define MAX_NUM_OF_ALLOTTED_BLOCKS 100

int mem_requests = 0;
int mem_frees = 0;
int mem_errs = 0;
struct head *REQUESTS[MAX_NUM_OF_ALLOTTED_BLOCKS];
int request_pointer = 0;


int main() {
    flist = new();
    print_status();
    perform_memory_requests(10);
    sanity();
    print_status();
    perform_memory_frees(10);
    sanity();
    print_status();
}

void sanity(){
    struct head *curr = flist;
    struct head *prev = curr->prev;
    while(curr != NULL){
        assert(prev == curr->prev);
        assert(curr->size % ALIGN == 0);
        assert(curr->free == TRUE);
        prev = curr;
        curr = curr->next;
    }
}

//could speed these up and do the calculations for average and length in 1 pass instead of 3,
//buuuut im not gonna. for loop go brrrrrrrrrrr.
int length_of_list() {
    int length = 0;
    struct head *curr = flist;
    while (curr != NULL) {
        ++length;
        curr = curr->next;
    }
    return length;
}

float average_size() {
    float average_size = 0;
    struct head *curr = flist;
    while (curr != NULL) {
        average_size += curr->size;
        curr = curr->next;
    }
    return average_size / (float) length_of_list();
}

void print_status() {
    int length;
    length = length_of_list();
    float average = average_size();
    printf("the length of the freelist is %d\n", length);
    printf("the average size of the entries on the freelist is %f\n", average);
    printf("Total number of memory requests performed: %d, total number of memory frees: %d, current number of allocated memory blocks: %d, number of failed memory requests: %d\n", mem_requests, mem_frees, request_pointer, mem_errs);
}

void perform_memory_requests(int num_of_requests) {
    srand(SEED);
    size_t size;
    void *mem_pointer;
    for (int i = 0; i < num_of_requests; ++i) {
        size = generate_random_request_size();
        mem_pointer = dalloc(size);
        if (mem_pointer == NULL) {
            fprintf(stderr, "error allocating memory");
            mem_errs++;
            break;
        }
        mem_requests++;
        struct head *mem_header = (char *) mem_pointer - HEAD;
        REQUESTS[request_pointer] = mem_header;
        request_pointer++;
    }
}

void perform_memory_frees(int num_frees) {
    for (int i = 0; i < num_frees; ++i) {
        struct head *mem_header = REQUESTS[request_pointer - 1];
        void *mem_pointer = (char *) mem_header + HEAD;
        dfree(mem_pointer);
        request_pointer--;
        mem_frees++;
    }
}

size_t generate_random_request_size() {
    size_t size = rand();
    size = (size % (MAX_REQ_SIZE - MIN_REQ_SIZE + 1)) + MIN_REQ_SIZE;
    return size;
}


