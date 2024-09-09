/* Lab1.c */  
   
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
    shm_id = shmget(mem_key, 4*sizeof(int), IPC_CREAT | 0666);  
  
    if (shm_id < 0) {  
        printf("*** shmget error (server) ***\n");         
        exit(1);  
    }  
  
    shm_ptr = (int *) shmat(shm_id, NULL, 0); /* attach */  
  
    if (shm_ptr == (void*) -1) {  
        printf("*** shmat error (server) ***\n");         
        exit(1);  
    }  

    // Write some data to the shared memory
    shm_ptr[0] = 10;
    shm_ptr[1] = 20;
    shm_ptr[2] = 30;
    shm_ptr[3] = 40;

    printf("Shared memory values written: %d %d %d %d\n", shm_ptr[0], shm_ptr[1], shm_ptr[2], shm_ptr[3]);

    // Keep the process running so you can inspect the memory from another process
    printf("Server process is running... Press Ctrl+C to exit.\n");
    while (1);  // Infinite loop to keep the process running

    return 0;  
}
