#include <stdlib.h>
#include <sys/time.h>
#include "dlmall.h"
#include <time.h>

int length_of_list();

float average_size();

size_t generate_random_request_size();

void perform_memory_requests(int);

void print_status();

void perform_memory_frees(int);

void sanity();

int get_random_index(int);

void shrink_array(int, int);

void perform_small_memory_requests(int);

void write_to_blocks();

#define MAX_REQ_SIZE 5000
#define MIN_REQ_SIZE 20
#define MAX_NUM_OF_ALLOTTED_BLOCKS 1050

int mem_requests = 0;
int mem_frees = 0;
int mem_errs = 0;
struct taken *REQUESTS[MAX_NUM_OF_ALLOTTED_BLOCKS];
int request_pointer = 0;


int main() {
    flist = new();
    clock_t tic = clock();
    perform_small_memory_requests(1000);
    for (int i = 0; i < 3000; ++i) {
        write_to_blocks();
    }
    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
}

void write_to_blocks(){
    int message = 42;
    for (int i = 0; i < request_pointer; ++i){
        void * mem_block = HIDE(REQUESTS[i]);
        mem_block = (void *) message;
    }
}

void perform_small_memory_requests(int num_reqs){
    int size = 16;
    void * mem_block = dalloc(size);
    struct taken* head = MAGIC(mem_block);
    REQUESTS[request_pointer] = head;
    request_pointer++;
}
void sanity() {
    struct head *curr = flist;
    struct head *prev = curr->prev;
    while (curr != NULL) {
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
    printf("Total number of memory requests performed: %d, total number of memory frees: %d, current number of allocated memory blocks: %d, number of failed memory requests: %d\n",
           mem_requests, mem_frees, request_pointer, mem_errs);
}

void perform_memory_requests(int num_of_requests) {
    srand(time(0));
    size_t size;
    void *mem_pointer;
    for (int i = 0; i < num_of_requests; ++i) {
        size = generate_random_request_size();
        mem_pointer = dalloc(size);
        if (mem_pointer == NULL) {
            fprintf(stderr, "error allocating memory\n");
            mem_errs++;
            continue;
        }
        mem_requests++;
        struct head *mem_header = (char *) mem_pointer - HEAD;
        REQUESTS[request_pointer] = mem_header;
        request_pointer++;
    }
}

void perform_memory_frees(int num_frees) {
    for (int i = 0; i < num_frees; ++i) {
        int entry_to_free = get_random_index(request_pointer - 1);
        struct taken *mem_header = REQUESTS[entry_to_free];
        void *mem_pointer = (char *) mem_header + HEAD;
        dfree(mem_pointer);
        shrink_array(entry_to_free, request_pointer);
        request_pointer--;
        mem_frees++;
    }
}

void shrink_array(int start, int end) {
    for (int i = start; i < end; i++) {
        REQUESTS[i] = REQUESTS[i + 1];
    }
}

//inclusive of max
int get_random_index(int max_index) {
    int index = rand();
    index = index % (max_index + 1);
    return index;
}

size_t generate_random_request_size() {
    size_t size = rand();
    size = (size % (MAX_REQ_SIZE - MIN_REQ_SIZE + 1)) + MIN_REQ_SIZE;
    return size;
}


