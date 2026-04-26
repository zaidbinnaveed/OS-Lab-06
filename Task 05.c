/* Task 5: Shared Memory - Square Calculator
   - Parent asks user for an integer and writes it to shared memory
   - Child reads the number from shared memory
   - Child calculates and prints the square
   Compile: gcc task5_shm_square.c -o shm_square -lrt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_NAME "/shm_square"
#define SIZE     sizeof(int)

int main() {
    int fd;
    int *ptr;
    pid_t pid;
    int number;

    /* Create shared memory object */
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    ftruncate(fd, SIZE);

    /* Map shared memory */
    ptr = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    /* Parent reads number before forking */
    printf("Enter number: ");
    scanf("%d", &number);

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }

    if (pid > 0) {
        /* Parent: write number to shared memory */
        *ptr = number;
        printf("Parent: wrote %d to shared memory.\n", number);

        wait(NULL);   /* Wait for child to finish */

        /* Cleanup */
        munmap(ptr, SIZE);
        shm_unlink(SHM_NAME);
    }
    else {
        /* Child: read number, calculate square, print result */
        int n = *ptr;
        printf("Square of %d is: %d\n", n, n * n);

        munmap(ptr, SIZE);
    }

    return 0;
}
