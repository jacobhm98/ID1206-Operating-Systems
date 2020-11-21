#include "dlmall.h"

int length();

int main() {
    flist = new();
    void * mem = dalloc(12 * sizeof(int));
    printf("the length of the freelist is %d\n", length());
    dfree(mem);
    printf("the length of the freelist is %d\n", length());
}

//could speed these up and do the calculations for average and length in 1 pass instead of 3,
//buuuut im not gonna because im lazy.
int length(){
    int length = 0;
    struct head *curr = flist;
    while(curr != NULL){
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
    return average_size/length();
}
