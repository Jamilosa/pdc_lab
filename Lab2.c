/* Lab2.c */  
   
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/shm.h>  
#include <stdio.h>  
#include <stdlib.h>  // For exit()

int main() {
    int shm_id;  
    key_t mem_key;  
    int *shm_ptr;  
  
    mem_key = ftok(".", 'a');  
  
    shm_id = shmget(mem_key, 4*sizeof(int), 0666);  
  
    if (shm_id < 0) {  
        printf("*** shmget error (client) ***\n");         
        exit(1);  
    }  
  
    shm_ptr = (int *) shmat(shm_id, NULL, 0);  /* attach */  
  
    if (shm_ptr == (void*) -1) {  
        printf("*** shmat error (client) ***\n");             
        exit(1);     
    }  

    // Read the shared memory and print the contents
    printf("Shared memory contents: %d %d %d %d\n", shm_ptr[0], shm_ptr[1], shm_ptr[2], shm_ptr[3]);

    return 0;  
}
