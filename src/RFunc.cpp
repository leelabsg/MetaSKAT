#include <stdio.h>
#include <stdlib.h>
#include "RFunc.h"

void * F_alloc(int n, int size){
    
    void * ptr = NULL;
    
#ifdef _STAND_ALONE_
    ptr = calloc(n, size);
#else
    ptr = (void *) calloc( n, size);
    //Rprintf("Memory alloc %d, %d, [%d]\n", n, size, ptr);
    if(ptr == NULL){
        error("Memory allocation error size:[%d]", n);
    }
#endif

    return ptr;
}


int F_free(void * ptr){
    
    if(ptr ==NULL){
        return 0;
    }
    
#ifdef _STAND_ALONE_
    free(ptr);
#else
    //Rprintf("FREE [%d]\n", ptr);
    free(ptr);
    //Rprintf("FREE-done\n", ptr);
#endif
    
    return 0;
    
}

