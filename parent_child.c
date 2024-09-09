/* parent_child.c */  

#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/shm.h>  
#include <unistd.h>  // for fork() and sleep()
#include <sys/wait.h>  // for wait()
#include <stdlib.h>
#include <stdio.h>

int main(void)  // Ensure this is correctly defined
{  
    int shmid;  
    char *shmPtr;     
    int n;  
  
    if (fork() == 0)  // Child process
    {  
        sleep(5);  // Delay to allow the parent to write to shared memory
  
        if ((shmid = shmget(2041, 32, 0)) == -1)  
        {  
            perror("shmget (child)");  
            exit(1);  
        }  
  
        shmPtr = shmat(shmid, NULL, 0);  
        if (shmPtr == (char *) -1) {            
            perror("shmat (child)");  
            exit(2);  
        }  
  
        printf("\nChild Reading ....\n\n");  
        for (n = 0; n < 26; n++)             
            putchar(shmPtr[n]);             
        putchar('\n'); 
    }     
    else  // Parent process
    {  
        if ((shmid = shmget(2041, 32, 0666 | IPC_CREAT)) == -1)  
        {  
            perror("shmget (parent)");  
            exit(1);   
        }  
  
        shmPtr = shmat(shmid, NULL, 0);  
        if (shmPtr == (char *) -1) {             
            perror("shmat (parent)");  
            exit(2);  
        }  
  
        for (n = 0; n < 26; n++)         
            shmPtr[n] = 'a' + n;         
        
        printf("Parent Writing ....\n\n");         
        for (n = 0; n < 26; n++)         
            putchar(shmPtr[n]);   
        putchar('\n');               
        wait(NULL);  // Wait for the child to finish
  
        shmdt(shmPtr);  // Detach the shared memory segment
  
        if (shmctl(shmid, IPC_RMID, NULL) == -1)  // Remove the shared memory segment
        {  
            perror("shmctl");  
            exit(-1);  
        }     
    }  
    return 0;   
}  
